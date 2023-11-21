#pragma once

#include "ITextItem.h"

#include "../../../MsBinaryFile/Common/Base/TextMark.h"

namespace Docx2Doc
{
	class SectionBreak: public ITextItem
	{
	private:
		static const WCHAR sectionBreakText = TextMark::PageBreakOrSectionMark;

	public:
		SectionBreak()
		{
		}

		SectionBreak( const SectionBreak& _sectionBreak )
		{
		}

		virtual ~SectionBreak()
		{
		}

		virtual std::wstring GetAllText() const
		{
			std::wstring allText;

			allText.push_back( sectionBreakText );

			return allText;
		}

		virtual operator std::wstring() const
		{
			std::wstring allText;

			allText.push_back( sectionBreakText );

			return allText;  
		}

		virtual std::vector<TextItemPtr> GetAllParagraphsCopy() const
		{
			std::vector<TextItemPtr> allParagraphsCopy;

			allParagraphsCopy.push_back( TextItemPtr( reinterpret_cast<ITextItem*>( NULL ) ) );

			return allParagraphsCopy;
		}

		virtual std::vector<ITextItem*> GetAllParagraphs()
		{
			std::vector<ITextItem*> allParagraphs;

			allParagraphs.push_back( NULL );

			return allParagraphs;   
		}

		virtual std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const
		{
			std::vector<PapxInFkp> allParagraphsProperties;

			if ( allParagraphsOffsets != NULL )
			{
				allParagraphsProperties.push_back( PapxInFkp() );
				allParagraphsOffsets->push_back( 0 );
			}

			return allParagraphsProperties;
		}

		virtual std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const
		{
			std::vector<Chpx> AllChpx;

			if ( allRunsOffsets != NULL )
			{
				AllChpx.push_back( Chpx() );

				allRunsOffsets->push_back( 0 );
			}

			return AllChpx;
		}

		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const
		{
			std::vector<IParagraphItemPtr> allRuns;

			if ( allRunsOffsets != NULL )
			{
				std::wstring text;

				text.push_back( sectionBreakText );

				allRuns.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(Run( Text( text.c_str() ) ).Clone()) ) );
				allRunsOffsets->push_back( 0 );
			}

			return allRuns;
		}

		virtual std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy (std::vector<unsigned int>* allParagraphItemsOffsets) const
		{
			std::vector<IParagraphItemPtr> allParagraphItems;

			if ( allParagraphItemsOffsets != NULL )
			{
				std::wstring text;

				text.push_back( sectionBreakText );

				allParagraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(Run( Text( text.c_str() ) ).Clone()) ) );
				allParagraphItemsOffsets->push_back( 0 );
			}

			return allParagraphItems;
		}

		virtual IVirtualConstructor* New() const
		{
			return new SectionBreak();
		}

		virtual IVirtualConstructor* Clone() const
		{
			return new SectionBreak( *this );
		}
	};
}
