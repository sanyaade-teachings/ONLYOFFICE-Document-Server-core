#pragma once

#include "Prl.h"
#include "../../../MsBinaryFile/Common/Base/IVirtualConstructor.h"

namespace Docx2Doc
{
	struct IRunItem : public IVirtualConstructor
	{
		virtual unsigned long GetTextSize() const = 0;
		virtual std::wstring GetAllText() const = 0;
		virtual std::vector<Prl> GetRunProperties() const = 0;
		virtual unsigned int PrlSize () const = 0;
		virtual ~IRunItem() {}
	};
}
