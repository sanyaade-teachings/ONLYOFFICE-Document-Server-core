#pragma once

#include "OfficeArtRecordHeader.h"
#include "IOfficeArtRecord.h"
#include "OfficeArtRGFOPTE.h"

namespace OfficeArt
{
	class OfficeArtFOPT: public IOfficeArtRecord
	{
	public:
		OfficeArtFOPT() : rh( 0x3, 0, 0xF00B, 0 ), fopt(), bytes(NULL), size(0)
		{
			size = sizeof(rh);

			if (size)
			{
				bytes = new BYTE[size];

				if (bytes)
				{
					memset( bytes, 0, size );
					memcpy( bytes, (BYTE*)rh, sizeof(rh) );
				}
			}
		}

		explicit OfficeArtFOPT (const OfficeArtRGFOPTE& _fopt ) : rh( 0x3, _fopt.Count(), 0xF00B, _fopt.Size() ), fopt(_fopt), bytes(NULL), size(0)
		{
			this->size = ( sizeof(this->rh) + this->fopt.Size() );

			if ( this->size != 0 )
			{
				this->bytes = new BYTE[this->size];

				if ( this->bytes != NULL )
				{
					memset( this->bytes, 0, this->size );

					memcpy( this->bytes, (BYTE*)this->rh, sizeof(this->rh) );
					memcpy( ( this->bytes + sizeof(this->rh) ), (BYTE*)this->fopt, this->fopt.Size() );
				}
			}
		}

		OfficeArtFOPT (const OfficeArtFOPT& _officeArtFOPT) : rh(_officeArtFOPT.rh), fopt(_officeArtFOPT.fopt), bytes(NULL), size(_officeArtFOPT.size)
		{
			if (size)
			{
				bytes = new BYTE[size];

				if ( this->bytes != NULL )
				{
					memset( bytes, 0, size );
					memcpy( bytes, _officeArtFOPT.bytes, size );
				}
			}
		}

		virtual operator const BYTE* () const
		{
			return (const BYTE*)(bytes);
		}

		virtual operator BYTE* () const
		{
			return bytes;
		}

		virtual unsigned int Size() const
		{
			return size;
		}

		virtual IOfficeArtRecord* New() const
		{
			return new OfficeArtFOPT ();
		}

		virtual IOfficeArtRecord* Clone() const
		{
			return new OfficeArtFOPT( *this );
		}

		virtual ~OfficeArtFOPT()
		{
			RELEASEARRAYOBJECTS (bytes);
		}

	protected:

		OfficeArtRecordHeader		rh;
		OfficeArtRGFOPTE			fopt;

		BYTE*						bytes;
		unsigned int				size;
	};
	class OfficeArtSecondaryFOPT: public IOfficeArtRecord
	{
	public:
		OfficeArtSecondaryFOPT() : rh( 0x3, 0, 0xF122, 0 ), fopt(), bytes(NULL), size(0)
		{
			size = sizeof(rh);

			if (size)
			{
				bytes = new BYTE[size];

				if (bytes)
				{
					memset( bytes, 0, size );
					memcpy( bytes, (BYTE*)rh, sizeof(rh) );
				}
			}
		}

		explicit OfficeArtSecondaryFOPT (const OfficeArtRGFOPTE& _fopt ) : rh( 0x3, _fopt.Count(), 0xF122, _fopt.Size() ), fopt(_fopt), bytes(NULL), size(0)
		{
			this->size = ( sizeof(this->rh) + this->fopt.Size() );

			if ( this->size != 0 )
			{
				this->bytes = new BYTE[this->size];

				if ( this->bytes != NULL )
				{
					memset( this->bytes, 0, this->size );

					memcpy( this->bytes, (BYTE*)this->rh, sizeof(this->rh) );
					memcpy( ( this->bytes + sizeof(this->rh) ), (BYTE*)this->fopt, this->fopt.Size() );
				}
			}
		}

		OfficeArtSecondaryFOPT (const OfficeArtSecondaryFOPT& _officeArtFOPT) : rh(_officeArtFOPT.rh), fopt(_officeArtFOPT.fopt), bytes(NULL), size(_officeArtFOPT.size)
		{
			if (size)
			{
				bytes = new BYTE[size];

				if ( this->bytes != NULL )
				{
					memset( bytes, 0, size );
					memcpy( bytes, _officeArtFOPT.bytes, size );
				}
			}
		}

		virtual operator const BYTE* () const
		{
			return (const BYTE*)(bytes);
		}

		virtual operator BYTE* () const
		{
			return bytes;
		}

		virtual unsigned int Size() const
		{
			return size;
		}

		virtual IOfficeArtRecord* New() const
		{
			return new OfficeArtSecondaryFOPT ();
		}

		virtual IOfficeArtRecord* Clone() const
		{
			return new OfficeArtSecondaryFOPT( *this );
		}

		virtual ~OfficeArtSecondaryFOPT()
		{
			RELEASEARRAYOBJECTS (bytes);
		}

	protected:

		OfficeArtRecordHeader		rh;
		OfficeArtRGFOPTE			fopt;

		BYTE*						bytes;
		unsigned int				size;
	};
}
