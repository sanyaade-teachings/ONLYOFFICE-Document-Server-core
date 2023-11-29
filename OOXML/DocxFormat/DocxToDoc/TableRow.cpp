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

#include "TableRow.h"

namespace Docx2Doc
{
	void TableRow::SetDepth( unsigned int _depth )
	{
		this->depth = _depth;

		const BYTE PFInTable = 1;
		const int PItap = this->depth;
		const BYTE PFInnerTableCell = 1;

		this->AddProperty( (short)DocFileFormat::sprmPFInTable, (void*)(&PFInTable) );
		this->AddProperty( (short)DocFileFormat::sprmPItap, (void*)(&PItap) );

		if ( this->depth <= 1 )
		{
			const BYTE PFTtp = 1;
			this->AddProperty( (short)DocFileFormat::sprmPFTtp, (void*)(&PFTtp) );
		}
		else
		{
			const BYTE PFInnerTtp = 1;
			this->AddProperty( (short)DocFileFormat::sprmPFInnerTtp, (void*)(&PFInnerTtp) );
			this->AddProperty( (short)DocFileFormat::sprmPFInnerTableCell, (void*)(&PFInnerTableCell) );
		}
	}

	/*========================================================================================================*/

	unsigned int TableRow::GetDepth() const
	{
		return this->depth;
	}

	/*========================================================================================================*/

	TableRow::TableRow():
		depth(1), tableCellsOffset(0)
	{
	}

	/*========================================================================================================*/

	TableRow::TableRow( unsigned int _depth ):
		depth(_depth), tableCellsOffset(0)
	{
	}

	/*========================================================================================================*/

	TableRow::~TableRow()
	{
	}

	/*========================================================================================================*/

	TableRow::TableRow( const TableRow& tableRow ):
		cells(tableRow.cells), properties(tableRow.properties), depth(tableRow.depth), tableCellsOffset(tableRow.tableCellsOffset)
	{
	}

	/*========================================================================================================*/

	void TableRow::AddCell( const TableCell& cell )
	{
		this->cells.push_back( TableCellWithOffset( cell, this->tableCellsOffset ) );
		this->tableCellsOffset += ( sizeof(WCHAR) * cell.GetAllText().size() );
	}

	/*========================================================================================================*/

