#pragma once

#include "ITextItem.h"
#include "FootnoteRef.h"
#include "FootnoteReference.h"
#include "PLC.h"

namespace Docx2Doc
{
	typedef PLC<EmptyPLCData> PlcffndTxt;
	typedef PLC<short> PlcffndRef;

	class Footnote : public ITextItem
	{
		struct FootnoteItemWithOffset
		{
			TextItemPtr footnoteItem;
			unsigned int footnoteItemOffset;

			FootnoteItemWithOffset():
			footnoteItem(), footnoteItemOffset(0)
			{
			}

			FootnoteItemWithOffset( const TextItemPtr& _footnoteItem, unsigned int _footnoteItemOffset ):
			footnoteItem(_footnoteItem), footnoteItemOffset(_footnoteItemOffset)
			{
			}
		};

	private:
		std::list<FootnoteItemWithOffset> textItems;
		unsigned int footnoteItemsOffset;
		short aFtnIdx;

	public:
		explicit Footnote( short _aFtnIdx = 0 );
		Footnote( const Footnote& _footnote );
		void AddTextItem( const ITextItem& _textItem );
		short GetIndex() const;
		virtual ~Footnote();
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
