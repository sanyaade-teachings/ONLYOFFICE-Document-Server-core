#pragma once

#include "Paragraph.h"
#include "Picture.h"
#include "Footnote.h"
#include "Endnote.h"
#include "SectionBreak.h"
#include "CSSAOperand.h"
#include "TableBordersOperand.h"
#include "TableBordersOperand80.h"
#include "TDefTableOperand.h"
#include "TableCellWidthOperand.h"
#include "TableBrcOperand.h"
#include "TableBrc80Operand.h"
#include "TLP.h"

namespace Docx2Doc
{
class TableCell
{
	friend class TableRow;

	struct TableCellItemWithOffset
	{
		TextItemPtr tableCellItem;
		unsigned int tableCellItemOffset;

		TableCellItemWithOffset() : tableCellItem(), tableCellItemOffset(0)
		{
		}

		TableCellItemWithOffset( const TextItemPtr& _tableCellItem, unsigned int _tableCellItemOffset ) :
			tableCellItem(_tableCellItem), tableCellItemOffset(_tableCellItemOffset)
		{
		}
	};
	
private:
	std::list<TableCellItemWithOffset> textItems;
	std::list<Prl> properties;
	unsigned int depth;
	unsigned int tableCellItemsOffset;

protected:
	void SetDepth( unsigned int _depth );
	unsigned int GetDepth() const;

public:
	TableCell();
	explicit TableCell( unsigned int _depth );
	~TableCell();
	TableCell( const TableCell& tableCell );
	void AddTextItem( const ITextItem& _textItem );
	std::wstring GetAllText() const;
	operator std::wstring() const;
	std::vector<TextItemPtr> GetAllParagraphsCopy() const;
	std::vector<ITextItem*> GetAllParagraphs();
	void AddProperty( short sprm, void* operand );
	void AddProperties( const std::vector<Prl>& prls );
	void RemoveProperty( short sprm, void* operand );
	void RemoveAllProperties();
	PapxInFkp GetAllProperties() const;
	unsigned int GetAllPropertiesCount() const;
	std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const;
	std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const;
	std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const;
	std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const;
};
}
