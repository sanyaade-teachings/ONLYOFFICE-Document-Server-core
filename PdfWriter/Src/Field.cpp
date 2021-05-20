/*
* (c) Copyright Ascensio System SIA 2010-2019
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
* You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
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
#include "Field.h"
#include "Pages.h"
#include "Streams.h"
#include "Document.h"
#include "ResourcesDictionary.h"
#include "Types.h"

#include <algorithm>
#include <math.h>

#include "../../DesktopEditor/common/SystemUtils.h"
#include "../../DesktopEditor/common/File.h"

namespace PdfWriter
{
	//----------------------------------------------------------------------------------------
	// CFieldBase
	//----------------------------------------------------------------------------------------
	CFieldBase::CFieldBase(CXref* pXref, CDocument* pDocument)
	{
		pXref->Add(this);
		Add("Ff", (unsigned int)0);

		m_pXref     = pXref;
		m_pDocument = pDocument;
	}
	void CFieldBase::SetReadOnlyFlag(bool isReadOnly)
	{
		SetFlag(isReadOnly, 1 << 0);
	}
	void CFieldBase::SetRequiredFlag(bool isRequired)
	{
		SetFlag(isRequired, 1 << 1);
	}
	void CFieldBase::SetNoExportFlag(bool isNoExport)
	{
		SetFlag(isNoExport, 1 << 2);
	}
	void CFieldBase::SetFlag(bool isFlag, int nBit)
	{
		int nFlags = ((CNumberObject*)this->Get("Ff"))->Get();

		if ((nFlags & nBit) && !isFlag)
		{
			nFlags &= 0xffffffff ^ nBit;
		}
		else if (!(nFlags & nBit) && isFlag)
		{
			nFlags |= nBit;
		}

		Add("Ff", nFlags);
	}
	void CFieldBase::AddPageRect(CPage* pPage, const TRect& oRect)
	{
		if (!pPage)
			return;

		pPage->AddAnnotation(this);

		Add("Type", "Annot");
		Add("Subtype", "Widget");

		Add("P", pPage);

		CArrayObject* pArray = new CArrayObject();
		if (!pArray)
			return;

		Add("Rect", pArray);

		if (oRect.fTop < oRect.fBottom)
		{
			pArray->Add(oRect.fLeft);
			pArray->Add(oRect.fTop);
			pArray->Add(oRect.fRight);
			pArray->Add(oRect.fBottom);

			m_oRect.fLeft = oRect.fLeft;
			m_oRect.fTop = oRect.fTop;
			m_oRect.fRight = oRect.fRight;
			m_oRect.fBottom = oRect.fBottom;
		}
		else
		{
			pArray->Add(oRect.fLeft);
			pArray->Add(oRect.fBottom);
			pArray->Add(oRect.fRight);
			pArray->Add(oRect.fTop);

			m_oRect.fLeft = oRect.fLeft;
			m_oRect.fTop = oRect.fBottom;
			m_oRect.fRight = oRect.fRight;
			m_oRect.fBottom = oRect.fTop;
		}

		Add("F", 4);		
	}
	void CFieldBase::SetFieldName(const std::wstring& wsName) 
	{
		std::string sName = NSFile::CUtf8Converter::GetUtf8StringFromUnicode(wsName);
		Add("T", new CStringObject(sName.c_str(), true));
	}
	void CFieldBase::SetFieldHint(const std::wstring& wsHint)
	{
		std::string sHint = NSFile::CUtf8Converter::GetUtf8StringFromUnicode(wsHint);
		Add("TU", new CStringObject(sHint.c_str(), true));
	}
	TRect& CFieldBase::GetRect()
	{
		return m_oRect;
	}
	CResourcesDict* CFieldBase::GetResourcesDict()
	{
		return m_pDocument->GetFieldsResources();
	}
	//----------------------------------------------------------------------------------------
	// CTextField
	//----------------------------------------------------------------------------------------
	CTextField::CTextField(CXref* pXref, CDocument* pDocument) : CFieldBase(pXref, pDocument)
	{
		Add("FT", "Tx");
	}
	void CTextField::SetMultilineFlag(bool isMultiLine)
	{
		SetFlag(isMultiLine, 1 << 12);
	}
	void CTextField::SetPasswordFlag(bool isPassword) 
	{
		SetFlag(isPassword, 1 << 13);
	}
	void CTextField::SetFileSelectFlag(bool isFileSelect)
	{
		SetFlag(isFileSelect, 1 << 20);
	}
	void CTextField::SetDoNotSpellCheckFlag(bool isDoNotSpellCheck)
	{
		SetFlag(isDoNotSpellCheck, 1 << 22);
	}
	void CTextField::SetDoNotScrollFlag(bool isDoNotScroll)
	{
		SetFlag(isDoNotScroll, 1 << 23);
	}
	void CTextField::SetCombFlag(bool isComb)
	{
		SetFlag(isComb, 1 << 24);
	}
	void CTextField::SetRichTextFlag(bool isRichText)
	{
		SetFlag(isRichText, 1 << 25);
	}
	void CTextField::SetMaxLen(int nMaxLen)
	{
		Add("MaxLen", nMaxLen);
	}
	void CTextField::SetValue(const std::wstring &wsValue, CFontDict* pFont, double dFontSize, double dX, double dY)
	{
		std::string sValue = NSFile::CUtf8Converter::GetUtf8StringFromUnicode(wsValue);
		Add("V", new CStringObject(sValue.c_str(), true));

		CAnnotAppearance* pAppearance = new CAnnotAppearance(m_pXref, this);
		Add("AP", pAppearance);
		

		CAnnotAppearanceObject* pNormal = pAppearance->GetNormal();

		CResourcesDict* pFieldsResources = m_pDocument->GetFieldsResources();

		CResourcesDict* pResources = new CResourcesDict(m_pXref, true, false);
		const char* sFontName = pResources->GetFontName(pFont);
		if (!sFontName)
			return;

		Add("DR", pResources);

		pNormal->DrawSimpleText(wsValue, pFieldsResources->GetFontName(pFont), dFontSize, dX, dY);

		std::string sDA = "0 0 0 rg /";
		sDA.append(sFontName);
		sDA.append(" ");
		sDA.append(std::to_string(dFontSize));
		sDA.append(" Tf");

		Add("DA", new CStringObject(sDA.c_str()));
	}


	CAnnotAppearance::CAnnotAppearance(CXref* pXref, CFieldBase* pField)
	{
		m_pXref  = pXref;
		m_pField = pField;

		m_pNormal   = new CAnnotAppearanceObject(pXref, pField);
		m_pRollover = NULL;
		m_pDown     = NULL;

		Add("N", m_pNormal);
	}
	CAnnotAppearanceObject* CAnnotAppearance::GetNormal()
	{
		return m_pNormal;
	}
	CAnnotAppearanceObject* CAnnotAppearance::GetRollover()
	{
		if (!m_pRollover)
		{
			m_pRollover = new CAnnotAppearanceObject(m_pXref, m_pField);
			Add("R", m_pRollover);
		}

		return m_pRollover;
	}
	CAnnotAppearanceObject* CAnnotAppearance::GetDown()
	{
		if (!m_pDown)
		{
			m_pDown = new CAnnotAppearanceObject(m_pXref, m_pField);
			Add("D", m_pDown);
		}

		return m_pDown;
	}
	
	CAnnotAppearanceObject::CAnnotAppearanceObject(CXref* pXref, CFieldBase* pField)
	{
		m_pXref   = pXref;
		m_pStream = new CMemoryStream();

		SetStream(m_pXref, m_pStream);

		Add("Type", "XObject");
		Add("Subtype", "Form");

		TRect oRect = pField->GetRect();

		CArrayObject* pArray = new CArrayObject();
		if (!pArray)
			return;

		Add("BBox", pArray);
		pArray->Add(0);
		pArray->Add(0);
		pArray->Add(oRect.fRight - oRect.fLeft);
		pArray->Add(oRect.fBottom - oRect.fTop);

		Add("Resources", pField->GetResourcesDict());
	}
	void CAnnotAppearanceObject::DrawSimpleText(const std::wstring& wsText, const char* sFontName, double dFontSize, double dX, double dY)
	{
		if (!m_pStream || !sFontName)
			return;

		m_pStream->WriteEscapeName("Tx");
		m_pStream->WriteStr(" BMC\012q\012");

		m_pStream->WriteStr("1 1 98 100 re\012W\012n\012");


		m_pStream->WriteStr("BT\012");

		dFontSize = std::min(1000.0, std::max(0.0, dFontSize));

		m_pStream->WriteEscapeName(sFontName);
		m_pStream->WriteChar(' ');
		m_pStream->WriteReal(dFontSize);
		m_pStream->WriteStr(" Tf\012");

		m_pStream->WriteReal(dX);
		m_pStream->WriteChar(' ');
		m_pStream->WriteReal(dY);
		m_pStream->WriteStr(" Td\012");

		std::string sText = NSFile::CUtf8Converter::GetUtf8StringFromUnicode(wsText);
		m_pStream->WriteEscapeText((BYTE*)(sText.c_str()), sText.length(), true);

		m_pStream->WriteStr(" Tj\012");

		m_pStream->WriteStr("ET\012");
		
		m_pStream->WriteStr("Q\012EMC\012");
	}


}
