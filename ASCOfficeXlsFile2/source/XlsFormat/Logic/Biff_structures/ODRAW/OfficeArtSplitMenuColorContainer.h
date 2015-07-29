#pragma once

#include "OfficeArtRecord.h"
#include "MSOCR.h"

namespace XLS
{
	class CFRecord;
}


namespace ODRAW
{;

class OfficeArtSplitMenuColorContainer : public OfficeArtRecord
{
	BASE_STRUCTURE_DEFINE_CLASS_NAME(OfficeArtSplitMenuColorContainer)
public:
	OfficeArtSplitMenuColorContainer();
	XLS::BiffStructurePtr clone();

	
	
	virtual void loadFields(XLS::CFRecord& record);
	virtual void storeFields(XLS::CFRecord& record);

	// overriden
	const unsigned short GetInstanceToStore();

public:
	std::vector<MSOCR> smca;
};

typedef boost::shared_ptr<OfficeArtSplitMenuColorContainer> OfficeArtSplitMenuColorContainerPtr;


} // namespace XLS
