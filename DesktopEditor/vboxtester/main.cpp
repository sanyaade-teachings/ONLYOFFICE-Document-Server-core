﻿/*
 * (c) Copyright Ascensio System SIA 2010-2023
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-6 Ernesta Birznieka-Upish
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <algorithm>

#include "help.h"
#include "../common/File.h"
#include "../common/Directory.h"
#include "../../DesktopEditor/common/StringBuilder.h"
#include "../../DesktopEditor/common/SystemUtils.h"
#include "../../DesktopEditor/graphics/BaseThread.h"
#include "../../OfficeUtils/src/OfficeUtils.h"
#include "../../Common/Network/FileTransporter/include/FileTransporter.h"

#ifdef CreateDirectory
#undef CreateDirectory
#endif

#ifdef GetTempPath
#undef GetTempPath
#endif

#ifdef LINUX
#include <unistd.h>
#include <stdio.h>
#endif

// Misc
std::string CorrectValue(const std::string& value)
{
    if (value.empty())
        return "";

    const char* data = value.c_str();

    std::string::size_type pos1 = (data[0] == '\"') ? 1 : 0;
    std::string::size_type pos2 = value.length();

    if (data[pos2 - 1] == '\"')
        --pos2;

    return value.substr(pos1, pos2 - pos1);
}

bool SplitStringAsVector(const std::string& sData, const std::string& sDelimiter, std::vector<std::string>& arrOutput)
{
    arrOutput.clear();

    if ( sData.length() )
    {
        std::string sTmp = sData;
        NSStringUtils::string_replaceA(sTmp, ", ", ",");

        size_t pos_start = 0, pos_end, delim_len = sDelimiter.length();
        std::string token = "";

        while ((pos_end = sTmp.find(sDelimiter, pos_start)) != std::string::npos)
        {
            token = sTmp.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            if (token.length())
                arrOutput.push_back(token);
        }

        token = sTmp.substr(pos_start);
        if ( token.length() )
            arrOutput.push_back(token);
    }

    return arrOutput.size() > 0;
}

//
class CVm
{
public:
    std::string m_sName;
    std::string m_sGuid;
    std::string m_sGuestOS;

    CVm()
    {
        m_sName = "";
        m_sGuid = "";
        m_sGuestOS = "";
    }

    CVm(const std::string& sName, const std::string& sGuid, const std::string& sGuestOS)
    {
        m_sName = sName;
        m_sGuid = sGuid;
        m_sGuestOS = sGuestOS;
    }

    std::string ToString()
    {
        std::stringstream sInfo;

        if ( m_sName.length() && m_sGuid.length() && m_sGuestOS.length() )
            sInfo << m_sName << "-" << m_sGuestOS << "-" << m_sGuid;

        return sInfo.str();
    }
};

class CVirtualBox
{
private:
    std::string m_sVbmPath;

    std::string m_sVmUser;
    std::string m_sVmPassword;
    std::string m_sDesktopUrl;    
    std::string m_sReportName;
    std::string m_sEditorsPath;

    std::string m_sRunScript;
    std::string m_sSetupScript;

    std::vector<CVm*> m_arrVms;

public:
    CVirtualBox()
    {
        m_sVmUser = "dmitry";
        m_sVmPassword = "Dm-23";

        m_sRunScript = "run";
        m_sSetupScript = "setup";

        m_sReportName = "report.txt";

        m_sEditorsPath = "/opt/onlyoffice/desktopeditors/DesktopEditors";

        // test url, need parse somewhere
        m_sDesktopUrl = "http://s3.eu-west-1.amazonaws.com/repo-doc-onlyoffice-com/desktop/linux/debian/onlyoffice-desktopeditors_7.4.0-125~cef107_amd64.deb";

#ifdef WIN32
        m_sVbmPath = "\"c:\\Program Files\\Oracle\\VirtualBox\\VBoxManage.exe\" ";
#endif

#ifdef LINUX
        m_sVBoxManagePath = "/usr/lib/virtualbox/VBoxManage ";
#endif
    }

    bool InitVms()
    {
        m_arrVms.clear();
        std::string sOutput = ExecuteCommand("list vms");

        std::vector<std::string> arrLines;
        if ( SplitStringAsVector(sOutput, "\n", arrLines) )
        {
            for (size_t i = 0; i < arrLines.size(); i++)
            {
                std::string sLine = arrLines[i];

                std::string::size_type pos1 = sLine.find("{");
                std::string::size_type pos2 = sLine.find("}", pos1);

                if (pos1 != std::string::npos && pos2 != std::string::npos && pos2 > pos1)
                {
                    std::string sGuid = sLine.substr(pos1, pos2 - pos1 + 1);
                    std::string sName = sLine.substr(0, pos1 - 1);
                    sName = CorrectValue(sName);
                    std::string sOs = GetVmOS(sGuid);

                    m_arrVms.push_back(new CVm(sName, sGuid, sOs));
                }
            }
        }

        return m_arrVms.size() > 0;
    }

    std::vector<CVm*> GetLinuxVms()
    {
        std::vector<CVm*> arrVms;

        for (size_t i = 0; i < m_arrVms.size(); i++)
        {
            std::string sGuestOs = m_arrVms[i]->m_sGuestOS;
            std::transform(sGuestOs.begin(), sGuestOs.end(), sGuestOs.begin(), tolower);

            if ( sGuestOs.find("ubuntu") != std::string::npos )
                arrVms.push_back(m_arrVms[i]);
        }

        return arrVms;
    }

    bool StartVm(const std::string& sGuid)
    {
        bool bResult = false;

        if ( sGuid.length() )
        {
            std::string sCommand = "startvm " + sGuid;
            std::string sOutput = ExecuteCommand(sCommand);

            bResult = sOutput.find("has been successfully started") != std::string::npos;
        }

        return bResult;
    }

    bool ResetVm(const std::string& sGuid)
    {
        bool bResult = false;

        if ( sGuid.length() )
        {
            std::string sCommand = "controlvm " + sGuid + " reset";
            std::string sOutput = ExecuteCommand(sCommand);

            bResult = sOutput.find("") != std::string::npos;
        }

        return bResult;
    }

    void WaitLoadVm(const std::string& sGuid)
    {
        // Wait success or 10 min
        int iSleep = 5000;
        int iCount = 10 * 60 * 1000 / iSleep;
        if ( sGuid.length() )
        {
            while ( (iCount > 0) && !IsVmLoggedIn(sGuid))
            {
                NSThreads::Sleep(iSleep);
                iCount--;
            }
        }
    }

    bool WaitInstall(const std::string& sGuid)
    {
        // Wait success or 10 min
        int iSleep = 5000;
        int iCount = 10 * 60 * 1000 / iSleep;

        if ( sGuid.length() )
        {
            while ( (iCount > 0) && (IsProcessExists(sGuid, "dpkg") || IsProcessExists(sGuid, "apt") || !IsLocationExists(sGuid, m_sEditorsPath)) )
            {
                NSThreads::Sleep(iSleep);
                iCount--;
            }
        }

        // True - installation, False - timeout
        return iCount > 0;
    }

    bool StopVm(const std::string& sGuid, bool bSaveState = false)
    {
        bool bResult = false;

        if ( sGuid.length() )
        {
            std::string sCommand = "controlvm " + sGuid + (bSaveState ? " savestate" : " poweroff");
            std::string sOutput = ExecuteCommand(sCommand);

            bResult = sOutput.find("100%") != std::string::npos;
        }

        return bResult;
    }

    bool IsVmLoggedIn(const std::string& sGuid)
    {
        bool bResult = false;

        if ( sGuid.length() )
        {
            // not works on Ubuntu 20
            std::string sCommand = "guestcontrol " + sGuid +
                                   " run --exe /usr/bin/whoami" +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " --wait-stdout";

            std::string sOutput = ExecuteCommand(sCommand);

            bool bWhoami = sOutput.find(m_sVmUser) != std::string::npos;

            sCommand = "guestcontrol " + sGuid +
                                   " run --exe /usr/bin/uptime" +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " --wait-stdout";

            sOutput = ExecuteCommand(sCommand);

            bool bUptime = sOutput.find("user") != std::string::npos;

            bResult = bWhoami || bUptime;
        }

        return bResult;
    }

    bool SaveScreenshot(CVm* pVm)
    {
        bool bResult = false;

        if ( pVm )
        {
            std::string sFilePath = GetReportDir() + "/" + pVm->m_sGuid + ".png";

            if ( NSFile::CFileBinary::Exists(UTF8_TO_U(sFilePath)) )
                NSFile::CFileBinary::Remove(UTF8_TO_U(sFilePath));

            std::string sCommand = "controlvm " + pVm->m_sGuid + " screenshotpng " + sFilePath;
            std::string sOutput = ExecuteCommand(sCommand);

            bResult = NSFile::CFileBinary::Exists(UTF8_TO_U(sFilePath));
        }

        return bResult;
    }

    bool PrepareWorkingDir(const std::string& sGuid)
    {
        bool bResult = false;

        if ( sGuid.length() && m_sVmUser.length() )
        {
            std::string sCommand = "guestcontrol " + sGuid +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " rmdir --recursive " + GetWorkingDir();

            std::string sOutput = ExecuteCommand(sCommand);

            sCommand = "guestcontrol " + sGuid +
                       " --username " + m_sVmUser +
                       " --password " + m_sVmPassword +
                       " mkdir " + GetWorkingDir();

            sOutput = ExecuteCommand(sCommand);

            bResult = true;
        }

        return bResult;
    }

    bool DownloadDistrib(const std::string& sGuid)
    {
        bool bResult = false;

        if ( sGuid.length() && m_sDesktopUrl.length() )
        {
            // wget may not download the file to the end, use curl

            /*std::string sCommand = "guestcontrol " + sGuid +
                                   " run --exe /usr/bin/wget" +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " --wait-stdout -- wget/arg0 " + m_sDesktopUrl +
                                   " -P " + GetWorkingDir();*/

            std::string sCommand = "guestcontrol " + sGuid +
                                   " run --exe /usr/bin/curl" +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " --wait-stdout -- curl/arg0 " + m_sDesktopUrl +
                                   " --output " + GetWorkingDir() + "/" + GetFileName(m_sDesktopUrl);

            std::string sOutput = ExecuteCommand(sCommand);

            // Wait flush to disk. This problem with wget and curl. Wait min
            NSThreads::Sleep(60000);

            bResult = true;
            // sOutput is empty...
            // bResult = sOutput.find("") != std::string::npos;
        }

        return bResult;
    }

    bool CopyScripts(const std::string& sGuid)
    {
        bool bResult = false;

        if ( sGuid.length() )
        {
            // Setup
            std::string sScriptPath = U_TO_UTF8(NSDirectory::GetTempPath()) + "/" + m_sSetupScript;
            std::string sDistribFile = GetFileName(m_sDesktopUrl);

            if ( NSFile::CFileBinary::Exists(UTF8_TO_U(sScriptPath)) )
                NSFile::CFileBinary::Remove(UTF8_TO_U(sScriptPath));

            std::string sData =  "#!/bin/bash\n" \
                                "echo \"Install DesktopEditors\"\n" \
                                "apt purge onlyoffice-desktopeditors -y\n" \
                                "dpkg -i ./" + sDistribFile + "\n" \
                                "apt install -f";

            NSFile::CFileBinary oFile;
            bResult = oFile.CreateFileW(UTF8_TO_U(sScriptPath));
            oFile.WriteStringUTF8(UTF8_TO_U(sData));
            oFile.CloseFile();

            std::string sCommand = "guestcontrol " + sGuid +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " copyto " + sScriptPath + " " + GetWorkingDir() + "/" + m_sSetupScript;

            std::string sOutput = ExecuteCommand(sCommand);

            NSFile::CFileBinary::Remove(UTF8_TO_U(sScriptPath));

            // Run
            sScriptPath = U_TO_UTF8(NSDirectory::GetTempPath()) + "/" + m_sRunScript;

            if ( NSFile::CFileBinary::Exists(UTF8_TO_U(sScriptPath)) )
                NSFile::CFileBinary::Remove(UTF8_TO_U(sScriptPath));

            std::string sEditorsFolder = m_sEditorsPath;
            NSStringUtils::string_replaceA(sEditorsFolder, GetFileName(m_sEditorsPath), "");

            sData =  "#!/bin/bash\n" \
                     "LP_LIBRARY_PATH=" + sEditorsFolder + " " + m_sEditorsPath;

            bResult = oFile.CreateFileW(UTF8_TO_U(sScriptPath));
            oFile.WriteStringUTF8(UTF8_TO_U(sData));
            oFile.CloseFile();

            sCommand = "guestcontrol " + sGuid +
                       " --username " + m_sVmUser +
                       " --password " + m_sVmPassword +
                       " copyto " + sScriptPath + " " + GetWorkingDir() + "/" + m_sRunScript;

            sOutput = ExecuteCommand(sCommand);

            NSFile::CFileBinary::Remove(UTF8_TO_U(sScriptPath));
        }

        return bResult;
    }

    bool RemoveScripts(const std::string& sGuid)
    {
        bool bResult = true;

        if ( sGuid.length() )
        {
            std::vector<std::string> arrScipts;
            arrScipts.push_back(m_sRunScript);
            arrScipts.push_back(m_sSetupScript);

            for (size_t i = 0; i < arrScipts.size(); i++)
            {
                std::string sScriptPath = GetWorkingDir() + "/" + arrScipts[i];

                if ( IsLocationExists(sGuid, sScriptPath) )
                {
                    std::string sCommand = "guestcontrol " + sGuid +
                                           " --username " + m_sVmUser +
                                           " --password " + m_sVmPassword +
                                           " rm " + sScriptPath;

                    std::string sOutput = ExecuteCommand(sCommand);

                    bResult &= !IsLocationExists(sGuid, sScriptPath);
                }
            }
        }

        return bResult;
    }

    bool RunEditors(const std::string& sGuid)
    {
        bool bResult = true;

        if ( sGuid.length() && IsLocationExists(sGuid, m_sEditorsPath) )
        {
            std::string sRunScript = GetWorkingDir() + "/" + m_sRunScript;

            std::string sCommand = "guestcontrol " + sGuid +
                                   " start " + sRunScript +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " --putenv DISPLAY=:0.0";

            std::string sOutput = ExecuteCommand(sCommand);

            // Wait main page
            NSThreads::Sleep(10000);
        }

        return bResult;
    }

    bool IsReadyReset(const std::string& sGuid)
    {
        bool bResult = true;

        if ( sGuid.length() )
        {
            std::string sRunScript = GetWorkingDir() + "/" + m_sRunScript;
            std::string sInstallScript = GetWorkingDir() + "/" + m_sSetupScript;
            std::string sDistribPath = GetWorkingDir() + "/" + GetFileName(m_sDesktopUrl);

            bResult = IsLocationExists(sGuid, sRunScript) &&
                      IsLocationExists(sGuid, sInstallScript) &&
                      IsLocationExists(sGuid, sDistribPath);
        }

        return bResult;
    }

    bool IsProcessExists(const std::string& sGuid, const std::string& sProcName)
    {
        bool bResult = false;

        if ( sGuid.length() && sProcName.length() )
        {
            std::string sCommand = "guestcontrol " + sGuid +
                                   " run --exe /bin/ps" +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " --wait-stdout -- ps/arg0 -e";

            std::string sOutput = ExecuteCommand(sCommand);

            if ( sOutput.length() )
            {
                std::vector<std::string> arrLines;
                std::vector<std::string> arrParts;

                if ( SplitStringAsVector(sOutput, "\n", arrLines) )
                {
                    for (size_t i = 0; i < arrLines.size(); i++)
                    {
                        std::string sLine = arrLines[i];
                        if ( (i > 0) && SplitStringAsVector(sLine, " ", arrParts) )
                        {
                            if ( arrParts[arrParts.size() - 1] == sProcName )
                            {
                                bResult = true;
                                break;
                            }
                        }
                    }
                }
            }
        }

        return bResult;
    }

    bool IsEditorsRunned(const std::string& sGuid)
    {
        bool bResult = true;

        if ( sGuid.length() )
        {
            std::string sEditorProc = GetFileName(m_sEditorsPath);

            bResult = IsProcessExists(sGuid, sEditorProc);
        }

        return bResult;
    }

    // Report
    std::string GetReportDir()
    {
        std::string sAppPath = U_TO_UTF8(NSFile::GetProcessDirectory());
        sAppPath += "/report";

        if ( !NSDirectory::Exists(UTF8_TO_U(sAppPath)) )
            NSDirectory::CreateDirectory(UTF8_TO_U(sAppPath));

        return sAppPath;
    }

    void CreateReport()
    {
        std::ofstream oFile;
        std::string sReportPath = GetReportDir() + "/" + m_sReportName;
        oFile.open(sReportPath, std::ofstream::out | std::ofstream::trunc);
        oFile.close();
    }

    void WriteReport(CVm* pVm, const std::string& sText)
    {
        if ( pVm && sText.length() )
        {
            std::string sInfo = pVm->ToString() + " -> " + sText;

            std::ofstream oFile;
            std::string sReportPath = GetReportDir() + "/" + m_sReportName;
            oFile.open(sReportPath, std::ios_base::app);
            oFile << sInfo.c_str() << std::endl;
            oFile.close();
        }
    }

    void RemoveReport()
    {
        if ( NSDirectory::Exists(UTF8_TO_U(GetReportDir())) )
            NSDirectory::DeleteDirectory(UTF8_TO_U(GetReportDir()));
    }

