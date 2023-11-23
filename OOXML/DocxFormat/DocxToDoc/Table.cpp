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

#include "Table.h"

namespace Docx2Doc
{
	void Table::SetDepth( unsigned int _depth )
	{
		this->depth = _depth;
	}

	/*========================================================================================================*/

	unsigned int Table::GetDepth() const
	{
		return this->depth;
	}

	/*========================================================================================================*/

	Table::Table():
	depth(1), tableRowsOffset(0)
	{
	}

	/*========================================================================================================*/

	Table::~Table()
	{
	}

	/*========================================================================================================*/

	Table::Table( const Table& table ):
	rows(table.rows), depth(table.depth), tableRowsOffset(table.tableRowsOffset)
	{
	}

	/*========================================================================================================*/

	void Table::AddRow( const TableRow& row )
	{
		TableRow newRow( row );

		const BYTE PFInTable = 1;
		const int PItap = row.GetDepth();
		const BYTE PFInnerTableCell = 1;

		newRow.AddProperty( (short)DocFileFormat::sprmPFInTable, (void*)(&PFInTable) );
		newRow.AddProperty( (short)DocFileFormat::sprmPItap, (void*)(&PItap) );

		if ( row.GetDepth() <= 1 )
		{
			const BYTE PFTtp = 1;
			newRow.AddProperty( (short)DocFileFormat::sprmPFTtp, (void*)(&PFTtp) );
		}
		else
		{
			const BYTE PFInnerTtp = 1;
			newRow.AddProperty( (short)DocFileFormat::sprmPFInnerTtp, (void*)(&PFInnerTtp) );
			newRow.AddProperty( (short)DocFileFormat::sprmPFInnerTableCell, (void*)(&PFInnerTableCell) );
		}

		this->rows.push_back( TableRowWithOffset( newRow, this->tableRowsOffset ) );
		this->tableRowsOffset += ( sizeof(WCHAR) * row.GetAllText().size() );
	}

	/*========================================================================================================*/

	std::wstring Table::GetAllText() const
	{
		std::wstring allText;

		for ( std::list<TableRowWithOffset>::const_iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
		{
			allText += iter->tableRow.GetAllText();
		}

		return allText;
	}

	/*========================================================================================================*/

	Table::operator std::wstring() const
	{
		std::wstring allText;

		for ( std::list<TableRowWithOffset>::const_iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
		{
			allText += iter->tableRow;
		}

		return allText;
	}

	/*========================================================================================================*/

	IVirtualConstructor* Table::New() const
	{
		return new Table();
	}

	/*========================================================================================================*/

	IVirtualConstructor* Table::Clone() const
	{
		return new Table( *this );
	}

	/*========================================================================================================*/

	std::vector<TextItemPtr> Table::GetAllParagraphsCopy() const
	{
		std::vector<TextItemPtr> allParagraphs;

		for ( std::list<TableRowWithOffset>::const_iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
		{
			std::vector<TextItemPtr> tableRowParagraphs = iter->tableRow.GetAllParagraphsCopy();

			for ( std::vector<TextItemPtr>::const_iterator tableRowParagraphsIter = tableRowParagraphs.begin(); tableRowParagraphsIter != tableRowParagraphs.end(); tableRowParagraphsIter++ )
			{
				allParagraphs.push_back( TextItemPtr( static_cast<ITextItem*>( (*tableRowParagraphsIter)->Clone() ) ) );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	std::vector<ITextItem*> Table::GetAllParagraphs()
	{
		std::vector<ITextItem*> allParagraphs;

		for ( std::list<TableRowWithOffset>::iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
		{
			std::vector<ITextItem*> tableRowParagraphs = iter->tableRow.GetAllParagraphs();

			for ( std::vector<ITextItem*>::iterator tableRowParagraphsIter = tableRowParagraphs.begin(); tableRowParagraphsIter != tableRowParagraphs.end(); tableRowParagraphsIter++ )
			{
				allParagraphs.push_back( *tableRowParagraphsIter );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> Table::GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allRuns;

		if ( allRunsOffsets != NULL )
		{
			unsigned int runOffset = 0;

			for ( std::list<TableRowWithOffset>::const_iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
			{
				std::vector<unsigned int> allRowRunsOffsets;
				std::vector<IParagraphItemPtr> allRowRuns = iter->tableRow.GetAllRunsCopy( &allRowRunsOffsets );

				for ( unsigned int i = 0; i < allRowRuns.size(); i++ )
				{
					allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allRowRuns[i]->Clone()) ) );
					allRunsOffsets->push_back( runOffset + allRowRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->tableRow.GetAllText().size() );
			}
		}

		return allRuns;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> Table::GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allParagraphItems;

		if ( allParagraphItemsOffsets != NULL )
		{
			unsigned int paragraphItemOffset = 0;

			for ( std::list<TableRowWithOffset>::const_iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
			{
				std::vector<unsigned int> allRowParagraphItemsOffsets;
				std::vector<IParagraphItemPtr> allRowParagraphItems = iter->tableRow.GetAllParagraphItemsCopy( &allRowParagraphItemsOffsets );

				for ( unsigned int i = 0; i < allRowParagraphItems.size(); i++ )
				{
					allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allRowParagraphItems[i]->Clone()) ) );
					allParagraphItemsOffsets->push_back( paragraphItemOffset + allRowParagraphItemsOffsets[i] );
				}

				paragraphItemOffset += ( sizeof(WCHAR) * iter->tableRow.GetAllText().size() );
			}
		}

		return allParagraphItems;
	}

	/*========================================================================================================*/

	std::vector<PapxInFkp> Table::GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
	{
		std::vector<PapxInFkp> allParagraphsProperties;
		unsigned int paragraphOffset = 0;

		if ( allParagraphsOffsets != NULL )
		{
			for ( std::list<TableRowWithOffset>::const_iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
			{
				std::vector<unsigned int> tableRowParagraphsOffsets;
				std::vector<PapxInFkp> tableRowParagraphsProperties = iter->tableRow.GetAllParagraphsProperties( &tableRowParagraphsOffsets );

				for ( unsigned int i = 0; i < tableRowParagraphsProperties.size(); i++ )
				{
					allParagraphsProperties.push_back( tableRowParagraphsProperties[i] );
					allParagraphsOffsets->push_back( paragraphOffset + tableRowParagraphsOffsets[i] );
				}

				paragraphOffset += ( sizeof(WCHAR) * iter->tableRow.GetAllText().size() );
			}
		}

		return allParagraphsProperties;
	}

	/*========================================================================================================*/

	std::vector<Chpx> Table::GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<Chpx> allRunsProperties;
		unsigned int runOffset = 0;

		if ( allRunsOffsets != NULL )
		{
			for ( std::list<TableRowWithOffset>::const_iterator iter = this->rows.begin(); iter != this->rows.end(); iter++ )
			{
				std::vector<unsigned int> tableRowRunsOffsets;
				std::vector<Chpx> tableRowRunsProperties = iter->tableRow.GetAllRunProperties( &tableRowRunsOffsets );

				for ( unsigned int i = 0; i < tableRowRunsProperties.size(); i++ )
				{
					allRunsProperties.push_back( tableRowRunsProperties[i] );
					allRunsOffsets->push_back( runOffset + tableRowRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->tableRow.GetAllText().size() );
			}
		}

		return allRunsProperties;
	}
}
