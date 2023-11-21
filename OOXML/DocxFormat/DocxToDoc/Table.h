#pragma once

#include "TableRow.h"

namespace Docx2Doc
{
class Table: public ITextItem
{
	struct TableRowWithOffset
	{
		TableRow tableRow;
		unsigned int tableRowOffset;

		TableRowWithOffset():
			tableRow(), tableRowOffset(0)
		{
		}

		TableRowWithOffset( const TableRow& _tableRow, unsigned int _tableRowOffset ):
			tableRow(_tableRow), tableRowOffset(_tableRowOffset)
		{
		}
	};

private:
	std::list<TableRowWithOffset> rows;
	unsigned int depth;
	unsigned int tableRowsOffset;

protected:
	void SetDepth( unsigned int _depth );
	unsigned int GetDepth() const;

public:
	Table();
	Table( const Table& table );
	void AddRow( const TableRow& row );
	virtual ~Table();
	virtual std::wstring GetAllText() const;
	virtual operator std::wstring() const;
	virtual std::vector<TextItemPtr> GetAllParagraphsCopy() const;
	virtual std::vector<ITextItem*> GetAllParagraphs();
	virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const;
	virtual std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const;
	virtual std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const;
	virtual std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const;
	virtual IVirtualConstructor* New() const;
	virtual IVirtualConstructor* Clone() const;
};
}
