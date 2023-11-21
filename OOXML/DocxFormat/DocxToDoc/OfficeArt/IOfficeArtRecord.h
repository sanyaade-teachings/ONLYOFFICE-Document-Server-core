#pragma once

#include "../../../Base/SmartPtr.h"

namespace OfficeArt
{
	struct IOfficeArtRecord
	{
		virtual operator const BYTE* () const = 0;
		virtual operator BYTE* () const = 0;
		virtual unsigned int Size() const = 0;
		virtual IOfficeArtRecord* New() const = 0;
		virtual IOfficeArtRecord* Clone() const = 0;
		virtual ~IOfficeArtRecord() {}
	};

	typedef NSCommon::smart_ptr<IOfficeArtRecord> OfficeArtRecordPtr;
}
