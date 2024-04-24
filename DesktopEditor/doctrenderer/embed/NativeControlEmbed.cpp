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

#include "NativeControlEmbed.h"
#include "../server.h"

JSSmart<CJSValue> CNativeControlEmbed::SetFilePath(JSSmart<CJSValue> path)
{
	m_pInternal->SetFilePath(path->toStringW());
	return NULL;
}

JSSmart<CJSValue> CNativeControlEmbed::GetFilePath()
{
	return CJSContext::createString(m_pInternal->GetFilePath());
}

JSSmart<CJSValue> CNativeControlEmbed::SetFileId(JSSmart<CJSValue> fileId)
{
	m_pInternal->SetFileId(fileId->toStringW());
	return NULL;
}

JSSmart<CJSValue> CNativeControlEmbed::GetFileId()
{
	return CJSContext::createString(m_pInternal->GetFileId());
}

JSSmart<CJSValue> CNativeControlEmbed::GetFileBinary(JSSmart<CJSValue> file)
{
	std::wstring sFilePath = file->toStringW();

	if (CServerInstance::getInstance().IsEnable())
	{
		std::wstring sFileFolder = NSFile::GetDirectoryName(m_pInternal->GetFilePath());
		if (0 == sFilePath.find(sFileFolder))
			return CJSContext::createUint8Array(sFilePath);
		return CJSContext::createNull();
	}

	return CJSContext::createUint8Array(sFilePath);
}

JSSmart<CJSValue> CNativeControlEmbed::GetFontBinary(JSSmart<CJSValue> file)
{
	// TODO:
	// по идее файлы могут совпадать по имени, но лежать в разных директориях.
	// и поэтому в AllFonts.js надо бы писать пути полные.
	// пока оставим поддержку старой версии тоже
	std::wstring sFile = file->toStringW();
	bool bIsFullFilePath = (std::wstring::npos != sFile.find('\\') || std::wstring::npos != sFile.find('/'));
	if (bIsFullFilePath)
	{
		bIsFullFilePath = NSFile::CFileBinary::Exists(sFile);
	}

	if (!bIsFullFilePath)
	{
		std::map<std::wstring, std::wstring>::iterator pair = m_pInternal->m_map_fonts.find(sFile);
		if (pair != m_pInternal->m_map_fonts.end())
			sFile = pair->second;
		else
			sFile = m_pInternal->m_sDefaultFont;
	}

	return CJSContext::createUint8Array(sFile);
}

JSSmart<CJSValue> CNativeControlEmbed::GetFontsDirectory()
{
	return CJSContext::createString(m_pInternal->m_strFontsDirectory);
}

JSSmart<CJSValue> CNativeControlEmbed::GetFileString(JSSmart<CJSValue> file)
{
	if (CServerInstance::getInstance().IsEnable())
		return CJSContext::createNull();
	return CJSContext::createUint8Array(file->toStringW());
}

JSSmart<CJSValue> CNativeControlEmbed::GetEditorType()
{
	return CJSContext::createString(m_pInternal->m_strEditorType);
}

JSSmart<CJSValue> CNativeControlEmbed::CheckNextChange()
{
	m_pInternal->m_nCurrentChangesNumber++;
	if (-1 != m_pInternal->m_nMaxChangesNumber)
	{
		if (m_pInternal->m_nCurrentChangesNumber >= m_pInternal->m_nMaxChangesNumber)
		{
			return CJSContext::createBool(false);
		}
	}
	return CJSContext::createBool(true);
}

JSSmart<CJSValue> CNativeControlEmbed::GetCountChanges()
{
	int nCount = 0;
	if (m_pInternal->m_pChanges != NULL)
	{
		nCount = (int)m_pInternal->m_pChanges->size();
	}

	return CJSContext::createInt(nCount);
}

JSSmart<CJSValue> CNativeControlEmbed::GetChangesFile(JSSmart<CJSValue> index)
{
	int nIndex = index->toInt32();
	std::wstring strFile = L"";
	if (m_pInternal->m_pChanges != NULL)
		strFile = (*m_pInternal->m_pChanges)[nIndex];
	return CJSContext::createString(strFile);
}

JSSmart<CJSValue> CNativeControlEmbed::Save_AllocNative(JSSmart<CJSValue> nLen)
{
	int Len = nLen->toInt32();
	m_pInternal->Save_Alloc(Len);
	return CJSContext::createUint8Array(m_pInternal->m_pSaveBinary, m_pInternal->m_nSaveLen, true);
}

JSSmart<CJSValue> CNativeControlEmbed::Save_ReAllocNative(JSSmart<CJSValue> pos, JSSmart<CJSValue> len)
{
	int _pos = pos->toInt32();
	int _len = len->toInt32();
	m_pInternal->Save_ReAlloc(_pos, _len);
	return CJSContext::createUint8Array(m_pInternal->m_pSaveBinary, m_pInternal->m_nSaveLen, true);
}

