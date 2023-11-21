#pragma once

#include "IStreamWriter.h"
#include "GrpPrlAndIstd.h"

namespace Docx2Doc
{
	class PapxInFkp : public IStreamWriter
	{
	public:
		PapxInFkp() : grpprlInPapx()
		{

		}

		PapxInFkp(const GrpPrlAndIstd& _grpprlInPapx) : grpprlInPapx(_grpprlInPapx)
		{

		}

		PapxInFkp(const PapxInFkp& pifkp) : grpprlInPapx(pifkp.grpprlInPapx)
		{

		}

		virtual ~PapxInFkp()
		{
		}

		//
		inline bool operator == (const PapxInFkp& pifkp)
		{
			return ( grpprlInPapx == pifkp.grpprlInPapx );
		}

		inline bool operator != (const PapxInFkp& pifkp)
		{
			return !( *this == pifkp );
		}

		inline PapxInFkp& operator = (const PapxInFkp& pifkp)
		{
			if ( *this != pifkp )
			{
				grpprlInPapx = pifkp.grpprlInPapx;
			}

			return *this;
		}

		inline unsigned long Size() const
		{
			unsigned long sizeInBytes = 0;
			BYTE cb		= 0;
			BYTE cb_	= 0;

			sizeInBytes = this->grpprlInPapx.Size();

			if ( sizeInBytes % 2 != 0 )
			{
				cb = (BYTE)( ( sizeInBytes + 1 ) / 2 );
				sizeInBytes += sizeof(cb); 
			}
			else
			{
				cb = 0;
				cb_ = (BYTE)( sizeInBytes / 2 );
				sizeInBytes += ( sizeof(cb) + sizeof(cb_) );
			}

			return sizeInBytes;
		}

		inline Prl operator[] (unsigned int index) const
		{
			return grpprlInPapx[index];
		}

		inline unsigned int GetPrlCount() const
		{
			return this->grpprlInPapx.GetPrlCount();
		}

		inline std::vector<Prl> GetPrls() const
		{
			return this->grpprlInPapx.GetPrls();
		}

		inline short GetIstd() const
		{
			return grpprlInPapx.GetIstd();
		}

		// IStreamWriter
		virtual BYTE* GetBytes(unsigned long* size) const
		{
			BYTE* bytes = NULL;

			if ( size != NULL )
			{
				BYTE cb = 0;
				BYTE cb_ = 0;

				*size = this->grpprlInPapx.Size();

				if ( *size % 2 != 0 )
				{
					cb = (BYTE)( ( *size + 1 ) / 2 );
					*size += sizeof(cb); 
				}
				else
				{
					cb = 0;
					cb_ = (BYTE)( *size / 2 );
					*size += ( sizeof(cb) + sizeof(cb_) );
				}

				bytes = new BYTE[*size];

				if ( bytes != NULL )
				{
					memset( bytes, 0, *size );
					bytes[0] = cb;

					BYTE cb_offset = 0;

					if ( cb_ != 0 )
					{
						bytes[1] = cb_;
						cb_offset = sizeof(cb_);
					}

					BYTE* grpPrlAndIstdBytes = NULL;
					unsigned long grpPrlAndIstdSize = 0;

					grpPrlAndIstdBytes = this->grpprlInPapx.GetBytes( &grpPrlAndIstdSize );

					if ( grpPrlAndIstdBytes != NULL )
					{
						memcpy( ( bytes + sizeof(cb) + cb_offset ), grpPrlAndIstdBytes, grpPrlAndIstdSize );

						RELEASEARRAYOBJECTS (grpPrlAndIstdBytes);
					}
				}
			}

			return bytes;
		}

	private:

		GrpPrlAndIstd	grpprlInPapx;
	};
}
