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

#pragma once

#include <map>
#include <string>

#include "Defines.h"
#include "../../../DesktopEditor/common/ASCVariant.h"
#include "../../../OOXML/DocxFormat/Docx.h"

#include "../../../OOXML/DocxFormat/Logic/Paragraph.h"

namespace Docx2Doc
{
	class Converter
	{
	private:
		OOX::CDocx m_Docx;

		std::map<std::wstring, size_t> m_fontTableMap;
		std::vector<std::wstring> m_arrInternalFonts;

		std::map<std::wstring, size_t> m_styleIdDefaultMap;
		std::map<std::wstring, size_t> m_styleSheetMap;

	public:
		Converter();
		~Converter();

		_UINT32 SaveToFile(const std::wstring & sSrcPath, const std::wstring & sDstPath, const std::wstring & sXMLOptions);

	private:
		void ConvertDocument(OOX::CDocument* pDocument);
		void ConvertNumbering(OOX::CNumbering* pNumbering);
		void ConvertStyleSheet(OOX::CStyles* pStyles);
		void ConvertFontTable(OOX::CFontTable* pFontTable);

		std::wstring GetStyleID(const OOX::Logic::CParagraph& oParagraph);

		// Write to doc
		bool WriteInformationBlock ();
		bool WriteDocument();
		bool WriteNumbering();
		bool WriteStyleSheet();
		bool WriteFontTable();
	};
}
