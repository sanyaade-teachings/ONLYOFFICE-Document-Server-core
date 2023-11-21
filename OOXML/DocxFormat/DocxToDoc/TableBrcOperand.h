#pragma once

#include "Brc.h"
#include "ItcFirstLim.h"
#include "Constants.h"

namespace Docx2Doc
{
	class TableBrcOperand: public IOperand
	{
	private:
		static const BYTE SIZE_IN_BYTES = 12;
		BYTE bytes[SIZE_IN_BYTES];

	public:
		TableBrcOperand()
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			this->bytes[0] = ( SIZE_IN_BYTES - 1 );
		}

		explicit TableBrcOperand( const ItcFirstLim& _itc, BYTE _bordersToApply, const Brc& _brc )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			this->bytes[0] = ( SIZE_IN_BYTES - 1 );

			DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(BYTE) ), (short)_itc );
			this->bytes[sizeof(BYTE) + sizeof(short)] = _bordersToApply;
			memcpy( ( this->bytes + sizeof(BYTE) + sizeof(short) + sizeof(BYTE) ), (BYTE*)_brc, _brc.Size() );
		}

		TableBrcOperand( const TableBrcOperand& _tableBrcOperand )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _tableBrcOperand.bytes, SIZE_IN_BYTES );
		}

		virtual ~TableBrcOperand()
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