private:
    std::string GetWorkingDir()
    {
        std::string sDir = "";

        if ( m_sVmUser.length() )
            sDir = "/home/" + m_sVmUser + "/vboxtester";

        return sDir;
    }

    bool IsLocationExists(const std::string& sGuid, const std::string& sPath)
    {
        // check ile or folder
        bool bResult = false;

        if ( sGuid.length() && sPath.length() )
        {
            std::string sFile = "";
            std::string sFolder = sPath;
            std::vector<std::string> arrParts;
            if ( SplitStringAsVector(sPath, "/", arrParts) )
            {
                sFile = arrParts[arrParts.size() - 1];
                NSStringUtils::string_replaceA(sFolder, "/" + sFile, "");
            }

            std::string sCommand = "guestcontrol " + sGuid +
                                   " run --exe /bin/ls" +
                                   " --username " + m_sVmUser +
                                   " --password " + m_sVmPassword +
                                   " --wait-stdout -- ls/arg0 " + sFolder;

            std::string sOutput = ExecuteCommand(sCommand);
            if ( sOutput.length() )
            {
                if ( SplitStringAsVector(sOutput, "\n", arrParts) )
                    bResult = std::find(arrParts.begin(), arrParts.end(), sFile) != arrParts.end();
            }
        }

        return bResult;
    }

    std::string GetVmOS(const std::string& sGuid)
    {
        return ParseVmInfo(sGuid, "Guest OS");
    }

    std::string ParseVmInfo(const std::string& sGuid, const std::string& sPref)
    {
        std::string sStatus = "";

        if ( sGuid.length() && sPref.length() )
        {
            std::string command = "showvminfo " + sGuid;
            std::string sOutput = ExecuteCommand(command);

            std::vector<std::string> arrLines;
            if ( SplitStringAsVector(sOutput, "\n", arrLines) )
            {
                std::string sPrefix = sPref + ":";

                for (size_t i = 0; i < arrLines.size(); i++)
                {
                    std::string sLine = arrLines[i];

                    std::string::size_type pos = sLine.find(sPrefix);
                    if ( pos != std::string::npos )
                    {
                        sStatus = sLine;
                        pos = sStatus.find(sPrefix + " ");
                        while ( pos != std::string::npos )
                        {
                            NSStringUtils::string_replaceA(sStatus, sPrefix + " ", sPrefix);
                            pos = sStatus.find(sPrefix + " ");
                        }
                        NSStringUtils::string_replaceA(sStatus, sPrefix, "");
                        break;
                    }
                }
            }
        }

        return sStatus;
    }

    std::string GetFileName(const std::string& sPath)
    {
        std::string sName = "";

        if ( sPath.length() )
        {
            std::vector<std::string> arrParts;

            if ( SplitStringAsVector(sPath, "/", arrParts) )
                sName = arrParts[arrParts.size() - 1];
        }

        return sName;
    }

    std::string ExecuteCommand(const std::string& sArgs)
    {
        std::string sResult = "";

        std::array<char, 128> aBuffer;
        std::string sCommand = m_sVbmPath + sArgs;

#ifdef WIN32
        FILE* pipe = _popen(sCommand.c_str(), "r");
#endif
#ifdef LINUX
        FILE* pipe = popen(sCommand.c_str(), "r");
#endif
        if (!pipe)
            return sResult;

        while ( fgets(aBuffer.data(), 128, pipe) != NULL )
        {
            sResult += aBuffer.data();
        }

        return sResult;
    }
};

