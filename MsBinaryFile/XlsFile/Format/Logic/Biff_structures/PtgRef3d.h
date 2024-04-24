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
#pragma once

#include "OperandPtg.h"
#include "../GlobalWorkbookInfo.h"
#include "BIFF12/CellRef.h"

namespace XLS
{

class CFRecord;

class PtgRef3d: public OperandPtg
{
	BASE_STRUCTURE_DEFINE_CLASS_NAME(PtgRef3d)
public:
	PtgRef3d(const unsigned short full_ptg_id, const CellRef& cell_base_ref_init);
	PtgRef3d(const unsigned short ixti, const std::wstring& word, const PtgDataType data_type, const CellRef& cell_base_ref_init);

	void set_base_ref(const CellRef& cell_base_ref);

	BiffStructurePtr clone();

	void fromString(const std::wstring& str);

	void loadFields(CFRecord& record) override;

	void writeFields(CFRecord& record) override;
	
	void assemble(AssemblerStack& ptg_stack, PtgQueue& extra_data, bool full_ref = false) override;

	static const unsigned short fixed_id = 0x1A;
private:
//biff8
	unsigned short			ixti;
	RgceLocRel				rgce_loc_rel;
	RgceLoc					rgce_loc;
	CellRef					cell_base_ref;
//biff5
	_UINT16					ixals;
	_UINT16					itabFirst;
	_UINT16					itabLast;
//biff12
    XLSB::RgceLoc           rgce_loc_xlsb;

	GlobalWorkbookInfoPtr	global_info;

};

} // namespace XLS

