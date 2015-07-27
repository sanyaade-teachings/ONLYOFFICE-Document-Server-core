#pragma once

#include "BiffStructure.h"
#include <Logic/Biff_structures/Rgce.h>
#include <Logic/Biff_structures/RgbExtra.h>

namespace XLS
{;

class CFRecord;

class ParsedFormula : public BiffStructure
{
public:
	ParsedFormula(const CellRef& cell_base_ref);

	void setCCE(const size_t cce_val); // mandatory to call before any use of "cce"
	const size_t getCCE() const;
	const bool HasPtgTbl() const;

	const std::wstring getAssembledFormula() const;
	
	//const bool parseStringFormula(const std::wstring formula, const std::wstring & tag_name);

	Rgce rgce;
	RgbExtra rgcb;

	size_t cce; // Size of rgce variable. Setting explicit is mandatory
	bool cce_is_set;
};

} // namespace XLS

