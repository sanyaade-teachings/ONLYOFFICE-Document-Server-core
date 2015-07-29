#pragma once

#include "OfficeArtRecord.h"

namespace XLS
{
	class CFRecord;
}


namespace ODRAW
{;

class OfficeArtFDG : public OfficeArtRecord
{
	BASE_STRUCTURE_DEFINE_CLASS_NAME(OfficeArtFDG)
public:
	OfficeArtFDG();
	XLS::BiffStructurePtr clone();

	virtual void loadFields(XLS::CFRecord& record);
	virtual void storeFields(XLS::CFRecord& record);

public:
	unsigned int csp;
	unsigned int spidCur;
};

typedef boost::shared_ptr<OfficeArtFDG> OfficeArtFDGPtr;


} // namespace XLS
