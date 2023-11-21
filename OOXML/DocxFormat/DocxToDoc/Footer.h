#pragma once

#include "Paragraph.h"

namespace Docx2Doc
{
	class Footer: public ITextItem
	{
		struct FooterItemWithOffset
		{
			TextItemPtr		footerItem;
			unsigned int	footerItemOffset;

			FooterItemWithOffset() : footerItem(), footerItemOffset(0)
			{

			}

			FooterItemWithOffset(const TextItemPtr& _footerItem, unsigned int _footerItemOffset) : footerItem(_footerItem), footerItemOffset(_footerItemOffset)
			{

			}
		};

	private:
		std::list<FooterItemWithOffset>	textItems;
		unsigned int				footerItemsOffset;

	public:
		explicit Footer();
		Footer( const Footer& _footer );
		void AddTextItem( const ITextItem& _textItem );
		virtual ~Footer();
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
