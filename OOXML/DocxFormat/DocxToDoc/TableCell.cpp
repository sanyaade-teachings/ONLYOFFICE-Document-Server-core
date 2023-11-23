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

#include "TableCell.h"

namespace Docx2Doc
{
	void TableCell::SetDepth( unsigned int _depth )
	{
		this->depth = _depth;

		for ( std::list<TableCellItemWithOffset>::iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			Paragraph* paragraph = dynamic_cast<Paragraph*>(iter->tableCellItem.operator->());

			if ( paragraph != NULL )
			{
				paragraph->SetDepth( this->depth );
			}
		}
		if ( this->depth > 1 )
		{
			Paragraph* paragraph = dynamic_cast<Paragraph*>(this->textItems.back().tableCellItem.operator->());

			if ( paragraph != NULL )
			{
				const BYTE PFInnerTableCell = 1;

				paragraph->AddProperty( (short)DocFileFormat::sprmPFInnerTableCell, (void*)(&PFInnerTableCell) );
			}
		}
	}

	/*========================================================================================================*/

	unsigned int TableCell::GetDepth() const
	{
		return this->depth;
	}

	/*========================================================================================================*/

	TableCell::TableCell():
	depth(1), tableCellItemsOffset(0)
	{
	}

	/*========================================================================================================*/

	TableCell::TableCell( unsigned int _depth ):
	depth(_depth), tableCellItemsOffset(0)
	{
	}

	/*========================================================================================================*/

	TableCell::~TableCell()
	{
	}

	/*========================================================================================================*/

	TableCell::TableCell( const TableCell& tableCell ):
	depth(tableCell.depth), properties(tableCell.properties), tableCellItemsOffset(tableCell.tableCellItemsOffset)
	{
		for ( std::list<TableCellItemWithOffset>::const_iterator iter = tableCell.textItems.begin(); iter != tableCell.textItems.end(); iter++ )
		{
			this->textItems.push_back( TableCellItemWithOffset( TextItemPtr( static_cast<ITextItem*>( iter->tableCellItem->Clone() ) ), iter->tableCellItemOffset ) );
		}
	}

	/*========================================================================================================*/

	void TableCell::AddTextItem( const ITextItem& _textItem )
	{
		TextItemPtr newTextItem( static_cast<ITextItem*>( _textItem.Clone() ) );

		const BYTE PFInnerTableCell = 1;
		const BYTE PFInTable = 1;

		if ( !textItems.empty() )
		{
			Paragraph* paragraph = dynamic_cast<Paragraph*>(textItems.back().tableCellItem.operator->());

			if ( paragraph != NULL )
			{
				paragraph->RemoveProperty((short)DocFileFormat::sprmPFInnerTableCell, (void*)(&PFInnerTableCell));
			}
		}

		Paragraph* paragraph = dynamic_cast<Paragraph*>(newTextItem.operator->());

		if ( paragraph != NULL )
		{
			if ( this->depth > 1 )
			{
				paragraph->AddProperty( (short)DocFileFormat::sprmPFInnerTableCell, (void*)(&PFInnerTableCell) );
			}

			paragraph->SetDepth( this->depth );

			this->RemoveProperty( (short)DocFileFormat::sprmPFInTable, (void*)(&PFInTable) );
			this->RemoveProperty( (short)DocFileFormat::sprmPItap, (void*)(&this->depth) );
			this->RemoveProperty( (short)DocFileFormat::sprmPFInnerTableCell, (void*)(&PFInnerTableCell) );
		}
		else
		{
			this->AddProperty( (short)DocFileFormat::sprmPFInTable, (void*)(&PFInTable) );
			this->AddProperty( (short)DocFileFormat::sprmPItap, (void*)(&this->depth) );
			this->AddProperty( (short)DocFileFormat::sprmPFInnerTableCell, (void*)(&PFInnerTableCell) );
		}

		this->textItems.push_back( TableCellItemWithOffset( newTextItem, this->tableCellItemsOffset ) );
		this->tableCellItemsOffset += ( sizeof(WCHAR) * newTextItem.operator->()->GetAllText().size() );

		//!!!TODO: Add empty run, if this is a paragraph.
		//(There is issue with table content, when last item in table cell is a picture)!!!
		if ( paragraph != NULL )
		{
			paragraph->AddParagraphItem( Run() );
		}
	}

	/*========================================================================================================*/

	std::wstring TableCell::GetAllText() const
	{
		std::wstring allText;

		for ( std::list<TableCellItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += iter->tableCellItem->GetAllText();
		}

		if ( !this->textItems.empty() )
		{
			if ( typeid(*this->textItems.back().tableCellItem) == typeid(Paragraph) )
			{
				if ( this->depth > 1 )
				{
					allText[allText.size() - 1] = TextMark::ParagraphEnd;
				}
				else
				{
					allText[allText.size() - 1] = TextMark::CellOrRowMark;
				}
			}
			else
			{
				if ( this->depth > 1 )
				{
					allText += TextMark::ParagraphEnd;
				}
				else
				{
					allText += TextMark::CellOrRowMark;
				}
			}
		}

		return allText;
	}

	/*========================================================================================================*/

	TableCell::operator std::wstring() const
	{
		std::wstring allText;

		for ( std::list<TableCellItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += *(iter->tableCellItem);
		}

		return allText;
	}

