
#include "Footer.h"

namespace Docx2Doc
{
	Footer::Footer() : footerItemsOffset(0)
	{
		Paragraph paragraph;
		paragraph.AddParagraphItem( Run() );
		this->textItems.push_back( FooterItemWithOffset( TextItemPtr( static_cast<ITextItem*>(paragraph.Clone()) ), this->footerItemsOffset ) );
		this->footerItemsOffset += ( sizeof(WCHAR) * paragraph.GetAllText().size() );
	}

	Footer::Footer( const Footer& _footer ) : footerItemsOffset(_footer.footerItemsOffset)
	{
		for ( std::list<FooterItemWithOffset>::const_iterator iter = _footer.textItems.begin(); iter != _footer.textItems.end(); iter++ )
		{
			this->textItems.push_back( FooterItemWithOffset( TextItemPtr( static_cast<ITextItem*>( iter->footerItem->Clone() ) ), iter->footerItemOffset ) );
		}
	}

	void Footer::AddTextItem( const ITextItem& _textItem )
	{
		ITextItem* textItem = static_cast<ITextItem*>( _textItem.Clone() );

		if ( !this->textItems.empty() )
		{
			std::list<FooterItemWithOffset>::iterator iter = this->textItems.begin();

			for ( unsigned int i = 0; i < ( this->textItems.size() - 1 ); i++, iter++ );

			this->textItems.erase( iter );

			this->footerItemsOffset -= sizeof(WCHAR);
		}

		if ( textItem != NULL )
		{
			this->textItems.push_back( FooterItemWithOffset( TextItemPtr( textItem ), this->footerItemsOffset ) );
			this->footerItemsOffset += ( sizeof(WCHAR) * textItem->GetAllText().size() );
			Paragraph paragraph;
			paragraph.AddParagraphItem( Run() );
			this->textItems.push_back( FooterItemWithOffset( TextItemPtr( static_cast<ITextItem*>(paragraph.Clone()) ), this->footerItemsOffset ) );
			this->footerItemsOffset += ( sizeof(WCHAR) * paragraph.GetAllText().size() );
		}
	}

	Footer::~Footer()
	{
	}

	std::wstring Footer::GetAllText() const
	{
		std::wstring allText;

		for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += iter->footerItem->GetAllText();
		}

		return allText;
	}

	Footer::operator std::wstring() const
	{
		std::wstring allText;

		for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			allText += *(iter->footerItem);
		}

		return allText;   
	}

	std::vector<TextItemPtr> Footer::GetAllParagraphsCopy() const
	{
		std::vector<TextItemPtr> allParagraphs;

		for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			std::vector<TextItemPtr> textItemParagraphs = iter->footerItem->GetAllParagraphsCopy();

			for ( std::vector<TextItemPtr>::const_iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( TextItemPtr( static_cast<ITextItem*>( (*textItemParagraphsIter)->Clone() ) ) );
			}
		}

		return allParagraphs;
	}

	std::vector<ITextItem*> Footer::GetAllParagraphs()
	{
		std::vector<ITextItem*> allParagraphs;

		for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
		{
			ITextItem* item = (ITextItem*)iter->footerItem.operator->();

			std::vector<ITextItem*> textItemParagraphs = item->GetAllParagraphs();

			for ( std::vector<ITextItem*>::iterator textItemParagraphsIter = textItemParagraphs.begin(); textItemParagraphsIter != textItemParagraphs.end(); textItemParagraphsIter++ )
			{
				allParagraphs.push_back( *textItemParagraphsIter );
			}
		}

		return allParagraphs;
	}

	std::vector<PapxInFkp> Footer::GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
	{
		std::vector<PapxInFkp> allParagraphsProperties;
		unsigned int paragraphOffset = 0;

		if ( allParagraphsOffsets != NULL )
		{
			for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> footerItemParagraphsOffsets;
				std::vector<PapxInFkp> footerItemParagraphsProperties = iter->footerItem->GetAllParagraphsProperties( &footerItemParagraphsOffsets );

				for ( unsigned int i = 0; i < footerItemParagraphsProperties.size(); i++ )
				{
					allParagraphsProperties.push_back( footerItemParagraphsProperties[i] );
					allParagraphsOffsets->push_back( paragraphOffset + footerItemParagraphsOffsets[i] );
				}

				paragraphOffset += ( sizeof(WCHAR) * iter->footerItem->GetAllText().size() );
			}
		}

		return allParagraphsProperties;
	}

	std::vector<Chpx> Footer::GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<Chpx> allRunsProperties;
		unsigned int runOffset = 0;

		if ( allRunsOffsets != NULL )
		{
			for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> footerItemRunsOffsets;
				std::vector<Chpx> footerItemRunsProperties = iter->footerItem->GetAllRunProperties( &footerItemRunsOffsets );

				for ( unsigned int i = 0; i < footerItemRunsProperties.size(); i++ )
				{
					allRunsProperties.push_back( footerItemRunsProperties[i] );
					allRunsOffsets->push_back( runOffset + footerItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->footerItem->GetAllText().size() );
			}
		}

		return allRunsProperties;
	}

	std::vector<IParagraphItemPtr> Footer::GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allRuns;

		if ( allRunsOffsets != NULL )
		{
			unsigned int runOffset = 0;

			for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemRunsOffsets;
				std::vector<IParagraphItemPtr> allTextItemRuns = iter->footerItem->GetAllRunsCopy( &allTextItemRunsOffsets );

				for ( unsigned int i = 0; i < allTextItemRuns.size(); i++ )
				{
					allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemRuns[i]->Clone()) ) );
					allRunsOffsets->push_back( runOffset + allTextItemRunsOffsets[i] );
				}

				runOffset += ( sizeof(WCHAR) * iter->footerItem->GetAllText().size() );
			}
		}

		return allRuns;
	}

	std::vector<IParagraphItemPtr> Footer::GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const
	{
		std::vector<IParagraphItemPtr> allParagraphItems;

		if ( allParagraphItemsOffsets != NULL )
		{
			unsigned int textItemOffset = 0;

			for ( std::list<FooterItemWithOffset>::const_iterator iter = this->textItems.begin(); iter != this->textItems.end(); iter++ )
			{
				std::vector<unsigned int> allTextItemParagraphItemsOffsets;
				std::vector<IParagraphItemPtr> allTextItemParagraphItems = iter->footerItem->GetAllParagraphItemsCopy( &allTextItemParagraphItemsOffsets );

				for ( unsigned int i = 0; i < allTextItemParagraphItems.size(); i++ )
				{
					allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(allTextItemParagraphItems[i]->Clone()) ) );
					allParagraphItemsOffsets->push_back( textItemOffset + allTextItemParagraphItemsOffsets[i] );
				}

				textItemOffset += ( sizeof(WCHAR) * iter->footerItem->GetAllText().size() );
			}
		}

		return allParagraphItems;
	}

	IVirtualConstructor* Footer::New() const
	{
		return new Footer();
	}

	IVirtualConstructor* Footer::Clone() const
	{
		return new Footer( *this );
	}
}
