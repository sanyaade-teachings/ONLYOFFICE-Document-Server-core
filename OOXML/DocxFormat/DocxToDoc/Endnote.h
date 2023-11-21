#pragma once

#include "ITextItem.h"
#include "EndnoteRef.h"
#include "EndnoteReference.h"
#include "PLC.h"

namespace Docx2Doc
{
typedef PLC<EmptyPLCData> PlcfendTxt;
typedef PLC<short> PlcfendRef;

class Endnote: public ITextItem
{
	struct EndnoteItemWithOffset
	{
		TextItemPtr endnoteItem;
		unsigned int endnoteItemOffset;

		EndnoteItemWithOffset() : endnoteItem(), endnoteItemOffset(0)
		{
		}

		EndnoteItemWithOffset( const TextItemPtr& _endnoteItem, unsigned int _endnoteItemOffset ) : endnoteItem(_endnoteItem), endnoteItemOffset(_endnoteItemOffset)
		{
		}
	};

private:
	std::list<EndnoteItemWithOffset> textItems;
	unsigned int endnoteItemsOffset;
	short aFtnIdx;

public:
	explicit Endnote( short _aFtnIdx = 0 );
	Endnote( const Endnote& _endnote );
	void AddTextItem( const ITextItem& _textItem );
	short GetIndex() const;
	virtual ~Endnote();
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
