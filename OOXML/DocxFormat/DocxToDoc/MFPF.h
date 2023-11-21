#pragma once

#include "Constants.h"

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
class MFPF: public IOperand
{
private:
	Constants::PictureDataFormat mm;
	static const BYTE SIZE_IN_BYTES = 8;
	BYTE bytes[SIZE_IN_BYTES];

public:
	MFPF() : mm(Constants::MM_SHAPE)
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		DocFileFormat::FormatUtils::SetBytes( this->bytes, (short)(this->mm) );
	}

	explicit MFPF( Constants::PictureDataFormat _mm ) : mm(_mm)
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		DocFileFormat::FormatUtils::SetBytes( this->bytes, (short)(this->mm) );
	}

	MFPF( const MFPF& _mFPF )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _mFPF.bytes, SIZE_IN_BYTES );
	}

	virtual ~MFPF()
	{
	}

	virtual operator BYTE*() const
	{
		return (BYTE*)(this->bytes);
	}

	virtual operator const BYTE*() const
	{
		return (const BYTE*)this->bytes;
	}

	virtual unsigned int Size() const
	{
		return sizeof(this->bytes);
	}

	operator Constants::PictureDataFormat() const
	{
		return this->mm;
	}
};
}
