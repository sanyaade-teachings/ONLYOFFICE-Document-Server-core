/*
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

#include "Converter.h"

#include "../../../Common/OfficeFileErrorDescription.h"

#include "../../../OOXML/DocxFormat/Document.h"
#include "../../../OOXML/DocxFormat/Numbering.h"
#include "../../../OOXML/DocxFormat/Styles.h"
#include "../../../OOXML/DocxFormat/Footnote.h"
#include "../../../OOXML/DocxFormat/Endnote.h"
#include "../../../OOXML/DocxFormat/FtnEdn.h"
#include "../../../OOXML/DocxFormat/FontTable.h"
#include "../../../OOXML/DocxFormat/Logic/Table.h"
#include "../../../OOXML/DocxFormat/Logic/Sdt.h"
#include "../../../OOXML/DocxFormat/Logic/FldSimple.h"
#include "../../../OOXML/DocxFormat/Logic/Hyperlink.h"
#include "../../../OOXML/DocxFormat/Logic/ParagraphProperty.h"
#include "../../../OOXML/DocxFormat/Logic/SectionProperty.h"
#include "../../../OOXML/DocxFormat/Logic/Run.h"
#include "../../../OOXML/DocxFormat/Logic/FldChar.h"

#include "../../../MsBinaryFile/DocFile/StyleSheetDescription.h"

namespace Docx2Doc
{
	Converter::Converter()
	{
		for (size_t i = 0; i < (sizeof(DocFileFormat::StyleIdentifierMap) / sizeof(DocFileFormat::StyleIdentifierMap[0])); i++)
		{
			m_styleIdDefaultMap.insert(std::pair<std::wstring, size_t>(DocFileFormat::StyleIdentifierMap[i], i));
		}
	}

	Converter::~Converter()
	{}

	_UINT32 Converter::SaveToFile(const std::wstring & sSrcPath, const std::wstring & sDstPath, const std::wstring & sXMLOptions)
	{
		bool result = false;

		m_Docx.Read(sSrcPath);

		if (m_Docx.m_oMain.document)
		{
			// Fonts
			if (m_Docx.m_oMain.fontTable)
			{
				std::vector<OOX::CFont*> arrFonts = m_Docx.m_oMain.fontTable->m_arrFonts;

				for (size_t i = 0; i < arrFonts.size(); i++)
				{
					m_fontTableMap.insert(std::pair<std::wstring, size_t>(arrFonts[i]->m_sName, i));
				}
			}

			// Numbering
			ConvertNumbering(m_Docx.m_oMain.numbering);

			// Styles
			ConvertStyleSheet(m_Docx.m_oMain.styles);

			// Document
			ConvertDocument(m_Docx.m_oMain.document);

			// FontTable
			ConvertFontTable(m_Docx.m_oMain.fontTable);

			// Write to doc
			bool WriteInformationBlock();
			bool WriteDocument();
			bool WriteFontTable();
			bool WriteStyleSheet();
			bool WriteNumbering();
		}

		return result ? 0 : AVS_FILEUTILS_ERROR_CONVERT;
	}

	// Converting
	void Converter::ConvertNumbering(OOX::CNumbering* pNumbering)
	{
		if (pNumbering)
		{
			if (!pNumbering->m_arrNum.size() || !pNumbering->m_arrAbstractNum.size())
				return;
		}
	}

	void Converter::ConvertDocument(OOX::CDocument* pDocument)
	{
		if (pDocument)
		{
			// Convert items
			for (size_t i = 0; i < pDocument->m_arrItems.size(); i++)
			{
				// Paragraph
				if (pDocument->m_arrItems[i]->getType() == OOX::EElementType::et_w_p)
				{
					XmlUtils::CXmlNode oNode;
					oNode.FromXmlString(pDocument->m_arrItems[i]->toXML());

					OOX::Logic::CParagraph oParagraph;
					oParagraph.fromXML(oNode);

					std::wstring sId = GetStyleID(oParagraph);
				}
				// Table
				if (pDocument->m_arrItems[i]->getType() == OOX::EElementType::et_w_tbl)
				{
					int x = 1;
				}
				// Std
				if (pDocument->m_arrItems[i]->getType() == OOX::EElementType::et_w_sdt)
				{
					int x = 1;
				}
			}
		}
	}

	void Converter::ConvertStyleSheet(OOX::CStyles* pStyles)
	{
		if (pStyles)
		{
			std::vector<OOX::CStyle*> arrStyles = pStyles->m_arrStyle;
			for (size_t i = 0; i < arrStyles.size(); i++)
			{
				std::wstring sId = arrStyles[i]->m_sStyleId.get();
				int x = 1;
			}
		}
	}

	void Converter::ConvertFontTable(OOX::CFontTable* pFontTable)
	{
		if (pFontTable)
		{
			for (size_t i = 0; i < pFontTable->m_arrFonts.size(); i++)
			{
				//DocFileFormat::
			}
		}
	}

	std::wstring Converter::GetStyleID(const OOX::Logic::CParagraph& oParagraph)
	{
		std::wstring sId;

		if (oParagraph.m_oParagraphProperty->IsNoEmpty() && oParagraph.m_oParagraphProperty->m_oPStyle.IsInit())
		{
			sId = oParagraph.m_oParagraphProperty->m_oPStyle->ToString();
		}
		else
		{
			// set default, Normal
		}

		return sId;
	}

	// Write to doc
	bool Converter::WriteInformationBlock()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteDocument()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteNumbering()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteStyleSheet()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteFontTable()
	{
		bool bResult = false;
		return bResult;
	}
}
