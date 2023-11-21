#pragma once

#include "Tplc.h"
#include "grfhic.h"

namespace Docx2Doc
{
class LSTF: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 28;
	static const BYTE RGISTD_PARA_COUNT = 9;
	BYTE bytes[SIZE_IN_BYTES];

public:
	LSTF()
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );
	}

	explicit LSTF( int _lsid, const Tplc* _tplc, bool _fSimpleList,
				   bool _fAutoNum, bool _fHybrid, grfhic _grfhic, const std::vector<short>* _rgistdPara = NULL )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		DocFileFormat::FormatUtils::SetBytes( this->bytes, _lsid );

		if ( _tplc != NULL )
		{
			DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(_lsid) ), (unsigned int)(*_tplc) );
		}
		else
		{
			DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(_lsid) ), (unsigned int)0 );
		}

		if ( ( _rgistdPara != NULL ) && ( _rgistdPara->size() == RGISTD_PARA_COUNT ) )
		{
			for ( unsigned int i = 0; i < RGISTD_PARA_COUNT; i++ )
			{
				DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(_lsid) + sizeof(unsigned int) + ( i * sizeof(short) ) ), _rgistdPara->at( i ) );
			}
		}
		else
		{
			for ( unsigned int i = 0; i < RGISTD_PARA_COUNT; i++ )
			{
				DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(_lsid) + sizeof(unsigned int) + ( i * sizeof(short) ) ), (short)0x0FFF );
			}
		}

		BYTE simpleListAutoNumHybridFlags = 0x00;
		BYTE fSimpleList = 0x00;
		BYTE fAutoNum = 0x00;
		BYTE fHybrid = 0x00;

		( _fSimpleList ) ? ( fSimpleList = 0x01 ) : ( fSimpleList = 0x00 );
		( _fAutoNum ) ? ( fAutoNum = 0x04 ) : ( fAutoNum = 0x00 );
		( _fHybrid ) ? ( fHybrid = 0x10 ) : ( fHybrid = 0x00 );

		simpleListAutoNumHybridFlags |= ( fSimpleList | fAutoNum | fHybrid );

		this->bytes[sizeof(_lsid) + sizeof(unsigned int) + ( RGISTD_PARA_COUNT * sizeof(short) )] = simpleListAutoNumHybridFlags;
		this->bytes[sizeof(_lsid) + sizeof(unsigned int) + ( RGISTD_PARA_COUNT * sizeof(short) ) + sizeof(simpleListAutoNumHybridFlags)] = (BYTE)_grfhic;
	}

	LSTF( const LSTF& _lSTF )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _lSTF.bytes, SIZE_IN_BYTES );
	}

	virtual ~LSTF()
	{
	}

	virtual operator BYTE*() const
	{
		return (BYTE*)(this->bytes);
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