	std::wstring TableRow::GetAllText() const
	{
		std::wstring allText;

		for ( std::list<TableCellWithOffset>::const_iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
		{
			allText += iter->tableCell.GetAllText();
		}

		if ( this->depth > 1 )
		{
			allText += TextMark::ParagraphEnd;
		}
		else
		{
			allText += TextMark::CellOrRowMark;
		}

		return allText;
	}

	/*========================================================================================================*/

	TableRow::operator std::wstring() const
	{
		std::wstring allText;

		for ( std::list<TableCellWithOffset>::const_iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
		{
			allText += iter->tableCell;
		}

		return allText;
	}

	/*========================================================================================================*/

	std::vector<TextItemPtr> TableRow::GetAllParagraphsCopy() const
	{
		std::vector<TextItemPtr> allParagraphs;

		for ( std::list<TableCellWithOffset>::const_iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
		{
			std::vector<TextItemPtr> tableCellParagraphs = iter->tableCell.GetAllParagraphsCopy();

			for ( std::vector<TextItemPtr>::const_iterator tableCellParagraphsIter = tableCellParagraphs.begin(); tableCellParagraphsIter != tableCellParagraphs.end(); tableCellParagraphsIter++ )
			{
				allParagraphs.push_back( TextItemPtr( static_cast<ITextItem*>( (*tableCellParagraphsIter)->Clone() ) ) );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	std::vector<ITextItem*> TableRow::GetAllParagraphs()
	{
		std::vector<ITextItem*> allParagraphs;

		for ( std::list<TableCellWithOffset>::iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
		{
			std::vector<ITextItem*> tableCellParagraphs = iter->tableCell.GetAllParagraphs();

			for ( std::vector<ITextItem*>::iterator tableCellParagraphsIter = tableCellParagraphs.begin(); tableCellParagraphsIter != tableCellParagraphs.end(); tableCellParagraphsIter++ )
			{
				allParagraphs.push_back( *tableCellParagraphsIter );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	void TableRow::AddProperty( short sprm, void* operand )
	{
		Prl prl( sprm, reinterpret_cast<BYTE*>( operand ) );
		this->properties.push_back( prl );
	}

	/*========================================================================================================*/

	void TableRow::AddProperties( const std::vector<Prl>& prls )
	{
		for ( std::vector<Prl>::const_iterator iter = prls.begin(); iter != prls.end(); iter++ )
		{
			this->properties.push_back( *iter );
		}
	}

	/*========================================================================================================*/

	void TableRow::RemoveProperty( short sprm, void* operand )
	{
		Prl prl( sprm, reinterpret_cast<BYTE*>( operand ) );
		this->properties.remove( prl );
	}

	/*========================================================================================================*/

	void TableRow::RemoveAllProperties()
	{
		this->properties.clear();
	}

	/*========================================================================================================*/

	PapxInFkp TableRow::GetAllProperties() const
	{
		std::vector<Prl> prls( this->properties.begin(), this->properties.end() );
		GrpPrlAndIstd gpai( 0, prls );
		return PapxInFkp( gpai );
	}

	/*========================================================================================================*/

	unsigned int TableRow::GetAllPropertiesCount() const
	{
		return this->properties.size();
	}

	/*========================================================================================================*/

	std::vector<PapxInFkp> TableRow::GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
	{
		std::vector<PapxInFkp> allParagraphsProperties;
		unsigned int paragraphOffset = 0;

		if ( allParagraphsOffsets != NULL )
		{
			for ( std::list<TableCellWithOffset>::const_iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
			{
				std::vector<unsigned int> tableCellParagraphsOffsets;
				std::vector<PapxInFkp> tableCellParagraphsProperties = iter->tableCell.GetAllParagraphsProperties( &tableCellParagraphsOffsets );

				for ( unsigned int i = 0; i < tableCellParagraphsProperties.size(); i++ )
				{
					allParagraphsProperties.push_back( tableCellParagraphsProperties[i] );
					allParagraphsOffsets->push_back( paragraphOffset + tableCellParagraphsOffsets[i] );
				}

				paragraphOffset += ( sizeof(WCHAR) * iter->tableCell.GetAllText().size() );
			}

			if ( !this->properties.empty() )
			{
				allParagraphsProperties.push_back( this->GetAllProperties() );
				allParagraphsOffsets->push_back( paragraphOffset );
			}
		}

		return allParagraphsProperties;
	}

	/*========================================================================================================*/

	std::vector<Chpx> TableRow::GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<Chpx> allRunsProperties;
		unsigned int runOffset = 0;

		if ( allRunsOffsets != NULL )
		{
			for ( std::list<TableCellWithOffset>::const_iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
			{
				std::vector<unsigned int> tableCellRunsOffsets;
				std::vector<Chpx> tableCellRunsProperties = iter->tableCell.GetAllRunProperties( &tableCellRunsOffsets );

				for ( unsigned int i = 0; i < tableCellRunsProperties.size(); i++ )
				{
					allRunsProperties.push_back( tableCellRunsProperties[i] );
					allRunsOffsets->push_back( runOffset + tableCellRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->tableCell.GetAllText().size() );
			}
		}

		return allRunsProperties;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> TableRow::GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allRuns;

		if ( allRunsOffsets != NULL )
		{
			unsigned int runOffset = 0;

			for ( std::list<TableCellWithOffset>::const_iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
			{
				std::vector<unsigned int> allCellRunsOffsets;
				std::vector<IParagraphItemPtr> allCellRuns = iter->tableCell.GetAllRunsCopy( &allCellRunsOffsets );

				for ( unsigned int i = 0; i < allCellRuns.size(); i++ )
				{
					allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allCellRuns[i]->Clone()) ) );
					allRunsOffsets->push_back( runOffset + allCellRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->tableCell.GetAllText().size() );
			}
		}

		return allRuns;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> TableRow::GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allParagraphItems;

		if ( allParagraphItemsOffsets != NULL )
		{
			unsigned int paragraphItemOffset = 0;

			for ( std::list<TableCellWithOffset>::const_iterator iter = this->cells.begin(); iter != this->cells.end(); iter++ )
			{
				std::vector<unsigned int> allCellParagraphItemsOffsets;
				std::vector<IParagraphItemPtr> allCellParagraphItems = iter->tableCell.GetAllParagraphItemsCopy( &allCellParagraphItemsOffsets );

				for ( unsigned int i = 0; i < allCellParagraphItems.size(); i++ )
				{
					allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allCellParagraphItems[i]->Clone()) ) );
					allParagraphItemsOffsets->push_back( paragraphItemOffset + allCellParagraphItemsOffsets[i] );
				}

				paragraphItemOffset += ( sizeof(WCHAR) * iter->tableCell.GetAllText().size() );
			}
		}

		return allParagraphItems;
	}
}
