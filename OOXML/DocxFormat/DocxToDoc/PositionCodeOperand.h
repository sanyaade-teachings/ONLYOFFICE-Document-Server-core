
#pragma once

#include "../../../DesktopEditor/common/Types.h"

namespace Docx2Doc
{
union PositionCodeOperand
{
private:
	struct
	{
		BYTE padding:4;
		BYTE pcVert:2;
		BYTE pcHorz:2;
	} PositionCodeOperandStruct;

	BYTE PositionCodeOperandByte;

public:
	PositionCodeOperand() : PositionCodeOperandByte(0)
	{
	}

	explicit PositionCodeOperand( BYTE _pcVert, BYTE _pcHorz ) : PositionCodeOperandByte(0)
	{
		this->PositionCodeOperandStruct.padding = 0;
		this->PositionCodeOperandStruct.pcVert = _pcVert;
		this->PositionCodeOperandStruct.pcHorz = _pcHorz;
	}

	explicit PositionCodeOperand( BYTE _positionCodeOperand ) : PositionCodeOperandByte(_positionCodeOperand)
	{
	}

	operator BYTE() const
	{
		return this->PositionCodeOperandByte;
	}
};
}
