#pragma once

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
	class Stshif : public IOperand
	{
	public:

		Stshif ()
		{
			memset ( bytes, 0, SIZE_IN_BYTES );
		}

		Stshif (unsigned short cstd, bool StdfPost2000Exists, unsigned short stiMaxWhenSaved, short ftcAsci = 0, short ftcFE = 0, short ftcOther = 0 )
		{
			memset ( bytes, 0, SIZE_IN_BYTES);

			if ( cstd < 0x000F )
			{
				DocFileFormat::FormatUtils::SetBytes ( bytes, (unsigned short)0x000F );
			}
			else if ( cstd >= 0x0FFE )
			{
				DocFileFormat::FormatUtils::SetBytes ( bytes, (unsigned short)0x0FFE );
			}
			else
			{
				DocFileFormat::FormatUtils::SetBytes ( bytes, cstd );
			}

			if ( StdfPost2000Exists )
			{
				DocFileFormat::FormatUtils::SetBytes( ( bytes + sizeof(cstd) ), (unsigned short)0x0012 );
			}
			else
			{
				DocFileFormat::FormatUtils::SetBytes( ( bytes + sizeof(cstd) ), (unsigned short)0x000A );
			}

			DocFileFormat::FormatUtils::SetBytes( ( bytes + 4 ), (unsigned short)0x0001 );
			DocFileFormat::FormatUtils::SetBytes( ( bytes + 6 ), stiMaxWhenSaved );
			DocFileFormat::FormatUtils::SetBytes( ( bytes + 8 ), (unsigned short)0x000F );
			DocFileFormat::FormatUtils::SetBytes( ( bytes + 10 ), (unsigned short)0x0000 );
			DocFileFormat::FormatUtils::SetBytes( ( bytes + 12 ), ftcAsci );
			DocFileFormat::FormatUtils::SetBytes( ( bytes + 14 ), ftcFE );
			DocFileFormat::FormatUtils::SetBytes( ( bytes + 16 ), ftcOther );
		}

		Stshif (const Stshif& stshif)
		{
			memset ( bytes, 0, SIZE_IN_BYTES );
			memcpy ( bytes, stshif.bytes, SIZE_IN_BYTES );
		}

		virtual ~Stshif()
		{
		}

		virtual operator BYTE*() const
		{
			return (BYTE*)(bytes);
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return SIZE_IN_BYTES;
		}

	private:
		static const BYTE	SIZE_IN_BYTES = 18;
		BYTE				bytes[SIZE_IN_BYTES];
	};
}
