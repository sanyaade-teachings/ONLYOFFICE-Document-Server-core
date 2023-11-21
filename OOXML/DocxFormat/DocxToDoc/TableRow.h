#pragma once

#include "TableCell.h"

namespace Docx2Doc
{
class TableRow
{
	friend class Table;

	struct TableCellWithOffset
	{
		TableCell tableCell;
		unsigned int tableCellOffset;

		TableCellWithOffset():
			tableCell(), tableCellOffset(0)
		{
		}

		TableCellWithOffset( const TableCell& _tableCell, unsigned int _tableCellOffset ) : tableCell(_tableCell), tableCellOffset(_tableCellOffset)
		{
		}
	};

private:
	std::list<TableCellWithOffset> cells;
	std::list<Prl> properties;
	unsigned int depth;
	unsigned int tableCellsOffset;

protected:
	void SetDepth( unsigned int _depth );
	unsigned int GetDepth() const;
	
public:
	TableRow();
	explicit TableRow( unsigned int _depth );
	~TableRow();
	TableRow( const TableRow& tableRow );
	void AddCell( const TableCell& cell );
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
