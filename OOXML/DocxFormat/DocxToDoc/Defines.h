/*
 * (c) Copyright Ascensio System SIA 2010-2023
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

namespace Docx2Doc
{
	namespace FIB_OFFSET
	{
		enum FIB
		{
			csw					=	32,
			cslw				=	62,
			cbRgFcLcb			=	152
		};

		enum FibBase
		{
			wIdent				=	0,
			nFib				=	2,
			lid					=	6,
			pnNext				=	8,
			nFibBack			=	12,
			lKey				=	14,
			envr				=	18
		};

		enum FibRgLw97
		{
			cbMac				=	64,
			ccpText				=	76,
			ccpFtn				=	80,
			ccpHdd				=	84,
			ccpAtn				=	92,
			ccpEdn				=	96,
			ccpTxbx 			=	100,
			ccpHdrTxbx 			=	104
		};

		enum FibRgFcLcb97
		{
			fcStshfOrig			=	154,
			lcbStshfOrig		=	158,
			fcStshf				=	162,
			lcbStshf			=	166,
			fcPlcfSed			=	202,
			lcbPlcfSed			=	206,
			fcSttbfFfn			=	274,
			lcbSttbfFfn			=	278,
			fcDop				=	402,
			lcbDop				=	406,
			fcClx				=	418,
			lcbClx				=	422,
			fcPlcSpaMom			=	474,
			lcbPlcSpaMom		=	478,
			fcPlcSpaHdr			=	482,
			lcbPlcSpaHdr		=	486,
			fcDggInfo			=	554,
			lcbDggInfo			=	558,

			fcPlcftxbxTxt		=	602,
			lcbPlcftxbxTxt		=	606,

			fcPlcfHdrtxbxTxt	=	618,
			lcbPlcfHdrtxbxTxt	=	622,

			fcPlcfTxbxBkd		=	754,
			lcbPlcfTxbxBkd		=	758,
			fcPlcfTxbxHdrBkd	=	762,
			lcbPlcfTxbxHdrBkd	=	766
		};
	}
}
