#pragma once

#include "LSTF.h"

namespace Docx2Doc
{
	class PlfLst : public IOperand
	{
	public:
		PlfLst() : bytes(NULL), sizeInBytes(2)
		{
			this->bytes = new BYTE[this->sizeInBytes];

			memset( this->bytes, 0, this->sizeInBytes );
		}

		explicit PlfLst( const std::vector<LSTF>& _rgLstf ) :  bytes(NULL), sizeInBytes(sizeof(short))
		{
			if ( !_rgLstf.empty() )
			{
				this->sizeInBytes += ( _rgLstf.size() * _rgLstf[0].Size() );
			}

			this->bytes = new BYTE[this->sizeInBytes];

			memset( this->bytes, 0, this->sizeInBytes );

			DocFileFormat::FormatUtils::SetBytes( this->bytes, (short)_rgLstf.size() );

			for ( unsigned int i = 0; i < _rgLstf.size(); i++ )
			{
				memcpy( ( this->bytes + sizeof(short) + ( i * _rgLstf[i].Size() ) ), (BYTE*)_rgLstf[i], _rgLstf[i].Size() );
			}
		}

		PlfLst( const PlfLst& _plfLst ) : bytes(NULL), sizeInBytes(_plfLst.sizeInBytes)
		{
			this->bytes = new BYTE[this->sizeInBytes];

			memset( this->bytes, 0, this->sizeInBytes );

			memcpy( this->bytes, _plfLst.bytes, this->sizeInBytes );
		}

		virtual ~PlfLst()
		{
			RELEASEARRAYOBJECTS (bytes);
		}

		virtual operator BYTE*() const
		{
			return this->bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)this->bytes;
		}

		virtual unsigned int Size() const
		{
			return this->sizeInBytes;
		}
	private:

		BYTE* bytes;
		unsigned int sizeInBytes;
	};
}
