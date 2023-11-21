
#pragma once

#include "../../../DesktopEditor/common/Types.h"

namespace Docx2Doc
{
union Shd80
{
private:
	struct
	{
		BYTE icoFore:5;
		BYTE icoBack:5;
		BYTE ipat:6;
	} Shd80Struct;
	unsigned short Shd80UnsignedShort;

public:
	Shd80():
		Shd80UnsignedShort(0)
	{
		Shd80Struct.icoFore = 0x1F;
		Shd80Struct.icoBack = 0x1F;
		Shd80Struct.ipat = 0x3F;
	}

	explicit Shd80( BYTE _icoFore, BYTE _icoBack, BYTE _ipat ):
		Shd80UnsignedShort(0)
	{
		Shd80Struct.icoFore = _icoFore;
		Shd80Struct.icoBack = _icoBack;
		Shd80Struct.ipat = _ipat;
	}

	operator unsigned short() const
	{
		return this->Shd80UnsignedShort;
	}
};
}