	/*========================================================================================================*/

	std::vector<TextItemPtr> TableCell::GetAllParagraphsCopy() const
	{
		std::vector<TextItemPtr> allParagraphs;

		for ( std::list<TableCellItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			std::vector<TextItemPtr> textItemParagraphs = iter->tableCellItem->GetAllParagraphsCopy();

			for ( std::vector<TextItemPtr>::const_iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( TextItemPtr( static_cast<ITextItem*>( (*textItemParagraphsIter)->Clone() ) ) );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	std::vector<ITextItem*> TableCell::GetAllParagraphs()
	{
		std::vector<ITextItem*> allParagraphs;

		for ( std::list<TableCellItemWithOffset>::iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			std::vector<ITextItem*> textItemParagraphs = iter->tableCellItem->GetAllParagraphs();

			for ( std::vector<ITextItem*>::iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( *textItemParagraphsIter );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	void TableCell::AddProperty( short sprm, void* operand )
	{
		Prl prl( sprm, reinterpret_cast<BYTE*>( operand ) );
		this->properties.push_back( prl );
	}

	/*========================================================================================================*/

	void TableCell::RemoveProperty( short sprm, void* operand )
	{
		Prl prl( sprm, reinterpret_cast<BYTE*>( operand ) );
		this->properties.remove( prl );  
	}

	/*========================================================================================================*/

	void TableCell::AddProperties( const std::vector<Prl>& prls )
	{
		for ( std::vector<Prl>::const_iterator iter = prls.begin(); iter != prls.end(); iter++ )
		{
			this->properties.push_back( *iter ); 
		}
	}

	/*========================================================================================================*/

	void TableCell::RemoveAllProperties()
	{
		this->properties.clear();
	}

	/*========================================================================================================*/

	PapxInFkp TableCell::GetAllProperties() const
	{
		std::vector<Prl> prls( this->properties.begin(), this->properties.end() );
		GrpPrlAndIstd gpai( 0, prls );
		return PapxInFkp( gpai );
	}

	/*========================================================================================================*/

	unsigned int TableCell::GetAllPropertiesCount() const
	{
		return this->properties.size();
	}

	/*========================================================================================================*/

	std::vector<PapxInFkp> TableCell::GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
	{
		std::vector<PapxInFkp> allParagraphsProperties;
		unsigned int paragraphOffset = 0;

		if ( allParagraphsOffsets != NULL )
		{
			for ( std::list<TableCellItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> tableCellItemParagraphsOffsets;
				std::vector<PapxInFkp> tableCellItemParagraphsProperties = iter->tableCellItem->GetAllParagraphsProperties( &tableCellItemParagraphsOffsets );

				for ( unsigned int i = 0; i < tableCellItemParagraphsProperties.size(); i++ )
				{
					allParagraphsProperties.push_back( tableCellItemParagraphsProperties[i] );
					allParagraphsOffsets->push_back( paragraphOffset + tableCellItemParagraphsOffsets[i] );
				}

				paragraphOffset += ( sizeof(WCHAR) * iter->tableCellItem->GetAllText().size() );
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

	std::vector<Chpx> TableCell::GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<Chpx> allRunsProperties;
		unsigned int runOffset = 0;

		if ( allRunsOffsets != NULL )
		{
			for ( std::list<TableCellItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> tableCellRunsOffsets;
				std::vector<Chpx> tableCellItemRunsProperties = iter->tableCellItem->GetAllRunProperties( &tableCellRunsOffsets );

				for ( unsigned int i = 0; i < tableCellItemRunsProperties.size(); i++ )
				{
					allRunsProperties.push_back( tableCellItemRunsProperties[i] );
					allRunsOffsets->push_back( runOffset + tableCellRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->tableCellItem->GetAllText().size() );
			}
		}

		return allRunsProperties;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> TableCell::GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allRuns;

		if ( allRunsOffsets != NULL )
		{
			unsigned int runOffset = 0;

			for ( std::list<TableCellItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemRunsOffsets;
				std::vector<IParagraphItemPtr> allTextItemRuns = iter->tableCellItem->GetAllRunsCopy( &allTextItemRunsOffsets );

				for ( unsigned int i = 0; i < allTextItemRuns.size(); i++ )
				{
					allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemRuns[i]->Clone()) ) );
					allRunsOffsets->push_back( runOffset + allTextItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->tableCellItem->GetAllText().size() );
			}
		}

		return allRuns;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> TableCell::GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allParagraphItems;

		if ( allParagraphItemsOffsets != NULL )
		{
			unsigned int paragraphItemOffset = 0;

			for ( std::list<TableCellItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemParagraphItemsOffsets;
				std::vector<IParagraphItemPtr> allTextItemParagraphItems = iter->tableCellItem->GetAllParagraphItemsCopy( &allTextItemParagraphItemsOffsets );

				for ( unsigned int i = 0; i < allTextItemParagraphItems.size(); i++ )
				{
					allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemParagraphItems[i]->Clone()) ) );
					allParagraphItemsOffsets->push_back( paragraphItemOffset + allTextItemParagraphItemsOffsets[i] );
				}

				paragraphItemOffset += ( sizeof(WCHAR) * iter->tableCellItem->GetAllText().size() );
			}
		}

		return allParagraphItems;
	}
}
