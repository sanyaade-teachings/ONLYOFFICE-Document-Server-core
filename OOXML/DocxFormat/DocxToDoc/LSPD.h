
#pragma once

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
class LSPD: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 4;

	short dyaLine;
	short fMultLinespace;

	BYTE bytes[SIZE_IN_BYTES];

public:
	LSPD():
		dyaLine(0), fMultLinespace(0)
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );
	}

	explicit LSPD( short _dyaLine, bool _fMultLinespace = true ):
		dyaLine(0), fMultLinespace(0)
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		this->dyaLine = _dyaLine;
		( _fMultLinespace ) ? ( this->fMultLinespace = 0x0001 ) : ( this->fMultLinespace = 0x0000 );

		DocFileFormat::FormatUtils::SetBytes( this->bytes, this->dyaLine );
		DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(this->dyaLine) ), this->fMultLinespace );
	}

	LSPD( const LSPD& _lspd ):
		dyaLine(_lspd.dyaLine), fMultLinespace(_lspd.fMultLinespace)
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _lspd.bytes, SIZE_IN_BYTES );
	}

	virtual ~LSPD()
	{
	}

	virtual operator BYTE*() const
	{
		return (BYTE*)this->bytes;
	}

	virtual operator const BYTE*() const
	{
		return (const BYTE*)this->bytes;
	}

	virtual unsigned int Size() const
	{
		return SIZE_IN_BYTES;
	}
};
}
