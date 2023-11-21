#pragma once

#include "ItcFirstLim.h"
#include "FtsWWidth.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"


namespace Docx2Doc
{
class TableCellWidthOperand: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 6;
	BYTE bytes[SIZE_IN_BYTES];

public:
	TableCellWidthOperand()
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );
	}

	explicit TableCellWidthOperand( const ItcFirstLim& _itc, const FtsWWidth_TablePart& _FtsWWidth )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );

		DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(BYTE) ), (short)_itc );
		memcpy( ( this->bytes + sizeof(BYTE) + sizeof(short) ), (BYTE*)_FtsWWidth, _FtsWWidth.Size() );
	}

	TableCellWidthOperand( const TableCellWidthOperand& _tableCellWidthOperand )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _tableCellWidthOperand.bytes, SIZE_IN_BYTES );
	}

	virtual ~TableCellWidthOperand()
	{
	}

	virtual unsigned int Size() const
	{
		return (unsigned int)sizeof(this->bytes);
	}

	virtual operator BYTE*() const
	{
		return (BYTE*)(this->bytes);
	}

	virtual operator const BYTE*() const
	{
		return (const BYTE*)(this->bytes);
	}
};
}
