#pragma once

#include "Paragraph.h"

namespace Docx2Doc
{
	class Header: public ITextItem
	{
		struct HeaderItemWithOffset
		{
			TextItemPtr headerItem;
			unsigned int headerItemOffset;

			HeaderItemWithOffset():
			headerItem(), headerItemOffset(0)
			{
			}

			HeaderItemWithOffset( const TextItemPtr& _headerItem, unsigned int _headerItemOffset ):
			headerItem(_headerItem), headerItemOffset(_headerItemOffset)
			{
			}
		};

	private:
		std::list<HeaderItemWithOffset> textItems;
		unsigned int headerItemsOffset;

	public:
		explicit Header();
		Header( const Header& _header );
		void AddTextItem( const ITextItem& _textItem );
		virtual ~Header();
		virtual std::wstring GetAllText() const;
		virtual operator std::wstring() const;
		virtual std::vector<TextItemPtr> GetAllParagraphsCopy() const;
		virtual std::vector<ITextItem*> GetAllParagraphs();
		virtual std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const;
		virtual std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const;
		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const;
		virtual std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const;
		virtual IVirtualConstructor* New() const;
		virtual IVirtualConstructor* Clone() const;
	};
}
