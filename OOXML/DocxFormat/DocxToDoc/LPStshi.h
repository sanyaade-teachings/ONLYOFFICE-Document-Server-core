#pragma once

#include "STSHI.h"

namespace Docx2Doc
{
	class LPStshi : public IOperand
	{
	public:

		LPStshi () : bytes(NULL), sizeInBytes(0)
		{
		}

		LPStshi( const STSHI& oSTSHI ): bytes(NULL), sizeInBytes(0)
		{
			sizeInBytes	=	( sizeof(unsigned short) + oSTSHI.Size() );

			bytes		=	new BYTE[sizeInBytes];

			if ( NULL != bytes )
			{
				memset ( bytes, 0, sizeInBytes );

				DocFileFormat::FormatUtils::SetBytes( bytes, (unsigned short)oSTSHI.Size() );
				memcpy ( ( bytes + sizeof(unsigned short) ), (BYTE*)oSTSHI, oSTSHI.Size() );
			}
		}

		LPStshi (const LPStshi& oLPStshi) : bytes (NULL), sizeInBytes (oLPStshi.sizeInBytes)
		{
			bytes = new BYTE[sizeInBytes];

			if ( NULL != bytes )
			{
				memset ( bytes, 0, sizeInBytes );
				memcpy ( bytes, oLPStshi.bytes, sizeInBytes );
			}
		}

		virtual ~LPStshi()
		{
			RELEASEARRAYOBJECTS(bytes);
		}

		virtual operator BYTE*() const
		{
			return bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeInBytes;
		}

	private:

		BYTE*			bytes;
		unsigned int	sizeInBytes;
	};
}
