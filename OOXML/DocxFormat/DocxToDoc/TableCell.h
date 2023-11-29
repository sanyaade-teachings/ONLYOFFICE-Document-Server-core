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

#include "Paragraph.h"
#include "Picture.h"
#include "Footnote.h"
#include "Endnote.h"
#include "SectionBreak.h"
#include "CSSAOperand.h"
#include "TableBordersOperand.h"
#include "TableBordersOperand80.h"
#include "TDefTableOperand.h"
#include "TableCellWidthOperand.h"
#include "TableBrcOperand.h"
#include "TableBrc80Operand.h"
#include "TLP.h"

namespace Docx2Doc
{
	class TableCell
	{
		friend class TableRow;

		struct TableCellItemWithOffset
		{
			TextItemPtr tableCellItem;
			unsigned int tableCellItemOffset;

			TableCellItemWithOffset() : tableCellItem(), tableCellItemOffset(0)
			{
			}

			TableCellItemWithOffset( const TextItemPtr& _tableCellItem, unsigned int _tableCellItemOffset ) :
				tableCellItem(_tableCellItem), tableCellItemOffset(_tableCellItemOffset)
			{
			}
		};

	private:
		std::list<TableCellItemWithOffset> textItems;
		std::list<Prl> properties;
		unsigned int depth;
		unsigned int tableCellItemsOffset;

	protected:
		void SetDepth( unsigned int _depth );
		unsigned int GetDepth() const;

	public:
		TableCell();
		explicit TableCell( unsigned int _depth );
		~TableCell();
		TableCell( const TableCell& tableCell );
		void AddTextItem( const ITextItem& _textItem );
		std::wstring GetAllText() const;
		operator std::wstring() const;
		std::vector<TextItemPtr> GetAllParagraphsCopy() const;
		std::vector<ITextItem*> GetAllParagraphs();
		void AddProperty( short sprm, void* operand );
		void AddProperties( const std::vector<Prl>& prls );
		void RemoveProperty( short sprm, void* operand );
		void RemoveAllProperties();
		PapxInFkp GetAllProperties() const;
		unsigned int GetAllPropertiesCount() const;
		std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const;
		std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const;
		std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const;
		std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const;
	};
}