JSSmart<CJSValue> CNativeControlEmbed::Save_End(JSSmart<CJSValue> pos, JSSmart<CJSValue> len)
{
	std::string sHeader = pos->toStringA();
	int _len = len->toInt32();
	m_pInternal->Save_End(sHeader, _len);
	return NULL;
}

JSSmart<CJSValue> CNativeControlEmbed::AddImageInChanges(JSSmart<CJSValue> img)
{
	std::wstring sImage = img->toStringW();
	if (sImage.empty())
		return NULL;

	std::map<std::wstring, bool>::const_iterator iter = m_pInternal->m_mapImagesInChanges.find(sImage);
	if (iter == m_pInternal->m_mapImagesInChanges.end())
		m_pInternal->m_mapImagesInChanges.insert(std::pair<std::wstring, bool>(sImage, true));
	return NULL;
}

JSSmart<CJSValue> CNativeControlEmbed::ConsoleLog(JSSmart<CJSValue> message)
{
	m_pInternal->ConsoleLog(message->toStringA());
	return NULL;
}

JSSmart<CJSValue> CNativeControlEmbed::SaveChanges(JSSmart<CJSValue> sParam, JSSmart<CJSValue> nDeleteIndex, JSSmart<CJSValue> nCount)
{
	m_pInternal->DumpChanges(sParam->toStringA(), nDeleteIndex->toInt32(), nCount->toInt32());
	return NULL;
}

JSSmart<CJSValue> CNativeControlEmbed::ZipOpen(JSSmart<CJSValue> name)
{
	bool bIsOpen = m_pInternal->m_oZipWorker.Open(name->toStringW());
	if (!bIsOpen)
		return CJSContext::createNull();

	JSSmart<CJSObject> obj = CJSContext::createObject();
	for (std::vector<std::wstring>::iterator i = m_pInternal->m_oZipWorker.m_arFiles.begin(); i != m_pInternal->m_oZipWorker.m_arFiles.end(); i++)
	{
		std::string sFile = NSFile::CUtf8Converter::GetUtf8StringFromUnicode(*i);
		obj->set(sFile.c_str(), CJSContext::createString(sFile));
	}

	return obj->toValue();
}

JSSmart<CJSValue> CNativeControlEmbed::ZipOpenBase64(JSSmart<CJSValue> name)
{
	bool bIsOpen = m_pInternal->m_oZipWorker.OpenBase64(name->toStringA());
	if (!bIsOpen)
		return CJSContext::createNull();

	JSSmart<CJSObject> obj = CJSContext::createObject();
	for (std::vector<std::wstring>::iterator i = m_pInternal->m_oZipWorker.m_arFiles.begin(); i != m_pInternal->m_oZipWorker.m_arFiles.end(); i++)
	{
		std::string sFile = NSFile::CUtf8Converter::GetUtf8StringFromUnicode(*i);
		obj->set(sFile.c_str(), CJSContext::createString(sFile));
	}

	return obj->toValue();
}

JSSmart<CJSValue> CNativeControlEmbed::ZipFileAsString(JSSmart<CJSValue> name)
{
	BYTE* pData = NULL;
	DWORD len = 0;
	m_pInternal->m_oZipWorker.GetFileData(name->toStringW(), pData, len);
	return  CJSContext::createString((char*)pData, len);
}

JSSmart<CJSValue> CNativeControlEmbed::ZipFileAsBinary(JSSmart<CJSValue> name)
{
	return CJSContext::createUint8Array(m_pInternal->m_oZipWorker.m_sTmpFolder + L"/" + name->toStringW());
}

JSSmart<CJSValue> CNativeControlEmbed::ZipClose()
{
	m_pInternal->m_oZipWorker.Close();
	return NULL;
}

JSSmart<CJSValue> CNativeControlEmbed::GetImageUrl(JSSmart<CJSValue> sUrl)
{
	std::wstring Url = sUrl->toStringW();

	if (!m_pInternal->m_pWorker)
		m_pInternal->m_pWorker = new CImagesWorker(m_pInternal->m_strImagesDirectory);

	std::wstring sRet = m_pInternal->m_pWorker->GetImage(Url);

	return CJSContext::createString(sRet);
}

JSSmart<CJSValue> CNativeControlEmbed::GetImagesPath()
{
	return CJSContext::createString(m_pInternal->m_strImagesDirectory);
}

#include "./../../graphics/MetafileToRenderer.h"
#include "./../../raster/BgraFrame.h"
JSSmart<CJSValue> CNativeControlEmbed::GetImageOriginalSize(JSSmart<CJSValue> sUrl)
{
	IMetafileToRenderter oRenderer(NULL);
	oRenderer.SetMediaDirectory(NSDirectory::GetFolderPath(m_pInternal->m_strImagesDirectory));
	std::wstring sPath = oRenderer.GetImagePath(sUrl->toStringW());
	CBgraFrame oFrame;
	if (oFrame.OpenFile(sPath))
	{
		JSSmart<CJSObject> ret = CJSContext::createObject();
		ret->set("W", oFrame.get_Width());
		ret->set("H", oFrame.get_Height());
		return ret->toValue();
	}
	return CJSContext::createUndefined();
}
