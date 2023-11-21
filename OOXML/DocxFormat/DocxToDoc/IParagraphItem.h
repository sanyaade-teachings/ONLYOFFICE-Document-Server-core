#pragma once

#include "Chpx.h"

#include "../../Base/SmartPtr.h"
#include "../../../MsBinaryFile/Common/Base/IVirtualConstructor.h"

namespace Docx2Doc
{
	struct IParagraphItem;

	typedef NSCommon::smart_ptr<IParagraphItem> IParagraphItemPtr;

	struct IParagraphItem : public IVirtualConstructor
	{
		virtual unsigned long GetTextSize() const = 0;
		virtual std::wstring GetAllText() const = 0;
		virtual std::vector<Chpx> GetRunProperties( std::vector<unsigned int>* runOffsets ) const = 0;
		virtual unsigned int PrlSize () const = 0;
		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* runOffsets ) const = 0;

		virtual ~IParagraphItem() {}
	};
}
