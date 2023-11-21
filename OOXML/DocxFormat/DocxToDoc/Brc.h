#pragma once

#include "COLORREF.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
class Brc: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 8;

	BYTE bytes[SIZE_IN_BYTES];

public:
	Brc()
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );
	}

	explicit Brc( const COLORREF& _cv, BYTE _dptLineWidth, BYTE _brcType, BYTE _dptSpace, bool fShadow, bool fFrame )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		BYTE cvSize = _cv.Size();

		memcpy( this->bytes, (BYTE*)_cv, cvSize );

		BYTE dptLineWidth = 2;

		if ( _dptLineWidth > 2 )
		{
			dptLineWidth = _dptLineWidth;
		}

		this->bytes[cvSize] = dptLineWidth;
		this->bytes[cvSize + sizeof(dptLineWidth)] = _brcType;
		
		unsigned short dptSpaceAndFlags = 0;
		dptSpaceAndFlags |= _dptSpace; //Set dptSpace

		if ( fShadow )
		{
			dptSpaceAndFlags |= 0x20; //Set fShadow
		}

		if ( fFrame )
		{
			dptSpaceAndFlags |= 0x40; //Set fFrame
		}

		DocFileFormat::FormatUtils::SetBytes( ( this->bytes + cvSize + sizeof(dptLineWidth) + sizeof(_brcType) ), dptSpaceAndFlags );
	}

	explicit Brc( const BYTE* _bytes )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		if ( _bytes != NULL )
		{
			memcpy( this->bytes, _bytes, SIZE_IN_BYTES );
		}
	}

	Brc( const Brc& _brc )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _brc.bytes, SIZE_IN_BYTES );
	}

	Brc& operator = ( const Brc& _brc )
	{
		if ( this != &_brc )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _brc.bytes, SIZE_IN_BYTES );
		}

		return *this;
	}

	virtual ~Brc()
	{
	}

	virtual operator BYTE*() const
	{
		return (BYTE*)this->bytes;
	}

	virtual operator const BYTE*() const
	{
		return (const BYTE*)this->bytes;
	}

	virtual unsigned int Size() const
	{
		return sizeof(this->bytes);
	}
};

class BrcOperand: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 9;

	BYTE bytes[SIZE_IN_BYTES];

public:
	BrcOperand()
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );
	}

	explicit BrcOperand( const Brc& _brc )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );

		memcpy( ( this->bytes + sizeof(BYTE) ), (BYTE*)_brc, _brc.Size() );
	}

	BrcOperand( const BrcOperand& _brcOperand )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _brcOperand.bytes, SIZE_IN_BYTES );
	}

	BrcOperand& operator = ( const BrcOperand& _brcOperand )
	{
		if ( this != &_brcOperand )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _brcOperand.bytes, SIZE_IN_BYTES );
		}

		return *this;
	}

	virtual ~BrcOperand()
	{
	}

	virtual operator BYTE*() const
	{
		return (BYTE*)this->bytes;
	}

	virtual operator const BYTE*() const
	{
		return (const BYTE*)this->bytes;
	}

	virtual unsigned int Size() const
	{
		return sizeof(this->bytes);
	}
};
}
