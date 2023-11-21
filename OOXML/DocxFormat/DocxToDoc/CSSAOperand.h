#pragma once

#include "ItcFirstLim.h"
#include "Constants.h"

#include "../../../MsBinaryFile/Common/Base/IOperand.h"

namespace Docx2Doc
{
	class CSSA: public IOperand
	{
	private:
		ItcFirstLim itc;
		Constants::Fbrc grfbrc;
		Constants::Fts ftsWidth;
		unsigned short wWidth;

		static const BYTE SIZE_IN_BYTES = 6;
		BYTE bytes[SIZE_IN_BYTES];

	public:
		explicit CSSA( ItcFirstLim _itc, Constants::Fbrc _grfbrc, Constants::Fts _ftsWidth, unsigned short _wWidth ) : itc(_itc), grfbrc(_grfbrc), ftsWidth(_ftsWidth)
		{
			if ( this->ftsWidth == Constants::ftsNil )
			{
				this->wWidth = 0;
			}
			else
			{
				this->wWidth = _wWidth;
			}

			memset( this->bytes, 0, sizeof(this->bytes) );
			memcpy( this->bytes, (void*)(&this->itc), sizeof(this->itc) );
			memcpy( ( this->bytes + sizeof(this->itc) ), &(this->grfbrc), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) ), &(this->ftsWidth), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) + sizeof(BYTE) ), &(this->wWidth), sizeof(this->wWidth) );
		}

		CSSA( const CSSA& _cssa ) : itc(_cssa.itc), grfbrc(_cssa.grfbrc), ftsWidth(_cssa.ftsWidth), wWidth(_cssa.wWidth)
		{
			memset( this->bytes, 0, sizeof(this->bytes) );
			memcpy( this->bytes, (void*)(&this->itc), sizeof(this->itc) );
			memcpy( ( this->bytes + sizeof(this->itc) ), &(this->grfbrc), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) ), &(this->ftsWidth), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) + sizeof(BYTE) ), &(this->wWidth), sizeof(this->wWidth) );
		}

		virtual ~CSSA()
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

	class CSSAOperand: public IOperand
	{
	private:
		CSSA cssa;

		BYTE *bytes;

	public:
		explicit CSSAOperand( const CSSA& _cssa ): cssa(_cssa), bytes(NULL)
		{
			BYTE cssaSize = this->cssa.Size();
			this->bytes = new BYTE[cssaSize + 1];
			memset( this->bytes, 0, ( cssaSize + 1 ) );
			this->bytes[0] = cssaSize;
			memcpy( ( this->bytes + sizeof(BYTE) ), this->cssa.operator BYTE*(), cssaSize );
		}

		CSSAOperand( const CSSAOperand& _CSSAOperand ): cssa(_CSSAOperand.cssa), bytes(NULL)
		{
			BYTE cssaSize = this->cssa.Size();
			this->bytes = new BYTE[cssaSize + 1];
			memset( this->bytes, 0, ( cssaSize + 1 ) );
			this->bytes[0] = cssaSize;
			memcpy( ( this->bytes + sizeof(BYTE) ), this->cssa.operator BYTE*(), cssaSize );
		}

		virtual ~CSSAOperand()
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
			return ( this->cssa.Size() + 1 );
		}
	};
}
