
#pragma once

#include "../../../DesktopEditor/common/Types.h"

namespace Docx2Doc
{
union grfhic
{
private:
	struct
	{
		BYTE fhicChecked:1;
		BYTE fhicFormat:1;
		BYTE fhicListText:1;
		BYTE fhicPeriod:1;
		BYTE fhicLeft1:1;
		BYTE fhicListTab:1;
		BYTE unused:1;
		BYTE fhicBullet:1;
	} grfhicStruct;

	BYTE grfhicByte;

public:
	grfhic():
		grfhicByte(0)
	{
	}

	explicit grfhic( bool _fhicChecked, bool _fhicFormat, bool _fhicListText, bool _fhicPeriod,
					 bool _fhicLeft1, bool _fhicListTab, bool _fhicBullet ):
		grfhicByte(0)
	{
		( _fhicChecked ) ? ( this->grfhicStruct.fhicChecked = 1 ) : ( this->grfhicStruct.fhicChecked = 0 );
		( _fhicFormat ) ? ( this->grfhicStruct.fhicFormat = 1 ) : ( this->grfhicStruct.fhicFormat = 0 );
		( _fhicListText ) ? ( this->grfhicStruct.fhicListText = 1 ) : ( this->grfhicStruct.fhicListText = 0 );
		( _fhicPeriod ) ? ( this->grfhicStruct.fhicPeriod = 1 ) : ( this->grfhicStruct.fhicPeriod = 0 );
		( _fhicLeft1 ) ? ( this->grfhicStruct.fhicLeft1 = 1 ) : ( this->grfhicStruct.fhicLeft1 = 0 );
		( _fhicListTab ) ? ( this->grfhicStruct.fhicListTab = 1 ) : ( this->grfhicStruct.fhicListTab = 0 );
		this->grfhicStruct.unused = 0;
		( _fhicBullet ) ? ( this->grfhicStruct.fhicBullet = 1 ) : ( this->grfhicStruct.fhicBullet = 0 );
	}

	explicit grfhic( BYTE _grfhic ):
		grfhicByte(_grfhic)
	{
	}

	operator BYTE() const
	{
		return this->grfhicByte;
	}
};
}