// Main
int main(int argc, char** argv)
{
    // Test
    CVirtualBox oTester;
    oTester.InitVms();

    oTester.CreateReport();
    std::vector<CVm*> arrLinux = oTester.GetLinuxVms();

    for (size_t i = 0; i < arrLinux.size(); i++)
    {
        CVm* pVm = arrLinux[i];
        std::string sGuid = pVm->m_sGuid;
        std::string sName = pVm->m_sName;

        //if ( sName != "Ubuntu16" )
        //    continue;

        oTester.StartVm(sGuid);
        oTester.WaitLoadVm(sGuid);

        oTester.PrepareWorkingDir(sGuid);

        oTester.CopyScripts(sGuid);
        oTester.DownloadDistrib(sGuid);

        if ( oTester.IsReadyReset(sGuid) )
        {
            oTester.ResetVm(sGuid);
            oTester.WaitLoadVm(sGuid);

            if ( oTester.WaitInstall(sGuid) )
            {
                oTester.WriteReport(pVm, "installation - ok");

                oTester.RunEditors(sGuid);

                if ( oTester.IsEditorsRunned(sGuid) )
                {
                    // Check successful or not
                    // Need more checks such as logs etc.

                    oTester.SaveScreenshot(pVm);
                }
            }
            else
            {
                oTester.WriteReport(pVm, "installation - error, exit by timeout");
            }

            oTester.RemoveScripts(sGuid);
        }

        oTester.StopVm(sGuid);
    }

    //oTester.RemoveReport();

    // Parse arguments
    for (int i = 0; i < argc; ++i)
    {
        std::string sParam(argv[i]);

        if (sParam.find("--") == 0)
        {
            std::string sKey = "";
            std::string sValue = "";

            // Parse key - value
            std::wstring::size_type pos = sParam.find('=');
            if ( pos == std::wstring::npos )
            {
                sKey = sParam;

                if ( IsNeedSetValue(sKey))
                {
                    if (i < argc - 1)
                    {
                        i++;
                        sValue = std::string(argv[i]);
                    }

                    // Checks if value or next key exist
                    if ( !sValue.length() || (sValue.find("--") == 0) )
                    {
                        std::cout << "\nError. Check input parameters\n";
                        return 1;
                    }
                }
            }
            else
            {
                sKey = sParam.substr(0, pos);
                sValue = sParam.substr( pos + 1 );
            }

            // Check key
            if ( !IsCommandExists(sKey) )
            {
                std::cout << "\nError. Unknown parameter " << sKey << "\n" << "Print usage information --help\n";
                return 1;
            }

            // Usability
            if (sKey == sCmdHelp || sKey == sCmdHelpFull)
            {
            }

            // Settings
            else if (sKey == sCmdDir)
            {
                sValue = CorrectValue(sValue);
            }

        }
    }    

    return 0;
}

