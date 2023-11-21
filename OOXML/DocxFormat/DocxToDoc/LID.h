#pragma once

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/DocFile/LanguageId.h"

namespace Docx2Doc
{
class LID: public IOperand
{
private:
	DocFileFormat::LanguageCode lid;

public:
	LID() : lid(DocFileFormat::Nothing)
	{
	}

	explicit LID( DocFileFormat::LanguageCode _lid ):
		lid(_lid)
	{
	}

	virtual ~LID()
	{
	}

	virtual operator BYTE*() const
	{
		return (BYTE*)(&(this->lid));
	}

	virtual operator const BYTE*() const
	{
		return (const BYTE*)(&(this->lid));
	}

	virtual unsigned int Size() const
	{
		return sizeof(unsigned short);
	}

	operator unsigned int() const
	{
		return (unsigned int)this->lid;
	}
};
}
