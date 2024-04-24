﻿/*
 * (c) Copyright Ascensio System SIA 2010-2024
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-6 Ernesta Birznieka-Upish
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include "PivotParsedFormula.h"

namespace XLS
{

PivotParsedFormula::PivotParsedFormula()
:	ParsedFormula(CellRef())
{
}

PivotParsedFormula& PivotParsedFormula::operator=(const std::wstring& value)
{
	ParsedFormula::operator = (value);
	return *this;
}

BiffStructurePtr PivotParsedFormula::clone()
{
	return BiffStructurePtr(new PivotParsedFormula(*this));
}

void PivotParsedFormula::load(CFRecord& record)
{	
    if (record.getGlobalWorkbookInfo()->Version < 0x0800)
    {
        unsigned short cce;

        record >> cce >> cSxName;
        rgce.load(record, cce);
    }
    else
    {
        _UINT32 cce;
        record >> cce;

        rgce.load(record, cce);

        _UINT32 cb;
        record >> cb;

        //rgcb.load(record, rgce.getPtgs(), is_part_of_a_revision_);

    }
}

void PivotParsedFormula::save(CFRecord& record)
{
	if (record.getGlobalWorkbookInfo()->Version < 0x0800)
	{
		_UINT16 cce = 0;
		record << cce;

		auto rdPtr = record.getRdPtr();

		rgce.save(record);

		cce = record.getRdPtr() - rdPtr;

		record.RollRdPtrBack(cce + 4);
		record << cce;
		record.skipNunBytes(cce);
	}
	else
	{
		_UINT32 size = 0;

		auto saving = [&](BiffStructure& rgceORrgb)
		{
			record << size;

			auto rdPtr = record.getRdPtr();

			rgceORrgb.save(record);

			size = record.getRdPtr() - rdPtr;

			record.RollRdPtrBack(size + 4);
			record << size;
			record.skipNunBytes(size);
		};

		saving(rgce);

		size = 0;
		record << size;

		//saving(rgcb);
	}
}

} // namespace XLS

