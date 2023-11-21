#pragma once

#include "Prl.h"

namespace Docx2Doc
{
	class LPStshiGrpPrl: public IOperand
	{
	public:

		LPStshiGrpPrl() : bytes(NULL), sizeInBytes(0)
		{
		}

		explicit LPStshiGrpPrl( const std::vector<Prl>& _grpprl ) : bytes(NULL), sizeInBytes(0), grpprl(_grpprl)
		{
			this->sizeInBytes = sizeof(int);

			for ( std::vector<Prl>::const_iterator iter = this->grpprl.begin(); iter != this->grpprl.end(); iter++ )
			{
				this->sizeInBytes += iter->Size();
			}

			this->bytes = new BYTE[this->sizeInBytes];

			if ( this->bytes != NULL )
			{
				memset( this->bytes, 0, this->sizeInBytes );

				DocFileFormat::FormatUtils::SetBytes( this->bytes, (int)( this->sizeInBytes - sizeof(int) ) );

				BYTE* prlBytes = NULL;
				unsigned long prlSize = 0;
				unsigned int prlPrevSize = 0;

				for ( std::vector<Prl>::iterator iter = this->grpprl.begin(); iter != this->grpprl.end(); iter++ )
				{
					prlBytes = iter->GetBytes( &prlSize );

					if ( prlBytes != NULL )
					{
						memcpy( ( this->bytes + sizeof(int) + prlPrevSize ), prlBytes, prlSize );
						prlPrevSize += prlSize;

						RELEASEARRAYOBJECTS (prlBytes);
					}
				}
			}
		}

		LPStshiGrpPrl( const LPStshiGrpPrl& _lPStshiGrpPrl ) : bytes(NULL), sizeInBytes(_lPStshiGrpPrl.sizeInBytes), grpprl(_lPStshiGrpPrl.grpprl)
		{
			this->bytes = new BYTE[this->sizeInBytes];

			if ( this->bytes != NULL )
			{
				memset( this->bytes, 0, this->sizeInBytes );
				memcpy( this->bytes, _lPStshiGrpPrl.bytes, this->sizeInBytes );
			}
		}

		virtual ~LPStshiGrpPrl()
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

		vector<Prl> grpprl;

		BYTE* bytes;
		unsigned int sizeInBytes;
	};
}
