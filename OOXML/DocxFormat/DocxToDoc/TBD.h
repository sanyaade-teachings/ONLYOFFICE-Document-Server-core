
#pragma once

#include "Constants.h"
#include "../../../DesktopEditor/common/Types.h"

namespace Docx2Doc
{
union TBD
{
private:
	struct
	{
		BYTE jc:3;
		BYTE tlc:3;
		BYTE UNUSED:2;
	} TBDStruct;
	BYTE TBDByte;

public:
	explicit TBD( BYTE _tbd = 0 ):
		TBDByte(_tbd)
	{
	}

	TBD( Constants::TabJC _jc, Constants::TabLC _tlc ):
		TBDByte(0)
	{
		this->TBDStruct.jc = (BYTE)_jc;
		this->TBDStruct.tlc = (BYTE)_tlc;
	}

	operator BYTE() const
	{
		return this->TBDByte;
	}
};
}
