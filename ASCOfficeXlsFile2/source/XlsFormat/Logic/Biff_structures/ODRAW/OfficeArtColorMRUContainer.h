#pragma once

#include "OfficeArtRecord.h"
#include "MSOCR.h"

namespace XLS
{
	class CFRecord;
}


namespace ODRAW
{;

class OfficeArtColorMRUContainer : public OfficeArtRecord
{
	BASE_STRUCTURE_DEFINE_CLASS_NAME(OfficeArtColorMRUContainer)
public:
	OfficeArtColorMRUContainer();
	XLS::BiffStructurePtr clone();

	
	
	virtual void loadFields(XLS::CFRecord& record);
	virtual void storeFields(XLS::CFRecord& record);

	// overriden
	const unsigned short GetInstanceToStore();

public:
	std::vector<MSOCR> rgmsocr;
};

typedef boost::shared_ptr<OfficeArtColorMRUContainer> OfficeArtColorMRUContainerPtr;


} // namespace XLS
