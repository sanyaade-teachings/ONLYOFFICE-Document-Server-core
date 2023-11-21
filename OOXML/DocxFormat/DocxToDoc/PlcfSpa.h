#pragma once

#include "Spa.h"

namespace Docx2Doc
{
	class PlcfSpa : public IOperand
	{
	public:

		PlcfSpa(): bytes(NULL), sizeInBytes(0)
		{
			bytes = new BYTE[sizeInBytes];

			if (bytes)
				memset(bytes, 0, sizeInBytes);
		}

		PlcfSpa (const std::vector<unsigned int>& aCP, const std::vector<Spa>& oSpa) : bytes(NULL), sizeInBytes(0)
		{
			sizeInBytes	=	( (aCP.size() * sizeof(unsigned int) ) + ( oSpa.size() * Spa::SIZE_IN_BYTES ) );

			bytes		=	new BYTE[sizeInBytes];
			if (bytes)
			{
				memset (bytes, 0,sizeInBytes);

				unsigned int offset = 0;
				for ( std::vector<unsigned int>::const_iterator iter = aCP.begin(); iter != aCP.end(); ++iter)
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + offset ), (int)(*iter) );
					offset += sizeof(unsigned int);
				}

				if (bytes)
				{
					for (std::vector<Spa>::const_iterator iter = oSpa.begin(); iter != oSpa.end(); ++iter)
					{
						memcpy ((bytes + offset), (BYTE*)(*iter), iter->Size());
						offset += iter->Size();
					}
				}
			}
		}

		PlcfSpa(const PlcfSpa& oSpa) : bytes(NULL), sizeInBytes(oSpa.sizeInBytes)
		{
			bytes	=	new BYTE[sizeInBytes];

			if (bytes)
			{
				memset (bytes, 0, sizeInBytes);
				memcpy (bytes, oSpa.bytes, sizeInBytes);
			}
		}

		inline bool operator == (const PlcfSpa& oSpa)
		{
			return ((sizeInBytes == oSpa.sizeInBytes) && (memcmp(bytes, oSpa.bytes, sizeInBytes ) == 0));
		}

		inline bool operator != (const PlcfSpa& oSpa)
		{
			return !( this->operator == (oSpa) );
		}

		inline PlcfSpa& operator = (const PlcfSpa& oSpa)
		{
			if (*this != oSpa)
			{
				RELEASEARRAYOBJECTS(bytes);

				sizeInBytes	=	oSpa.sizeInBytes;
				bytes		=	new BYTE[sizeInBytes];

				if (bytes)
				{
					memcpy(bytes, oSpa.bytes, sizeInBytes);
				}  
			}

			return *this;
		}


		// IOperand

		virtual ~PlcfSpa()
		{
			RELEASEARRAYOBJECTS(bytes);
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
