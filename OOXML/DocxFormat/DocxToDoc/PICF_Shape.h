
#pragma once

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"

namespace Docx2Doc
{
class PICF_Shape: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 14;
	BYTE bytes[SIZE_IN_BYTES];

public:
	PICF_Shape()
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );
	}

	PICF_Shape( const PICF_Shape& _pICF_Shape )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _pICF_Shape.bytes, SIZE_IN_BYTES );
	}

	virtual ~PICF_Shape()
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
};
}
