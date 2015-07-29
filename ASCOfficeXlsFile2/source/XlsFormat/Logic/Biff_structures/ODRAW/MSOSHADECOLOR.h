#pragma once

#include "../BiffStructure.h"
#include "OfficeArtCOLORREF.h"
#include "../FixedPoint.h"

namespace XLS
{
	class CFRecord;
}


namespace ODRAW
{;

class MSOSHADECOLOR : public XLS::BiffStructure
{
	BASE_STRUCTURE_DEFINE_CLASS_NAME(MSOSHADECOLOR)
public:
	MSOSHADECOLOR();
	XLS::BiffStructurePtr clone();

	
	
	virtual void load(XLS::CFRecord& record);
	virtual void store(XLS::CFRecord& record);

public:
	OfficeArtCOLORREF color;
	OSHARED::FixedPoint position;
};

typedef boost::shared_ptr<MSOSHADECOLOR> MSOSHADECOLORPtr;


} // namespace XLS
