#pragma once

#include "Prl.h"
#include "XAS.h"

namespace Docx2Doc
{
	class SDxaColSpacingOperand : public IOperand
	{
	public:

		SDxaColSpacingOperand()
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );
		}

		explicit SDxaColSpacingOperand( BYTE _iCol, XAS_nonNeg _dxaCol )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			if ( _iCol > 43 )
			{
				this->bytes[0] = 43;
			}
			else
			{
				this->bytes[0] = _iCol;
			}

			DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(_iCol) ), (unsigned short)_dxaCol );
		}

		SDxaColSpacingOperand( const SDxaColSpacingOperand& _sDxaColSpacingOperand )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );
			memcpy( this->bytes, _sDxaColSpacingOperand.bytes, SIZE_IN_BYTES );
		}

		virtual ~SDxaColSpacingOperand()
		{
		}

		virtual operator BYTE*() const
		{
			return (BYTE*)(this->bytes);
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)(this->bytes);
		}

		virtual unsigned int Size() const
		{
			return sizeof(this->bytes);
		}
	private:

		static const BYTE SIZE_IN_BYTES = 3;
		BYTE bytes[SIZE_IN_BYTES];
	};

	class SDxaColWidthOperand : public IOperand
	{
	public:
		SDxaColWidthOperand()
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );
		}

		explicit SDxaColWidthOperand( BYTE _iCol, XAS_nonNeg _dxaCol )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			if ( _iCol > 43 )
			{
				this->bytes[0] = 43;
			}
			else
			{
				this->bytes[0] = _iCol;
			}

			unsigned short dxaCol = 718;

			if ( (unsigned short)_dxaCol > 718 )
			{
				dxaCol = (unsigned short)_dxaCol;  
			}

			DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(_iCol) ), dxaCol );
		}

		SDxaColWidthOperand( const SDxaColWidthOperand& _sDxaColWidthOperand )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _sDxaColWidthOperand.bytes, SIZE_IN_BYTES );
		}

		virtual ~SDxaColWidthOperand()
		{
		}

		virtual operator BYTE*() const
		{
			return (BYTE*)(this->bytes);
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)(this->bytes);
		}

		virtual unsigned int Size() const
		{
			return sizeof(this->bytes);
		}
	private:

		static const BYTE SIZE_IN_BYTES = 3;
		BYTE bytes[SIZE_IN_BYTES];
	};

	class Sepx : public IOperand
	{
	public:

		Sepx() : cb(0), bytes(NULL), size(0)
		{
			this->size = ( sizeof(this->cb) + this->cb );

			if ( this->size != 0 )
			{
				this->bytes = new BYTE[this->size];

				if ( this->bytes != NULL )
				{
					memset( this->bytes, 0, this->size );
					DocFileFormat::FormatUtils::SetBytes( this->bytes, this->cb );
				}
			}
		}

		Sepx( const std::vector<Prl>& _grpprl ):
		cb(0), bytes(NULL), size(0)
		{
			for ( unsigned int i = 0; i < _grpprl.size(); i++ )
			{
				this->cb += (short)_grpprl[i].Size();
				this->grpprl.push_back( _grpprl[i] );
			}

			this->size = ( sizeof(this->cb) + this->cb );

			if ( this->size != 0 )
			{
				this->bytes = new BYTE[this->size];

				if ( this->bytes != NULL )
				{
					memset( this->bytes, 0, this->size );
					DocFileFormat::FormatUtils::SetBytes( this->bytes, this->cb );

					BYTE* prlBytes = NULL;
					unsigned long prlSize = 0;
					unsigned int prlPrevSize = 0; 

					for ( unsigned int i = 0; i < this->grpprl.size(); i++ )
					{
						prlBytes = this->grpprl[i].GetBytes( &prlSize );

						if ( prlBytes != NULL )
						{
							memcpy( ( this->bytes + sizeof(this->cb) + prlPrevSize ), prlBytes, prlSize );
							prlPrevSize += prlSize;

							RELEASEARRAYOBJECTS (prlBytes);
						}
					}
				}
			}
		}

		Sepx( const Sepx& sepx ) : cb(sepx.cb), bytes(NULL), size(sepx.size)
		{
			for ( unsigned int i = 0; i < sepx.grpprl.size(); i++ )
			{
				this->grpprl.push_back( sepx.grpprl[i] );
			}

			if ( this->size != 0 )
			{
				this->bytes = new BYTE[this->size];

				if ( this->bytes != NULL )
				{
					memset( this->bytes, 0, this->size );
					memcpy( this->bytes, sepx.bytes, this->size );
				}
			}
		}

		virtual ~Sepx()
		{
			RELEASEARRAYOBJECTS (bytes);
		}

		bool operator == ( const Sepx& sepx )
		{
			if ( ( this->cb != sepx.cb ) || ( this->grpprl.size() != sepx.grpprl.size() ) || ( this->size != sepx.size ) )
			{
				return false;
			}
			else
			{
				unsigned int minPrlCount = std::min( this->grpprl.size(), sepx.grpprl.size() );

				for ( unsigned int i = 0; i < minPrlCount; i++ )
				{
					if ( this->grpprl[i] != sepx.grpprl[i] )
					{
						return false;
					}
				}

				if ( memcmp( this->bytes, sepx.bytes, this->size ) != 0 )
				{
					return false;
				}
			}

			return true;
		}

		bool operator != ( const Sepx& sepx )
		{
			return !( *this == sepx );
		}

		Sepx& operator = ( const Sepx& sepx )
		{
			if ( this != &sepx )
			{
				this->cb = sepx.cb;
				this->size = sepx.size;

				this->grpprl.clear();

				for ( unsigned int i = 0; i < sepx.grpprl.size(); i++ )
				{
					this->grpprl.push_back( sepx.grpprl[i] );
				}

				RELEASEARRAYOBJECTS (bytes);

				if ( this->size != 0 )
				{
					this->bytes = new BYTE[this->size];

					if ( this->bytes != NULL )
					{
						memset( this->bytes, 0, this->size );
						memcpy( this->bytes, sepx.bytes, this->size );
					}
				}
			}

			return *this;
		}

		virtual operator BYTE*() const
		{
			return (BYTE*)(this->bytes);
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)(this->bytes);
		}

		virtual unsigned int Size() const
		{
			return this->size;
		}

	private:

		short cb; //Size in bytes of the grpprl
		std::vector<Prl> grpprl;
		BYTE* bytes;
		unsigned int size;
	};
}
