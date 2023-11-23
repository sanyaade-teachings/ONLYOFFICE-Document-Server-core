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

#include "Footnote.h"

namespace Docx2Doc
{
	Footnote::Footnote( short _aFtnIdx ) : footnoteItemsOffset(0), aFtnIdx(_aFtnIdx)
	{
	}

	Footnote::Footnote( const Footnote& _footnote ) : footnoteItemsOffset(_footnote.footnoteItemsOffset), aFtnIdx(_footnote.aFtnIdx)
	{
		for ( std::list<FootnoteItemWithOffset>::const_iterator iter = _footnote.textItems.begin(); iter != _footnote.textItems.end(); iter++ )
		{
			this->textItems.push_back( FootnoteItemWithOffset( TextItemPtr( static_cast<ITextItem*>( iter->footnoteItem->Clone() ) ), iter->footnoteItemOffset ) );
		}
	}

	void Footnote::AddTextItem( const ITextItem& _textItem )
	{
		ITextItem* textItem = static_cast<ITextItem*>( _textItem.Clone() );

		if ( textItem != NULL )
		{
			this->textItems.push_back( FootnoteItemWithOffset( TextItemPtr( textItem ), this->footnoteItemsOffset ) );
			this->footnoteItemsOffset += ( sizeof(WCHAR) * textItem->GetAllText().size() );
		}
	}

	short Footnote::GetIndex() const
	{
		return this->aFtnIdx;
	}

	Footnote::~Footnote()
	{
	}

	std::wstring Footnote::GetAllText() const
	{
		std::wstring allText;

		for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += iter->footnoteItem->GetAllText();
		}

		return allText;
	}

	Footnote::operator std::wstring() const
	{
		std::wstring allText;

		for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += *(iter->footnoteItem);
		}

		return allText;   
	}

	std::vector<TextItemPtr> Footnote::GetAllParagraphsCopy() const
	{
		std::vector<TextItemPtr> allParagraphs;

		for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			std::vector<TextItemPtr> textItemParagraphs = iter->footnoteItem->GetAllParagraphsCopy();

			for ( std::vector<TextItemPtr>::const_iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( TextItemPtr( static_cast<ITextItem*>( (*textItemParagraphsIter)->Clone() ) ) );
			}
		}

		return allParagraphs;
	}

	std::vector<ITextItem*> Footnote::GetAllParagraphs()
	{
		std::vector<ITextItem*> allParagraphs;

		for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			ITextItem* item = (ITextItem*)iter->footnoteItem.operator->();

			std::vector<ITextItem*> textItemParagraphs = item->GetAllParagraphs();

			for ( std::vector<ITextItem*>::iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( *textItemParagraphsIter );
			}
		}

		return allParagraphs;
	}

	std::vector<PapxInFkp> Footnote::GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
	{
		std::vector<PapxInFkp> allParagraphsProperties;
		unsigned int paragraphOffset = 0;

		if ( allParagraphsOffsets != NULL )
		{
			for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> footnoteItemParagraphsOffsets;
				std::vector<PapxInFkp> footnoteItemParagraphsProperties = iter->footnoteItem->GetAllParagraphsProperties( &footnoteItemParagraphsOffsets );

				for ( unsigned int i = 0; i < footnoteItemParagraphsProperties.size(); i++ )
				{
					allParagraphsProperties.push_back( footnoteItemParagraphsProperties[i] );
					allParagraphsOffsets->push_back( paragraphOffset + footnoteItemParagraphsOffsets[i] );
				}

				paragraphOffset += ( sizeof(WCHAR) * iter->footnoteItem->GetAllText().size() );
			}
		}

		return allParagraphsProperties;
	}

	std::vector<Chpx> Footnote::GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<Chpx> allRunsProperties;
		unsigned int runOffset = 0;

		if ( allRunsOffsets != NULL )
		{
			for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> footnoteItemRunsOffsets;
				std::vector<Chpx> footnoteItemRunsProperties = iter->footnoteItem->GetAllRunProperties( &footnoteItemRunsOffsets );

				for ( unsigned int i = 0; i < footnoteItemRunsProperties.size(); i++ )
				{
					allRunsProperties.push_back( footnoteItemRunsProperties[i] );
					allRunsOffsets->push_back( runOffset + footnoteItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->footnoteItem->GetAllText().size() );
			}
		}

		return allRunsProperties;
	}

	std::vector<IParagraphItemPtr> Footnote::GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allRuns;

		if ( allRunsOffsets != NULL )
		{
			unsigned int runOffset = 0;

			for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemRunsOffsets;
				std::vector<IParagraphItemPtr> allTextItemRuns = iter->footnoteItem->GetAllRunsCopy( &allTextItemRunsOffsets );

				for ( unsigned int i = 0; i < allTextItemRuns.size(); i++ )
				{
					allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemRuns[i]->Clone()) ) );
					allRunsOffsets->push_back( runOffset + allTextItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->footnoteItem->GetAllText().size() );
			}
		}

		return allRuns;
	}

	std::vector<IParagraphItemPtr> Footnote::GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allParagraphItems;

		if ( allParagraphItemsOffsets != NULL )
		{
			unsigned int textItemOffset = 0;

			for ( std::list<FootnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemParagraphItemsOffsets;
				std::vector<IParagraphItemPtr> allTextItemParagraphItems = iter->footnoteItem->GetAllParagraphItemsCopy( &allTextItemParagraphItemsOffsets );

				for ( unsigned int i = 0; i < allTextItemParagraphItems.size(); i++ )
				{
					allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemParagraphItems[i]->Clone()) ) );
					allParagraphItemsOffsets->push_back( textItemOffset + allTextItemParagraphItemsOffsets[i] );
				}

				textItemOffset += ( sizeof(WCHAR) * iter->footnoteItem->GetAllText().size() );
			}
		}

		return allParagraphItems;
	}

	IVirtualConstructor* Footnote::New() const
	{
		return new Footnote();
	}

	IVirtualConstructor* Footnote::Clone() const
	{
		return new Footnote( *this );
	}
}
