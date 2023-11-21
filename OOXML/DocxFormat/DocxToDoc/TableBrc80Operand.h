#pragma once

#include "Brc80MayBeNil.h"
#include "ItcFirstLim.h"
#include "Constants.h"

#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
	class TableBrc80Operand: public IOperand
	{
	private:
		static const BYTE SIZE_IN_BYTES = 8;
		BYTE bytes[SIZE_IN_BYTES];

	public:
		TableBrc80Operand()
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			this->bytes[0] = ( SIZE_IN_BYTES - 1 );
		}

		explicit TableBrc80Operand( const ItcFirstLim& _itc, BYTE _bordersToApply, const Brc80MayBeNil& _brc )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			this->bytes[0] = ( SIZE_IN_BYTES - 1 );

			DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(BYTE) ), (short)_itc );
			this->bytes[sizeof(BYTE) + sizeof(short)] = _bordersToApply;
			unsigned int brc = (unsigned int)_brc;
			memcpy( ( this->bytes + sizeof(BYTE) + sizeof(short) + sizeof(BYTE) ), &brc, sizeof(brc) );
		}

		TableBrc80Operand( const TableBrc80Operand& _tableBrc80Operand )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _tableBrc80Operand.bytes, SIZE_IN_BYTES );
		}

		virtual ~TableBrc80Operand()
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
