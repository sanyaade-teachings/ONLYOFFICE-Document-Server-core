/*
 * (c) Copyright Ascensio System SIA 2010-2024
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
#include "../../../DesktopEditor/graphics/pro/js/wasm/src/serialize.h"
#include "../../../DesktopEditor/common/File.h"
#include "../../../DesktopEditor/common/Directory.h"

#include <vector>

int main()
{
    std::vector<std::wstring> arrFiles = NSDirectory::GetFiles(NSFile::GetProcessDirectory() + L"/../../CMap/CMap");

    NSWasm::CData oRes;
    for (const std::wstring& sFile : arrFiles)
    {
        BYTE* pData = NULL;
        DWORD nSize;
        NSFile::CFileBinary oFile;
        if (oFile.ReadAllBytes(sFile, &pData, nSize))
        {
            std::wstring sFileName = NSFile::GetFileName(sFile);
            BYTE* pStr = NULL;
            LONG nStrSize;
            NSFile::CUtf8Converter::GetUtf8StringFromUnicode(sFileName.c_str(), (LONG)sFileName.length(), pStr, nStrSize);
            oRes.WriteString(pStr, nStrSize);
            RELEASEARRAYOBJECTS(pStr);

            oRes.AddInt(nSize);
            oRes.Write(pData, nSize);

            oFile.CloseFile();
        }

        RELEASEARRAYOBJECTS(pData);
    }

    NSFile::CFileBinary oFile;
	if (oFile.CreateFileW(NSFile::GetProcessDirectory() + L"/../cmap.bin"))
    {
        oFile.WriteFile(oRes.GetBuffer(), oRes.GetSize());
        oFile.CloseFile();
    }

    oRes.Clear();
    return 0;
}
