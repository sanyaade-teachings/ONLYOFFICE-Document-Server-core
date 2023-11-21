
#include "Endnote.h"

namespace Docx2Doc
{
	Endnote::Endnote( short _aFtnIdx ) : endnoteItemsOffset(0), aFtnIdx(_aFtnIdx)
	{
	}

	Endnote::Endnote( const Endnote& _endnote ) : endnoteItemsOffset(_endnote.endnoteItemsOffset), aFtnIdx(_endnote.aFtnIdx)
	{
		for ( std::list<EndnoteItemWithOffset>::const_iterator iter = _endnote.textItems.begin(); iter != _endnote.textItems.end(); iter++ )
		{
			this->textItems.push_back( EndnoteItemWithOffset( TextItemPtr( static_cast<ITextItem*>( iter->endnoteItem->Clone() ) ), iter->endnoteItemOffset ) );
		}
	}

	void Endnote::AddTextItem( const ITextItem& _textItem )
	{
		ITextItem* textItem = static_cast<ITextItem*>( _textItem.Clone() );

		if ( textItem != NULL )
		{
			this->textItems.push_back( EndnoteItemWithOffset( TextItemPtr( textItem ), this->endnoteItemsOffset ) );
			this->endnoteItemsOffset += ( sizeof(WCHAR) * textItem->GetAllText().size() );
		}
	}

	short Endnote::GetIndex() const
	{
		return this->aFtnIdx;
	}

	Endnote::~Endnote()
	{
	}

	std::wstring Endnote::GetAllText() const
	{
		std::wstring allText;

		for ( std::list<EndnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += iter->endnoteItem->GetAllText();
		}

		return allText;
	}

	Endnote::operator std::wstring() const
	{
		std::wstring allText;

		for ( std::list<EndnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += *(iter->endnoteItem);
		}

		return allText;   
	}

	std::vector<TextItemPtr> Endnote::GetAllParagraphsCopy() const
	{
		std::vector<TextItemPtr> allParagraphs;

		for ( std::list<EndnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			std::vector<TextItemPtr> textItemParagraphs = iter->endnoteItem->GetAllParagraphsCopy();

			for ( std::vector<TextItemPtr>::const_iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( TextItemPtr( static_cast<ITextItem*>( (*textItemParagraphsIter)->Clone() ) ) );
			}
		}

		return allParagraphs;
	}

	std::vector<ITextItem*> Endnote::GetAllParagraphs()
	{
		std::vector<ITextItem*> allParagraphs;

		for (std::list<EndnoteItemWithOffset>::iterator iter = textItems.begin(); iter != textItems.end(); ++iter)
		{
			std::vector<ITextItem*> textItemParagraphs = iter->endnoteItem->GetAllParagraphs();

			for ( std::vector<ITextItem*>::iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( *textItemParagraphsIter );
			}
		}

		return allParagraphs;
	}

	std::vector<PapxInFkp> Endnote::GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
	{
		std::vector<PapxInFkp> allParagraphsProperties;
		unsigned int paragraphOffset = 0;

		if ( allParagraphsOffsets != NULL )
		{
			for ( std::list<EndnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> endnoteItemParagraphsOffsets;
				std::vector<PapxInFkp> endnoteItemParagraphsProperties = iter->endnoteItem->GetAllParagraphsProperties( &endnoteItemParagraphsOffsets );

				for ( unsigned int i = 0; i < endnoteItemParagraphsProperties.size(); i++ )
				{
					allParagraphsProperties.push_back( endnoteItemParagraphsProperties[i] );
					allParagraphsOffsets->push_back( paragraphOffset + endnoteItemParagraphsOffsets[i] );
				}

				paragraphOffset += ( sizeof(WCHAR) * iter->endnoteItem->GetAllText().size() );
			}
		}

		return allParagraphsProperties;
	}

	std::vector<Chpx> Endnote::GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<Chpx> allRunsProperties;
		unsigned int runOffset = 0;

		if ( allRunsOffsets != NULL )
		{
			for ( std::list<EndnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> endnoteItemRunsOffsets;
				std::vector<Chpx> endnoteItemRunsProperties = iter->endnoteItem->GetAllRunProperties( &endnoteItemRunsOffsets );

				for ( unsigned int i = 0; i < endnoteItemRunsProperties.size(); i++ )
				{
					allRunsProperties.push_back( endnoteItemRunsProperties[i] );
					allRunsOffsets->push_back( runOffset + endnoteItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->endnoteItem->GetAllText().size() );
			}
		}

		return allRunsProperties;
	}

	std::vector<IParagraphItemPtr> Endnote::GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allRuns;

		if ( allRunsOffsets != NULL )
		{
			unsigned int runOffset = 0;

			for ( std::list<EndnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemRunsOffsets;
				std::vector<IParagraphItemPtr> allTextItemRuns = iter->endnoteItem->GetAllRunsCopy( &allTextItemRunsOffsets );

				for ( unsigned int i = 0; i < allTextItemRuns.size(); i++ )
				{
					allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemRuns[i]->Clone()) ) );
					allRunsOffsets->push_back( runOffset + allTextItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->endnoteItem->GetAllText().size() );
			}
		}

		return allRuns;
	}

	std::vector<IParagraphItemPtr> Endnote::GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allParagraphItems;

		if ( allParagraphItemsOffsets != NULL )
		{
			unsigned int textItemOffset = 0;

			for ( std::list<EndnoteItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemParagraphItemsOffsets;
				std::vector<IParagraphItemPtr> allTextItemParagraphItems = iter->endnoteItem->GetAllParagraphItemsCopy( &allTextItemParagraphItemsOffsets );

				for ( unsigned int i = 0; i < allTextItemParagraphItems.size(); i++ )
				{
					allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemParagraphItems[i]->Clone()) ) );
					allParagraphItemsOffsets->push_back( textItemOffset + allTextItemParagraphItemsOffsets[i] );
				}

				textItemOffset += ( sizeof(WCHAR) * iter->endnoteItem->GetAllText().size() );
			}
		}

		return allParagraphItems;
	}

	IVirtualConstructor* Endnote::New() const
	{
		return new Endnote();
	}

	IVirtualConstructor* Endnote::Clone() const
	{
		return new Endnote(*this);
	}
}
