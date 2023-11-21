#pragma once

#include "LSD.h"

#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
	class StshiLsd: public IOperand
	{
	public:
		StshiLsd () : bytes(NULL), sizeInBytes(0)
		{

		}

		StshiLsd (const std::vector<LSD>& _mpstiilsd) : bytes(NULL), sizeInBytes(0), mpstiilsd(_mpstiilsd)
		{
			sizeInBytes	=	( sizeof(unsigned short) + ( sizeof(LSD) * mpstiilsd.size() ) );
			bytes		=	new BYTE[sizeInBytes];

			if ( NULL != bytes )
			{
				memset ( bytes, 0, sizeInBytes );
				DocFileFormat::FormatUtils::SetBytes ( bytes, (unsigned short)sizeof(LSD) );

				unsigned int lsdOffset = sizeof(unsigned short);

				for (std::vector<LSD>::iterator iter = mpstiilsd.begin(); iter != mpstiilsd.end(); ++iter)
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + lsdOffset ), (unsigned int)(*iter) );
					lsdOffset += sizeof(LSD);
				}
			}
		}

		StshiLsd (const StshiLsd& _stshiLsd) : bytes(NULL), sizeInBytes(_stshiLsd.sizeInBytes), mpstiilsd(_stshiLsd.mpstiilsd)
		{
			bytes = new BYTE[sizeInBytes];

			if ( NULL != bytes )
			{
				memset ( bytes, 0, sizeInBytes );
				memcpy ( bytes, _stshiLsd.bytes, sizeInBytes );
			}
		}

		virtual ~StshiLsd()
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

		std::vector<LSD>	mpstiilsd;

		BYTE*				bytes;
		unsigned int		sizeInBytes;
	};
}
