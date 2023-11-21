
#include "Header.h"

namespace Docx2Doc
{
	Header::Header()
	{
		headerItemsOffset	=	0;

		Paragraph paragraph;
		paragraph.AddParagraphItem( Run() );
		this->textItems.push_back( HeaderItemWithOffset( TextItemPtr( static_cast<ITextItem*>(paragraph.Clone()) ), this->headerItemsOffset ) );
		this->headerItemsOffset += ( sizeof(WCHAR) * paragraph.GetAllText().size() );
	}

	/*========================================================================================================*/

	Header::Header( const Header& _header ):
	headerItemsOffset(_header.headerItemsOffset)
	{
		for ( std::list<HeaderItemWithOffset>::const_iterator iter = _header.textItems.begin(); iter != _header.textItems.end(); iter++ )
		{
			this->textItems.push_back( HeaderItemWithOffset( TextItemPtr( static_cast<ITextItem*>( iter->headerItem->Clone() ) ), iter->headerItemOffset ) );
		}
	}

	/*========================================================================================================*/

	void Header::AddTextItem( const ITextItem& _textItem )
	{
		ITextItem* textItem = static_cast<ITextItem*>( _textItem.Clone() );

		if ( !this->textItems.empty() )
		{
			std::list<HeaderItemWithOffset>::iterator iter = this->textItems.begin();

			for ( unsigned int i = 0; i < ( this->textItems.size() - 1 ); i++, iter++ );

			this->textItems.erase( iter );

			this->headerItemsOffset -= sizeof(WCHAR);
		}

		if ( textItem != NULL )
		{
			this->textItems.push_back( HeaderItemWithOffset( TextItemPtr( textItem ), this->headerItemsOffset ) );
			this->headerItemsOffset += ( sizeof(WCHAR) * textItem->GetAllText().size() );
			Paragraph paragraph;
			paragraph.AddParagraphItem( Run() );
			this->textItems.push_back( HeaderItemWithOffset( TextItemPtr( static_cast<ITextItem*>(paragraph.Clone()) ), this->headerItemsOffset ) );
			this->headerItemsOffset += ( sizeof(WCHAR) * paragraph.GetAllText().size() );
		}
	}

	/*========================================================================================================*/

	Header::~Header()
	{
	}

	/*========================================================================================================*/

	std::wstring Header::GetAllText() const
	{
		std::wstring allText;

		for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += iter->headerItem->GetAllText();
		}

		return allText;
	}

	/*========================================================================================================*/

	Header::operator std::wstring() const
	{
		std::wstring allText;

		for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += *(iter->headerItem);
		}

		return allText;   
	}

	/*========================================================================================================*/

	std::vector<TextItemPtr> Header::GetAllParagraphsCopy() const
	{
		std::vector<TextItemPtr> allParagraphs;

		for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			std::vector<TextItemPtr> textItemParagraphs = iter->headerItem->GetAllParagraphsCopy();

			for ( std::vector<TextItemPtr>::const_iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( TextItemPtr( static_cast<ITextItem*>( (*textItemParagraphsIter)->Clone() ) ) );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	std::vector<ITextItem*> Header::GetAllParagraphs()
	{
		std::vector<ITextItem*> allParagraphs;

		for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			ITextItem* item = (ITextItem*)iter->headerItem.operator->();
			std::vector<ITextItem*> textItemParagraphs = item->GetAllParagraphs();

			for ( std::vector<ITextItem*>::iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( *textItemParagraphsIter );
			}
		}

		return allParagraphs;
	}

	/*========================================================================================================*/

	std::vector<PapxInFkp> Header::GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
	{
		std::vector<PapxInFkp> allParagraphsProperties;
		unsigned int paragraphOffset = 0;

		if ( allParagraphsOffsets != NULL )
		{
			for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> headerItemParagraphsOffsets;
				std::vector<PapxInFkp> headerItemParagraphsProperties = iter->headerItem->GetAllParagraphsProperties( &headerItemParagraphsOffsets );

				for ( unsigned int i = 0; i < headerItemParagraphsProperties.size(); i++ )
				{
					allParagraphsProperties.push_back( headerItemParagraphsProperties[i] );
					allParagraphsOffsets->push_back( paragraphOffset + headerItemParagraphsOffsets[i] );
				}

				paragraphOffset += ( sizeof(WCHAR) * iter->headerItem->GetAllText().size() );
			}
		}

		return allParagraphsProperties;
	}

	/*========================================================================================================*/

	std::vector<Chpx> Header::GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<Chpx> allRunsProperties;
		unsigned int runOffset = 0;

		if ( allRunsOffsets != NULL )
		{
			for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> headerItemRunsOffsets;
				std::vector<Chpx> headerItemRunsProperties = iter->headerItem->GetAllRunProperties( &headerItemRunsOffsets );

				for ( unsigned int i = 0; i < headerItemRunsProperties.size(); i++ )
				{
					allRunsProperties.push_back( headerItemRunsProperties[i] );
					allRunsOffsets->push_back( runOffset + headerItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->headerItem->GetAllText().size() );
			}
		}

		return allRunsProperties;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> Header::GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allRuns;

		if ( allRunsOffsets != NULL )
		{
			unsigned int runOffset = 0;

			for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemRunsOffsets;
				std::vector<IParagraphItemPtr> allTextItemRuns = iter->headerItem->GetAllRunsCopy( &allTextItemRunsOffsets );

				for ( unsigned int i = 0; i < allTextItemRuns.size(); i++ )
				{
					allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemRuns[i]->Clone()) ) );
					allRunsOffsets->push_back( runOffset + allTextItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->headerItem->GetAllText().size() );
			}
		}

		return allRuns;
	}

	/*========================================================================================================*/

	std::vector<IParagraphItemPtr> Header::GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allParagraphItems;

		if ( allParagraphItemsOffsets != NULL )
		{
			unsigned int textItemOffset = 0;

			for ( std::list<HeaderItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemParagraphItemsOffsets;
				std::vector<IParagraphItemPtr> allTextItemParagraphItems = iter->headerItem->GetAllParagraphItemsCopy( &allTextItemParagraphItemsOffsets );

				for ( unsigned int i = 0; i < allTextItemParagraphItems.size(); i++ )
				{
					allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemParagraphItems[i]->Clone()) ) );
					allParagraphItemsOffsets->push_back( textItemOffset + allTextItemParagraphItemsOffsets[i] );
				}

				textItemOffset += ( sizeof(WCHAR) * iter->headerItem->GetAllText().size() );
			}
		}

		return allParagraphItems;
	}

	/*========================================================================================================*/

	IVirtualConstructor* Header::New() const
	{
		return new Header();
	}

	/*========================================================================================================*/

	IVirtualConstructor* Header::Clone() const
	{
		return new Header( *this );
	}
}
