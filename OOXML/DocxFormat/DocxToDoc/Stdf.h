#pragma once

#include "StdfBase.h"
#include "StdfPost2000.h"


namespace Docx2Doc
{
	class Stdf: public IOperand
	{
	public:

		Stdf() : bytes(NULL), sizeInBytes(0)
		{
		}

		explicit Stdf( const StdfBase& _stdfBase, const StdfPost2000* _stdfPost2000OrNone = NULL ) : bytes(NULL), sizeInBytes(0)
		{
			this->sizeInBytes = sizeof(_stdfBase);

			if ( _stdfPost2000OrNone != NULL )
			{
				this->sizeInBytes += sizeof(*_stdfPost2000OrNone);
			}

			this->bytes = new BYTE[this->sizeInBytes];

			if ( this->bytes != NULL )
			{
				memset( this->bytes, 0, this->sizeInBytes );
				memcpy( this->bytes, (BYTE*)_stdfBase, sizeof(_stdfBase) );

				if ( _stdfPost2000OrNone != NULL )
				{
					memcpy( ( this->bytes + sizeof(_stdfBase) ), (BYTE*)(*_stdfPost2000OrNone), sizeof(*_stdfPost2000OrNone) );
				}
			}
		}

		Stdf( const Stdf& _stdf ) : bytes(NULL), sizeInBytes(_stdf.sizeInBytes)
		{
			this->bytes = new BYTE[this->sizeInBytes];

			if ( this->bytes != NULL )
			{
				memset( this->bytes, 0, this->sizeInBytes );
				memcpy( this->bytes, _stdf.bytes, this->sizeInBytes );
			}
		}

		virtual ~Stdf()
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
