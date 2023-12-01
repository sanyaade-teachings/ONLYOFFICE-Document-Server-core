
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

#include <map>
#include <string>
#include <algorithm>
#include <math.h>

#include "Prl.h"
#include "Constants.h"
#include "CSSAOperand.h"
#include "COLORREF.h"
#include "SHDOperand.h"
//#include "..\Common\SPRMCodes.h"

#include "Brc.h"
#include "Brc80MayBeNil.h"

#include "TableBrc80Operand.h"
#include "TableBrcOperand.h"
#include "ItcFirstLim.h"

/*#include "Logic\TCMar.h"
#include "Styles.h"
#include "Logic\Shading.h"
#include "Logic\Color.h"
#include "Logic\ColorsTable.h"
#include "Logic\Table.h"
#include "Logic\TableBorders.h"
#include "Logic\TableStyleProperties.h"
#include "Logic\TableCellBorders.h"*/

#include "../../DocxFormat/Logic/Table.h"
#include "../../DocxFormat/Logic/TableProperty.h"
#include "../../DocxFormat/Styles.h"

#include "../../PPTXFormat/Logic/Colors/ColorBase.h"

typedef std::vector<Docx2Doc::Shd> ShdList;

namespace DOCXDOCUTILS
{
	inline int ShadingPattern (const std::wstring& type)
	{
		int ipat = 0;

		if(std::wstring(L"clear") == type)
			ipat = 0;
		else if(std::wstring(L"nil") == type)
			ipat = 0;
		else if(std::wstring(L"solid") == type)
			ipat = 1;
		else if(std::wstring(L"horzStripe") == type)
			ipat = 14;
		else if(std::wstring(L"vertStripe") == type)
			ipat = 15;
		else if(std::wstring(L"diagStripe") == type)
			ipat = 16;
		else if(std::wstring(L"reverseDiagStripe") == type)
			ipat = 17;
		else if(std::wstring(L"horzCross") == type)
			ipat = 18;
		else if(std::wstring(L"diagCross") == type)
			ipat = 19;
		else if(std::wstring(L"thinHorzStripe") == type)
			ipat = 20;
		else if(std::wstring(L"thinVertStripe") == type)
			ipat = 21;
		else if(std::wstring(L"thinDiagStripe") == type)
			ipat = 22;
		else if(std::wstring(L"thinReverseDiagStripe") == type)
			ipat = 23;
		else if(std::wstring(L"thinHorzCross") == type)
			ipat = 24;
		else if(std::wstring(L"thinDiagCross") == type)
			ipat = 25;
		else if(std::wstring(L"pct5") == type)
			ipat = 2;
		else if(std::wstring(L"pct10") == type)
			ipat = 3;
		else if(std::wstring(L"pct12") == type)
			ipat = 37;
		else if(std::wstring(L"pct15") == type)
			ipat = 38;
		else if(std::wstring(L"pct20") == type)
			ipat = 4;
		else if(std::wstring(L"pct25") == type)
			ipat = 5;
		else if(std::wstring(L"pct30") == type)
			ipat = 6;
		else if(std::wstring(L"pct35") == type)
			ipat = 43;
		else if(std::wstring(L"pct37") == type)
			ipat = 44;
		else if(std::wstring(L"pct40") == type)
			ipat = 7;
		else if(std::wstring(L"pct45") == type)
			ipat = 46;
		else if(std::wstring(L"pct50") == type)
			ipat = 8;
		else if(std::wstring(L"pct55") == type)
			ipat = 49;
		else if(std::wstring(L"pct60") == type)
			ipat = 9;
		else if(std::wstring(L"pct62") == type)
			ipat = 51;
		else if(std::wstring(L"pct65") == type)
			ipat = 52;
		else if(std::wstring(L"pct70") == type)
			ipat = 10;
		else if(std::wstring(L"pct75") == type)
			ipat = 11;
		else if(std::wstring(L"pct80") == type)
			ipat = 12;
		else if(std::wstring(L"pct85") == type)
			ipat = 57;
		else if(std::wstring(L"pct87") == type)
			ipat = 58;
		else if(std::wstring(L"pct90") == type)
			ipat = 13;
		else if(std::wstring(L"pct95") == type)
			ipat = 60;

		return ipat;
	}

	inline Docx2Doc::Constants::Fts TableWidthUnitsFromString (const std::wstring& type)
	{
		if (type == std::wstring(L"nil"))
			return Docx2Doc::Constants::ftsNil;
		else if (type == std::wstring(L"auto"))
			return Docx2Doc::Constants::ftsAuto;
		else if (type == std::wstring(L"pct"))
			return Docx2Doc::Constants::ftsPercent;
		else if (type == std::wstring(L"dxa"))
			return Docx2Doc::Constants::ftsDxa;

		return Docx2Doc::Constants::ftsNil;
	}

	inline Docx2Doc::Prl GetOpTop  (const OOX::Logic::CTcMar& oTCMar, int nCells)
	{
		Docx2Doc::CSSAOperand opCSSA (Docx2Doc::CSSA(Docx2Doc::ItcFirstLim(0, nCells),
			Docx2Doc::Constants::fbrcTop,
			TableWidthUnitsFromString (oTCMar.m_oTop->m_oType->ToString() ),
			oTCMar.m_oTop->m_oW->GetValueIntegerPercent()));

		return Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)opCSSA );
	}

	inline Docx2Doc::Prl GetOpLeft (const OOX::Logic::CTcMar& oTCMar, int nCells)
	{
		Docx2Doc::CSSAOperand opCSSA(Docx2Doc::CSSA( Docx2Doc::ItcFirstLim(0, nCells),
			Docx2Doc::Constants::fbrcLeft,
			TableWidthUnitsFromString (oTCMar.m_oStart->m_oType->ToString()),
			oTCMar.m_oStart->m_oW->GetValueIntegerPercent()));

		return Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)opCSSA );
	}

	inline Docx2Doc::Prl GetOpRight (const OOX::Logic::CTcMar& oTCMar, int nCells)
	{
		Docx2Doc::CSSAOperand opCSSA( Docx2Doc::CSSA( Docx2Doc::ItcFirstLim(0, nCells),
			Docx2Doc::Constants::fbrcRight,
			DOCXDOCUTILS::TableWidthUnitsFromString (oTCMar.m_oEnd->m_oType->ToString()),
			oTCMar.m_oEnd->m_oW->GetValueIntegerPercent() ) );

		return Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)opCSSA );
	}

	inline Docx2Doc::Prl GetOpBottom (const OOX::Logic::CTcMar& oTCMar, int nCells)
	{
		Docx2Doc::CSSAOperand opCSSA( Docx2Doc::CSSA( Docx2Doc::ItcFirstLim(0, nCells),
			Docx2Doc::Constants::fbrcBottom,
			DOCXDOCUTILS::TableWidthUnitsFromString (oTCMar.m_oBottom->m_oType->ToString()),
			oTCMar.m_oBottom->m_oW->GetValueIntegerPercent() ) );

		return Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)opCSSA );
	}

	const int HexChar2Int(const char value)
	{
		if (value >= '0' && value <= '9')
			return value - '0';
		if (value >= 'a' && value <= 'f')
			return 10 + value - 'a';
		if (value >= 'A' && value <= 'F')
			return 10 + value - 'A';
		return 0;
	}

	const int HexString2Int(const std::wstring& value)
	{
		int summa = 0;
		for (int i = 0; i != value.length(); ++i)
			summa += HexChar2Int((char)value[i]) << (4 * (value.length() - i - 1));
		return summa;
	}

	inline Docx2Doc::Shd GetBackGroundShading (const nullable<ComplexTypes::Word::CShading>& oShading)
	{
		// <w:shd w:val="clear" w:color="auto" w:fill="4F81BD" w:themeFill="accent1"/>

		int nFillValue	=	0;
		int nFillAuto	=	0;
		int nColorValue	=	0;
		int nColorAuto	=	0;
		int nIpat		=	0;		

		if (oShading.is_init())
		{
			if (oShading->m_oFill.is_init())
			{
				if (std::wstring(L"auto") == (oShading->m_oFill->ToString()))
					nFillAuto	=	Docx2Doc::COLORREF::cvAuto;
				else
					nFillValue	=	HexString2Int(oShading->m_oFill->ToString());
			}

			if (oShading->m_oColor.is_init())
			{
				if (std::wstring(L"auto") == (oShading->m_oColor->ToString()))
					nColorAuto	=	Docx2Doc::COLORREF::cvAuto;
				else
					nColorValue	=	HexString2Int(oShading->m_oColor->ToString());
			}

			if (oShading->m_oVal.is_init())
				nIpat			=	ShadingPattern (oShading->m_oVal->ToString());

			return Docx2Doc::Shd(Docx2Doc::COLORREF((int)(nColorValue | nColorAuto)), Docx2Doc::COLORREF(nFillValue | nFillAuto), nIpat);
		}

		return Docx2Doc::Shd();
	}
}

namespace DOCXDOCUTILS	//	Help Borders and Fill 
{
	class CTblBorders
	{
	public:
		enum Border
		{
			TOP_BORDER		=	0,
			BOTTOM_BORDER	=	1,
			LEFT_BORDER		=	2,
			RIGHT_BORDER	=	3,
			INSIDEH_BORDER	=	4,
			INSIDEV_BORDER	=	5
		};

	public:
		CTblBorders ()
		{
		}

		CTblBorders (OOX::CStyle oStyle) : m_oStyle (oStyle)
		{
		}

		CTblBorders (const OOX::Logic::CTbl& oXmlTable, OOX::CStyle oStyle, int bCacheTableStyles = TRUE) : m_oStyle (oStyle)
		{
			/*GetBrcMap ();

			// параметры могут быть не правильно выставлены, поэтому стоит прочекать стили на существование

			m_bHaveBeginRow			=	oXmlTable.tblPr->firstRow;
			m_bHaveEndRow			=	oXmlTable.tblPr->lastRow;
			m_bHaveBeginCol			=	oXmlTable.tblPr->firstColumn;
			m_bHaveEndCol			=	oXmlTable.tblPr->lastColumn;

			m_bNoHBand				=	oXmlTable.tblPr->noHBand;
			m_bNoVBand				=	oXmlTable.tblPr->noVBand;
			
			m_bStyleFirstRow		=	FALSE;
			m_bStyleBand1Horz		=	FALSE;
			m_bStyleBand1Vert		=	FALSE;
			m_bStyleFirstCol		=	FALSE;
			m_bStyleLastRow			=	FALSE;
			m_bStyleLastCol			=	FALSE;

			m_bExistStyleFirstRow	=	FALSE;
			m_bExistStyleBand1Horz	=	FALSE;
			m_bExistStyleBand1Vert	=	FALSE;
			m_bExistStyleFirstCol	=	FALSE;
			m_bExistStyleLastRow	=	FALSE;
			m_bExistStyleLastCol	=	FALSE;

			if (bCacheTableStyles)
			{
				m_nRowBand			=	1;
				if(m_oStyle.tblPr.is_init())
					m_nRowBand		=	m_oStyle.tblPr->tblStyleRowBandSize;

				int nBandCol		=	1;
				if(m_oStyle.tblPr.is_init())
					m_nBandCol		=	m_oStyle.tblPr->tblStyleColBandSize;

				m_bStyleBorders		=	FALSE;

				if (m_oStyle.tblPr.is_init())
				{
					if (m_oStyle.tblPr->tblBorders.is_init())
					{
						m_oStyleBorders	=	m_oStyle.tblPr->tblBorders;
						m_bStyleBorders	=	TRUE;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("firstRow")))
				{
					m_bExistStyleFirstRow	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("firstRow"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleFirstRow	=	TRUE;
						m_oBordersFirstRow	=	oInternalStyle.tcPr->tblBorders;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("lastRow")))
				{
					m_bExistStyleLastRow	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("lastRow"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleLastRow		=	TRUE;
						m_oBordersLastRow	=	oInternalStyle.tcPr->tblBorders;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("band1Horz")))
				{
					m_bExistStyleBand1Horz	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("band1Horz"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleBand1Horz	=	TRUE;
						m_oBordersBand1Horz	=	oInternalStyle.tcPr->tblBorders;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("band1Vert")))
				{
					m_bExistStyleBand1Vert	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("band1Vert"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleBand1Vert	=	TRUE;
						m_oBordersBand1Vert	=	oInternalStyle.tcPr->tblBorders;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("band2Horz")))
				{
					m_bExistStyleBand2Horz	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("band2Horz"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleBand2Horz	=	TRUE;
						m_oBordersBand2Horz	=	oInternalStyle.tcPr->tblBorders;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("band2Vert")))
				{
					m_bExistStyleBand2Vert	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("band2Vert"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleBand2Vert	=	TRUE;
						m_oBordersBand2Vert	=	oInternalStyle.tcPr->tblBorders;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("firstCol")))
				{
					m_bExistStyleFirstCol	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("firstCol"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleFirstCol	=	TRUE;
						m_oBordersFirstCol	=	oInternalStyle.tcPr->tblBorders;
					}
				}

				if (m_oStyle.tableStyles->exist(std::string("lastCol")))
				{
					m_bExistStyleFirstCol	=	TRUE;

					const OOX::Logic::CTableStyleProperties& oInternalStyle = m_oStyle.tableStyles->operator [](std::string("lastCol"));
					if (oInternalStyle.tcPr.is_init() && oInternalStyle.tcPr->tblBorders.is_init())
					{
						m_bStyleLastCol		=	TRUE;
						m_oBordersLastCol	=	oInternalStyle.tcPr->tblBorders;
					}
				}
			}*/
		}

		//
		inline int Append (int nX, int nY, int nCX, int nCY, const nullable<OOX::Logic::CTblBorders>& oTableBorders, const nullable<OOX::Logic::CTcBorders>& oInternalBorders)
		{
			m_nIndCellX				=	nX;
			m_nIndCellY				=	nY;
			
			m_nCellsX				=	nCX - 1;
			m_nCellsY				=	nCY - 1;

			/*

			m_oBrc80MayBeNilTop		=	Docx2Doc::Brc80MayBeNil(2, 1, 1, 0, false, false);
			m_oBrc80MayBeNilBottom	=	Docx2Doc::Brc80MayBeNil(2, 1, 1, 0, false, false);
			m_oBrc80MayBeNilLeft	=	Docx2Doc::Brc80MayBeNil(2, 1, 1, 0, false, false);
			m_oBrc80MayBeNilRight	=	Docx2Doc::Brc80MayBeNil(2, 1, 1, 0, false, false);

			m_oBrcTop				=	Docx2Doc::Brc(Docx2Doc::COLORREF(HexString2Int(std::string ("000000"))), 1, 0, 0, false, false);
			m_oBrc80Top				=	Docx2Doc::Brc80MayBeNil(0, 0, 0, 0, false, false);

			m_oBrcBottom			=	Docx2Doc::Brc(Docx2Doc::COLORREF(HexString2Int(std::string ("000000"))), 1, 0, 0, false, false);
			m_oBrc80Bottom			=	Docx2Doc::Brc80MayBeNil(0, 0, 0, 0, false, false);

			m_oBrcLeft				=	Docx2Doc::Brc(Docx2Doc::COLORREF(HexString2Int(std::string ("000000"))), 1, 0, 0, false, false);
			m_oBrc80Left			=	Docx2Doc::Brc80MayBeNil(0, 0, 0, 0, false, false);

			m_oBrcRight				=	Docx2Doc::Brc(Docx2Doc::COLORREF(HexString2Int(std::string ("000000"))), 1, 0, 0, false, false);
			m_oBrc80Right			=	Docx2Doc::Brc80MayBeNil(0, 0, 0, 0, false, false);

			// for test

			m_oBrcTop				=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xFF0000), 50, 1, 0, false, false);
			m_oBrc80Top				=	Docx2Doc::Brc80MayBeNil(50, 1, 0, 0, false, false);
			m_oBrcBottom			=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xFF), 50, 1, 0, false, false);
			m_oBrc80Bottom			=	Docx2Doc::Brc80MayBeNil(50, 1, 0, 0, false, false);
			m_oBrcLeft				=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xFFFF00), 50, 1, 0, false, false);
			m_oBrc80Left			=	Docx2Doc::Brc80MayBeNil(50, 1, 0, 0, false, false);
			m_oBrcRight				=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xF0F0FF), 50, 1, 0, false, false);
			m_oBrc80Right			=	Docx2Doc::Brc80MayBeNil(50, 1, 0, 0, false, false);

			*/

			SetNilBrc (TOP_BORDER);
			SetNilBrc (BOTTOM_BORDER);
			SetNilBrc (LEFT_BORDER);
			SetNilBrc (RIGHT_BORDER);

			ReadTopNillBorder	 (oTableBorders);
			ReadBottomNillBorder (oTableBorders);
			ReadLeftNillBorder	 (oTableBorders);
			ReadRightNillBorder	 (oTableBorders);

			AppendCellBorder (TOP_BORDER,	 oTableBorders, oInternalBorders);
			AppendCellBorder (BOTTOM_BORDER, oTableBorders, oInternalBorders);
			AppendCellBorder (LEFT_BORDER,	 oTableBorders, oInternalBorders);
			AppendCellBorder (RIGHT_BORDER,  oTableBorders, oInternalBorders);

			return TRUE;
		}

		inline int ReadTopNillBorder (const nullable<OOX::Logic::CTblBorders>& oBorders)
		{
			/*if (oBorders.is_init())
			{				
				if (oBorders->top.is_init())
				{
					m_oBrc80MayBeNilTop	= Docx2Doc::Brc80MayBeNil(oBorders->top.get_value_or_default().Bdr->Sz.get_value_or_default(),
						m_oBrcTypeMap[oBorders->top.get_value_or_default().Bdr->Value], 
						ColorToIco (oBorders->top.get_value_or_default().Bdr->Color.get_value_or_default()), 
						oBorders->top.get_value_or_default().Bdr->Space.get_value_or_default(), 
						false, 
						false);

					return TRUE;
				}
			}*/

			return FALSE;
		}

		inline int ReadBottomNillBorder (const nullable<OOX::Logic::CTblBorders>& oBorders)
		{
			/*if (oBorders.is_init())
			{				
				if (oBorders->bottom.is_init())
				{
					m_oBrc80MayBeNilBottom	= Docx2Doc::Brc80MayBeNil(oBorders->bottom.get_value_or_default().Bdr->Sz.get_value_or_default(),
						m_oBrcTypeMap[oBorders->bottom.get_value_or_default().Bdr->Value], 
						ColorToIco (oBorders->bottom.get_value_or_default().Bdr->Color.get_value_or_default()), 
						oBorders->bottom.get_value_or_default().Bdr->Space.get_value_or_default(), 
						false, 
						false);

					return TRUE;
				}
			}*/

			return FALSE;
		}

		inline int ReadLeftNillBorder (const nullable<OOX::Logic::CTblBorders>& oBorders)
		{
			/*if (oBorders.is_init())
			{				
				if (oBorders->left.is_init())
				{
					m_oBrc80MayBeNilLeft = Docx2Doc::Brc80MayBeNil(oBorders->left.get_value_or_default().Bdr->Sz.get_value_or_default(),
						m_oBrcTypeMap[oBorders->left.get_value_or_default().Bdr->Value], 
						ColorToIco (oBorders->left.get_value_or_default().Bdr->Color.get_value_or_default()), 
						oBorders->left.get_value_or_default().Bdr->Space.get_value_or_default(), 
						false, 
						false);

					return TRUE;
				}
			}*/

			return FALSE;
		}

		inline int ReadRightNillBorder (const nullable<OOX::Logic::CTblBorders>& oBorders)
		{
			/*if (oBorders.is_init())
			{				
				if (oBorders->right.is_init())
				{
					m_oBrc80MayBeNilRight = Docx2Doc::Brc80MayBeNil(oBorders->right.get_value_or_default().Bdr->Sz.get_value_or_default(),
						m_oBrcTypeMap[oBorders->right.get_value_or_default().Bdr->Value], 
						ColorToIco (oBorders->right.get_value_or_default().Bdr->Color.get_value_or_default()), 
						oBorders->right.get_value_or_default().Bdr->Space.get_value_or_default(), 
						false, 
						false);

					return TRUE;
				}
			}*/

			return FALSE;
		}

		//
		inline const std::vector<Docx2Doc::TableBrcOperand>& GetSpecificationBorders () const
		{
			return m_oBrcs;
		}

		inline const std::vector<Docx2Doc::TableBrc80Operand>& GetDescriptBorders () const
		{
			return m_oBrc80s;
		}

		inline const Docx2Doc::Brc80MayBeNil& GetTopNillBorder () const
		{
			return m_oBrc80MayBeNilTop;
		}

		inline const Docx2Doc::Brc80MayBeNil& GetBottomNillBorder () const
		{
			return m_oBrc80MayBeNilBottom;
		}

		inline const Docx2Doc::Brc80MayBeNil& GetLeftNillBorder () const
		{
			return m_oBrc80MayBeNilLeft;
		}

		inline const Docx2Doc::Brc80MayBeNil& GetRightNillBorder () const
		{
			return m_oBrc80MayBeNilRight;
		}

		//
		inline void Clean ()
		{
			m_oBrcs.clear ();
			m_oBrc80s.clear ();
		}

		//
		inline std::map<std::string, BYTE>& GetBrcMap ()
		{
			if (0 == m_oBrcTypeMap.size())
			{
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "none" ), 0x00 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "single" ), 0x01 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thick" ), 0x02 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "double" ), 0x03 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "hairline" ), 0x05 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "dotted" ), 0x06 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "dashed" ), 0x07 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "dotDash" ), 0x08 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "dotDotDash" ), 0x09 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "triple" ), 0x0A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thinThickSmallGap" ), 0x0B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thickThinSmallGap" ), 0x0C ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thinThickThinSmallGap" ), 0x0D ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thinThickMediumGap" ), 0x0E ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thickThinMediumGap" ), 0x0F ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thinThickThinMediumGap" ), 0x10 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thinThickLargeGap" ), 0x11 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thickThinLargeGap" ), 0x12 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "thinThickThinLargeGap" ), 0x13 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "wave" ), 0x14 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "doubleWave" ), 0x15 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "dashSmallGap" ), 0x16 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "dashDotStroked" ), 0x17 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "threeDEmboss" ), 0x18 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "threeDEngrave" ), 0x19 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "outset" ), 0x1A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "inset" ), 0x1B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "apples" ), 0x40 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "archedScallops" ), 0x41 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "babyPacifier" ), 0x42 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "babyRattle" ), 0x43 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "balloons3Colors" ), 0x44 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "balloonsHotAir" ), 0x45 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicBlackDashes" ), 0x46 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicBlackDots" ), 0x47 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicBlackSquares" ), 0x48 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicThinLines" ), 0x49 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicWhiteDashes" ), 0x4A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicWhiteDots" ), 0x4B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicWhiteSquares" ), 0x4C ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicWideInline" ), 0x4D ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicWideMidline" ), 0x4E ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "basicWideOutline" ), 0x4F ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "bats" ), 0x50 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "birds" ), 0x51 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "birdsFlight" ), 0x52 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "cabins" ), 0x53 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "cakeSlice" ), 0x54 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "candyCorn" ), 0x55 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "celticKnotwork" ), 0x56 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "certificateBanner" ), 0x57 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "chainLink" ), 0x58 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "champagneBottle" ), 0x59 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "checkedBarBlack" ), 0x5A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "checkedBarColor" ), 0x5B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "checkered" ), 0x5C ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "christmasTree" ), 0x5D ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "circlesLines" ), 0x5E ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "circlesRectangles" ), 0x5F ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "classicalWave" ), 0x60 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "clocks" ), 0x61 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "compass" ), 0x62 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "confetti" ), 0x63 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "confettiGrays" ), 0x64 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "confettiOutline" ), 0x65 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "confettiStreamers" ), 0x66 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "confettiWhite" ), 0x67 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "cornerTriangles" ), 0x68 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "couponCutoutDashes" ), 0x69 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "couponCutoutDots" ), 0x6A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "crazyMaze" ), 0x6B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "creaturesButterfly" ), 0x6C ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "creaturesFish" ), 0x6D ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "creaturesInsects" ), 0x6E ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "creaturesLadyBug" ), 0x6F ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "crossStitch" ), 0x70 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "cup" ), 0x71 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "decoArch" ), 0x72 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "decoArchColor" ), 0x73 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "decoBlocks" ), 0x74 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "diamondsGray" ), 0x75 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "doubleD" ), 0x76 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "doubleDiamonds" ), 0x77 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "earth1" ), 0x78 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "earth2" ), 0x79 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "eclipsingSquares1" ), 0x7A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "eclipsingSquares2" ), 0x7B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "eggsBlack" ), 0x7C ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "fans" ), 0x7D ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "film" ), 0x7E ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "firecrackers" ), 0x7F ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersBlockPrint" ), 0x80 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersDaisies" ), 0x81 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersModern1" ), 0x82 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersModern2" ), 0x83 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersPansy" ), 0x84 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersRedRose" ), 0x85 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersRoses" ), 0x86 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersTeacup" ), 0x87 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "flowersTiny" ), 0x88 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "gems" ), 0x89 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "gingerbreadMan" ), 0x8A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "gradient" ), 0x8B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "handmade1" ), 0x8C ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "handmade2" ), 0x8D ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "heartBalloon" ), 0x8E ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "heartGray" ), 0x8F ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "hearts" ), 0x90 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "heebieJeebies" ), 0x91 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "holly" ), 0x92 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "houseFunky" ), 0x93 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "hypnotic" ), 0x94 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "iceCreamCones" ), 0x95 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "lightBulb" ), 0x96 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "lightning1" ), 0x97 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "lightning2" ), 0x98 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "mapPins" ), 0x99 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "mapleLeaf" ), 0x9A ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "mapleMuffins" ), 0x9B ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "marquee" ), 0x9C ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "marqueeToothed" ), 0x9D ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "moons" ), 0x9E ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "mosaic" ), 0x9F ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "musicNotes" ), 0xA0 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "northwest" ), 0xA1 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "ovals" ), 0xA2 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "packages" ), 0xA3 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "palmsBlack" ), 0xA4 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "palmsColor" ), 0xA5 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "paperClips" ), 0xA6 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "papyrus" ), 0xA7 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "partyFavor" ), 0xA8 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "partyGlass" ), 0xA9 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "pencils" ), 0xAA ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "people" ), 0xAB ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "peopleWaving" ), 0xAC ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "peopleHats" ), 0xAD ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "poinsettias" ), 0xAE ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "postageStamp" ), 0xAF ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "pumpkin1" ), 0xB0 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "pushPinNote2" ), 0xB1 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "pushPinNote1" ), 0xB2 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "pyramids" ), 0xB3 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "pyramidsAbove" ), 0xB4 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "quadrants" ), 0xB5 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "rings" ), 0xB6 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "safari" ), 0xB7 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "sawtooth" ), 0xB8 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "sawtoothGray" ), 0xB9 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "scaredCat" ), 0xBA ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "seattle" ), 0xBB ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "shadowedSquares" ), 0xBC ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "sharksTeeth" ), 0xBD ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "shorebirdTracks" ), 0xBE ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "skyrocket" ), 0xBF ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "snowflakeFancy" ), 0xC0 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "snowflakes" ), 0xC1 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "sombrero" ), 0xC2 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "southwest" ), 0xC3 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "stars" ), 0xC4 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "starsTop" ), 0xC5 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "stars3d" ), 0xC6 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "starsBlack" ), 0xC7 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "starsShadowed" ), 0xC8 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "sun" ), 0xC9 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "swirligig" ), 0xCA ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tornPaper" ), 0xCB ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tornPaperBlack" ), 0xCC ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "trees" ), 0xCD ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "triangleParty" ), 0xCE ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "triangles" ), 0xCF ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tribal1" ), 0xD0 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tribal2" ), 0xD1 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tribal3" ), 0xD2 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tribal4" ), 0xD3 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tribal5" ), 0xD4 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "tribal6" ), 0xD5 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "twistedLines1" ), 0xD6 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "twistedLines2" ), 0xD7 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "vine" ), 0xD8 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "waveline" ), 0xD9 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "weavingAngles" ), 0xDA ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "weavingBraid" ), 0xDB ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "weavingRibbon" ), 0xDC ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "weavingStrips" ), 0xDD ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "whiteFlowers" ), 0xDE ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "woodwork" ), 0xDF ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "xIllusions" ), 0xE0 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "zanyTriangles" ), 0xE1 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "zigZag" ), 0xE2 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "zigZagStitch" ), 0xE3 ) );
				m_oBrcTypeMap.insert( std::pair<std::string, BYTE>( std::string( "none" ), 0xFF ) );
			}

			return m_oBrcTypeMap;
		}

	private:

		inline int AppendCellBorder (int nBorder, const nullable<OOX::Logic::CTblBorders>& oTableBorders, const nullable<OOX::Logic::CTcBorders>& oBorders)
		{		
			/*if (m_nIndCellX==0 && m_nIndCellY == 5)
			{
				int c = 0;
			}

			if (ApplyBorderFromInlineStyle(nBorder, oBorders))						//	¤чейка имеет свои собственные настройки дл¤ границ (inline-стиль)
				return TRUE;

			if (AppleBorderFromIndeTableStyle (nBorder, oTableBorders))				//	таблица имеет свои собственные настройки дл¤ границ (inline-стиль)
				return TRUE;

			int bAppend	=	ApplyBorderFromStylePropery (nBorder);				//	если у ¤чейки есть настройки по умолчанию
			
			if (0 == m_bNoVBand)													//	контент (вертикальный набор)
			{
				if (m_nIndCellX > 0 || (0 == m_bHaveBeginCol))
				{
					int bValidInd	=	((m_nIndCellX - 1) / m_nBandCol) % 2 - 1;	//	смещаем, если доступен стиль у первого столбца
					if (0 == m_bHaveBeginCol)
						bValidInd	=	((m_nIndCellX - 1) / m_nBandCol) % 2;

					if (bValidInd)
					{
						if (m_oBordersBand1Vert.ValidBorder(nBorder) || m_oBordersBand1Horz.ValidBorder(INSIDEV_BORDER))
						{
							SetupBrc (m_oBordersBand1Vert, nBorder, 1);
							bAppend	=	TRUE;
						}
					}
					else
					{
						if (m_oBordersBand2Vert.ValidBorder(nBorder) || m_oBordersBand1Horz.ValidBorder(INSIDEV_BORDER))
						{
							SetupBrc (m_oBordersBand2Vert, nBorder, 1);
							bAppend	=	TRUE;
						}
					}
				}
			}

			// контент (горизонтальный набор)

			if (0 == m_bNoHBand)
			{
				if (m_nIndCellY > 0 || (0 == m_bHaveBeginRow))
				{
					int bValidInd	=	((m_nIndCellY - 1) / m_nRowBand) % 2 - 1;	//	смещаем, если доступен стиль у первой строка
					if (0 == m_bHaveBeginRow)
						bValidInd	=	((m_nIndCellY - 1) / m_nRowBand) % 2;

					if (bValidInd)
					{
						if (m_oBordersBand1Horz.ValidBorder(nBorder) || m_oBordersBand1Horz.ValidBorder(INSIDEH_BORDER))
						{
							SetupBrc (m_oBordersBand1Horz, nBorder, 0);
							bAppend	=	TRUE;
						}							
					}
					else
					{
						if (m_oBordersBand2Horz.ValidBorder(nBorder) || m_oBordersBand2Horz.ValidBorder(INSIDEH_BORDER))
						{
							SetupBrc (m_oBordersBand2Horz, nBorder, 0);
							bAppend	=	TRUE;
						}
					}
				}
			}

			// первый столбец

			if (m_bHaveBeginCol)
			{
				if (0 == m_nIndCellX)
				{
					if (m_oBordersFirstCol.ValidBorder(nBorder))
					{
						SetupBrc (m_oBordersFirstCol, nBorder, 1, FALSE);
						bAppend	=	TRUE;
					}			
				}
			}

			// последний столбец

			if (m_bHaveEndCol)
			{
				if (m_nIndCellX == m_nCellsX)
				{
					if (m_oBordersLastCol.ValidBorder(nBorder))
					{
						SetupBrc (m_oBordersLastCol, nBorder, 1, FALSE);
						bAppend	=	TRUE;
					}
				}
			}

			// перва¤ строка

			if (m_bHaveBeginRow)
			{
				if (0 == m_nIndCellY)
				{
					if (m_oBordersFirstRow.ValidBorder(nBorder))
					{
						SetupBrc (m_oBordersFirstRow, nBorder, 0, FALSE);
						bAppend	=	TRUE;
					}
				}	
			}

			// последн¤¤ строка

			if (m_bHaveEndRow)
			{
				if (m_nIndCellY == m_nCellsY)
				{
					if (m_oBordersLastRow.ValidBorder(nBorder))
					{
						SetupBrc (m_oBordersLastRow, nBorder, 0, FALSE);
						bAppend	=	TRUE;
					}
				}
			}

			AppendOpList (nBorder);*/

			return FALSE;
		}

		inline int ApplyBorderFromInlineStyle (int nBorder, const nullable<OOX::Logic::CTcBorders>& oBorders)
		{
			/*if (oBorders.is_init())							//	у ¤чейки свой стиль
			{
				OOX::Logic::Border oBorder;
				if (oBorders->GetBorder(nBorder, oBorder))
				{
					CompileSide (nBorder, oBorder);
					AppendOpList (nBorder);

					return TRUE;
				}				
			}*/

			return FALSE;
		}

		inline int ApplyBorderFromStylePropery (int nBorder)
		{
			int bAppend = FALSE;

			/*if (m_bStyleBorders)
			{
				// внешние границы

				if ((nBorder == TOP_BORDER) && (0 == m_nIndCellY))
				{
					OOX::Logic::Border oBorder;
					if (m_oStyleBorders.GetBorder (TOP_BORDER,oBorder))
					{
						CompileSide (TOP_BORDER, oBorder);
						bAppend	=	TRUE;
					}	
				}

				// внешние границы

				if ((nBorder == BOTTOM_BORDER) && (m_nIndCellY == m_nCellsY))
				{
					OOX::Logic::Border oBorder;
					if (m_oStyleBorders.GetBorder (BOTTOM_BORDER,oBorder))
					{
						CompileSide (BOTTOM_BORDER, oBorder);
						bAppend	=	TRUE;
					}					
				}

				// внешние границы

				if ((nBorder == LEFT_BORDER) && (0 == m_nIndCellX))
				{
					OOX::Logic::Border oBorder;
					if (m_oStyleBorders.GetBorder (LEFT_BORDER,oBorder))
					{
						CompileSide (LEFT_BORDER, oBorder);
						bAppend	=	TRUE;
					}					
				}

				// внешние границы

				if ((nBorder == RIGHT_BORDER) && (m_nIndCellX == m_nCellsX))
				{
					OOX::Logic::Border oBorder;
					if (m_oStyleBorders.GetBorder (RIGHT_BORDER,oBorder))
					{
						CompileSide (RIGHT_BORDER, oBorder);
						bAppend	=	TRUE;
					}					
				}

				// внутренние горизонтальные границы 

				if (((nBorder == TOP_BORDER) && (0 < m_nIndCellY)) || ((nBorder == BOTTOM_BORDER) && (m_nIndCellY != m_nCellsY)))
				{
					OOX::Logic::Border oBorder;
					if (m_oStyleBorders.GetBorder (INSIDEH_BORDER,oBorder))
					{
						CompileSide (nBorder, oBorder);
						bAppend	=	TRUE;
					}					
				}

				// внутренние вертикальные границы 

				if (((nBorder == LEFT_BORDER) && (0 < m_nIndCellX)) || ((nBorder == RIGHT_BORDER) && (m_nIndCellX != m_nCellsX)))
				{
					OOX::Logic::Border oBorder;
					if (m_oStyleBorders.GetBorder (INSIDEV_BORDER,oBorder))
					{
						CompileSide (nBorder, oBorder);
						bAppend	=	TRUE;
					}					
				}
			}*/

			return bAppend;
		}

		inline int AppleBorderFromIndeTableStyle (int nBorder, const nullable<OOX::Logic::CTblBorders>& oTableBorders)
		{
			/*if (oTableBorders.is_init())
			{
				OOX::Logic::Border oBorder;
				if (oTableBorders->GetBorder(nBorder, oBorder))
				{
					CompileSide (nBorder, oBorder);
					AppendOpList (nBorder);

					return TRUE;
				}				
			}*/

			return FALSE;
		}

		inline int IsInsideBorder (int nBorder, int bEven = FALSE)
		{
			if (TOP_BORDER == nBorder)
			{
				if (1 == m_nRowBand)	// inside объектов нету
					return FALSE;

				int bIsOdd			=	(m_nIndCellY / m_nRowBand) % 2;
				if (m_bHaveBeginRow)
					bIsOdd			=	((m_nIndCellY-1) / m_nRowBand) % 2;

				if (bIsOdd)
				{
					int nModulo		=	m_nIndCellY % m_nRowBand;
					if (m_bHaveBeginRow)
						nModulo		=	(m_nIndCellY-1) % m_nRowBand;

					if (0 != nModulo)	//	верх в наборе
						return TRUE;
				}					
				else
				{
					int nModulo		=	m_nIndCellY % m_nRowBand;
					if (m_bHaveBeginRow)
						nModulo		=	(m_nIndCellY-1) % m_nRowBand;

					if (0 != nModulo)	//	верх в наборе
						return TRUE;
				}

				return FALSE;
			}

			if (BOTTOM_BORDER == nBorder)
			{
				if (1 == m_nRowBand)	// inside объектов нету
					return FALSE;

				int bIsOdd			=	(m_nIndCellY / m_nRowBand) % 2;
				if (m_bHaveBeginRow)
					bIsOdd			=	((m_nIndCellY-1) / m_nRowBand) % 2;

				if (bIsOdd)
				{
					int nModulo		=	m_nIndCellY % m_nRowBand;
					if (m_bHaveBeginRow)
						nModulo		=	(m_nIndCellY-1) % m_nRowBand;

					//if (2 == m_nIndCellX)
					//	ATLTRACE (L"(%d,%d) : %d, Even : %d\n", m_nIndCellX, m_nIndCellY, nModulo, bIsEven);

					if (nModulo < m_nRowBand)	//	низ в наборе
						return TRUE;
				}					
				else
				{
					int nModulo		=	m_nIndCellY % m_nRowBand;
					if (m_bHaveBeginRow)
						nModulo		=	(m_nIndCellY-1) % m_nRowBand;

					//if (2 == m_nIndCellX)
					//	ATLTRACE (L"(%d,%d) : %d, Even : %d\n", m_nIndCellX, m_nIndCellY, nModulo, bIsEven);

					if (nModulo < m_nRowBand)	//	низ в наборе
						return TRUE;
				}

				return FALSE;
			}

			if (LEFT_BORDER == nBorder)
			{
				if (1 == m_nBandCol)
					return FALSE;

				int nModulo		=	m_nIndCellX % m_nBandCol;
				if (m_bHaveBeginCol)
					nModulo		=	(m_nIndCellX - 1) % m_nBandCol;

				if (0 != nModulo)	
					return TRUE;

				return FALSE;
			}

			if (RIGHT_BORDER == nBorder)
			{
				if (1 == m_nBandCol)
					return FALSE;

				int nModulo		=	m_nIndCellY % m_nBandCol;
				if (m_bHaveBeginRow)
					nModulo		=	(m_nIndCellY - 1) % m_nBandCol;

				if (nModulo < m_nRowBand)
					return TRUE;

				return FALSE;
			}

			return FALSE;
		}

		//
		/*inline Docx2Doc::Brc80MayBeNil CreateNilBorder (const OOX::Logic::Border& oBorder)
		{
			return Docx2Doc::Brc80MayBeNil(oBorder.Bdr->Sz.get_value_or_default(),
				m_oBrcTypeMap[oBorder.Bdr->Value], ColorToIco (oBorder.Bdr->Color.get_value_or_default()), oBorder.Bdr->Space.get_value_or_default(), false, false);
		}*/

		/*inline Docx2Doc::Brc CreateBorder (const OOX::Logic::Border& oBorder)
		{
			std::string strColor	=	oBorder.Bdr->Color.get_value_or_default().ToString();
			if (std::string("auto") == strColor)
				strColor			=	std::string ("000000");

			return Docx2Doc::Brc(Docx2Doc::COLORREF(HexString2Int(strColor)),
				oBorder.Bdr->Sz.get_value_or_default(), m_oBrcTypeMap[oBorder.Bdr->Value], oBorder.Bdr->Space.get_value_or_default(), false, false);
		}*/

		/*inline void CompileSide (int nSide, const OOX::Logic::Border& oBorder)
		{
			if (TOP_BORDER == nSide)
			{
				m_oBrc80Top				=	CreateNilBorder (oBorder);
				m_oBrcTop				=	CreateBorder (oBorder);
				m_oBrc80MayBeNilTop		=	m_oBrc80Top;

				return;
			}

			if (BOTTOM_BORDER == nSide)
			{
				m_oBrc80Bottom			=	CreateNilBorder (oBorder);
				m_oBrcBottom			=	CreateBorder (oBorder);
				m_oBrc80MayBeNilBottom	=	m_oBrc80Top;

				return;
			}

			if (LEFT_BORDER == nSide)
			{
				m_oBrc80Left			=	CreateNilBorder (oBorder);
				m_oBrcLeft				=	CreateBorder (oBorder);
				m_oBrc80MayBeNilLeft	=	m_oBrc80Left;

				return;
			}

			if (RIGHT_BORDER == nSide)
			{
				m_oBrc80Right			=	CreateNilBorder (oBorder);
				m_oBrcRight				=	CreateBorder (oBorder);
				m_oBrc80MayBeNilRight	=	m_oBrc80Right;
			}
		}*/

		inline void SetNilBrc (int nBorder)
		{
			if (TOP_BORDER == nBorder)
			{
				m_oBrc80MayBeNilTop			=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrc80Top					=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrcTop					=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xFF000000), 0, 0, 0, false, false);
			}

			if (BOTTOM_BORDER == nBorder)
			{
				m_oBrc80MayBeNilBottom		=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrc80Bottom				=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrcBottom				=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xFF000000), 0, 0, 0, false, false);
			}

			if (LEFT_BORDER == nBorder)
			{
				m_oBrc80MayBeNilLeft		=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrc80Left				=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrcLeft					=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xFF000000), 0, 0, 0, false, false);
			}

			if (RIGHT_BORDER == nBorder)
			{
				m_oBrc80MayBeNilRight		=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrc80Right				=	Docx2Doc::Brc80MayBeNil(0xFFFFFFFF);
				m_oBrcRight					=	Docx2Doc::Brc(Docx2Doc::COLORREF(0xFF000000), 0, 0, 0, false, false);
			}
		}

		/*inline void SetupBrc (const OOX::Logic::CTcBorders& oBorder, int nBorder, int bBand, int bInside = TRUE)
		{
			if (TOP_BORDER == nBorder)
			{
				int bValidInside = TRUE;

				OOX::Logic::Border oInsideH;
				if ((TRUE == bInside) && (m_nIndCellY > 0) && (oBorder.GetBorder(INSIDEH_BORDER, oInsideH)))
				{
					if (std::string("nil") == oInsideH.Bdr->Value)		//	запрет внутри таблицы на рисование границ
					{
						if (IsInsideBorder(nBorder))
							SetNilBrc (nBorder);
					}
					else
					{
						CompileSide (nBorder, oInsideH);
					}
				}
				else
				{
					if (oBorder.top.is_init())
					{
						if (std::string("nil") != oBorder.top->Bdr->Value && ((m_nIndCellY == 0) || (0==bBand)))
						{
							CompileSide (nBorder, oBorder.top);
						}
						else
						{
							SetNilBrc (TOP_BORDER);
						}
					}
					else
					{
						// SetNilBrc (TOP_BORDER);
					}
				}
			}

			if (BOTTOM_BORDER == nBorder)
			{
				if (m_nIndCellX == 1 && m_nIndCellY == 1)
				{
					int ccc = 0;
				}

				int bValidInside = TRUE;

				OOX::Logic::Border oInsideH;
				if ((TRUE == bInside) && (m_nIndCellY != m_nCellsY) && (oBorder.GetBorder(INSIDEH_BORDER, oInsideH)))
				{
					if (std::string("nil") == oInsideH.Bdr->Value)		//	запрет внутри таблицы на рисование границ
					{
						if (IsInsideBorder(nBorder))
							SetNilBrc (nBorder);
					}
					else
					{
						CompileSide (nBorder, oInsideH);
					}
				}
				else
				{
					if (oBorder.bottom.is_init())
					{
						if (std::string("nil") != oBorder.bottom->Bdr->Value && ((m_nIndCellY == m_nCellsY) || (0==bBand)))
						{
							CompileSide (nBorder, oBorder.bottom);
						}
						else
						{
							SetNilBrc (BOTTOM_BORDER);
						}
					}
					else
					{
						// SetNilBrc (BOTTOM_BORDER);
					}
				}
			}

			if (LEFT_BORDER == nBorder)
			{
				OOX::Logic::Border oInsideV;
				if ((TRUE == bInside) && (m_nIndCellX > 0) && oBorder.GetBorder(INSIDEV_BORDER, oInsideV))	// более приоритетен над стил¤м которые задают границу
				{
					if (std::string("nil") == oInsideV.Bdr->Value)		//	запрет внутри таблицы на рисование границ
					{
						if (IsInsideBorder(nBorder))
							SetNilBrc (nBorder);
					}
					else
					{
						CompileSide (nBorder, oInsideV);
					}
				}
				else
				{
					if (oBorder.left.is_init())
					{
						if (std::string("nil") != oBorder.left->Bdr->Value && ((m_nIndCellX == 0) || (1==bBand)))
						{
							CompileSide (nBorder, oBorder.left);
						}
						else
						{
							SetNilBrc (LEFT_BORDER);
						}
					}
					else
					{
						// SetNilBrc (LEFT_BORDER);
					}
				}
			}

			if (RIGHT_BORDER == nBorder)
			{
				OOX::Logic::Border oInsideV;
				if ((TRUE == bInside) && (m_nIndCellX != m_nCellsX) && oBorder.GetBorder(INSIDEV_BORDER, oInsideV))
				{
					if (std::string("nil") == oInsideV.Bdr->Value)		//	запрет внутри таблицы на рисование границ
					{
						if (IsInsideBorder(nBorder))
							SetNilBrc (nBorder);
					}
					else
					{
						CompileSide (nBorder, oInsideV);
					}
				}
				else
				{
					if (oBorder.right.is_init())
					{
						if ((std::string("nil") != oBorder.right->Bdr->Value) && ((m_nIndCellX == m_nCellsX) || (1==bBand)))
						{
							CompileSide (nBorder, oBorder.right);
						}
						else
						{
							SetNilBrc (RIGHT_BORDER);
						}
					}
					else
					{
						// SetNilBrc (RIGHT_BORDER);
					}
				}
			}
		}*/

		inline void AppendOpList (int nBorder)
		{
			if (TOP_BORDER == nBorder)
			{
				Docx2Doc::TableBrc80Operand brc80Operand(Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyTopBorder, m_oBrc80Top);
				m_oBrc80s.push_back(brc80Operand);

				Docx2Doc::TableBrcOperand brcOperand(Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyTopBorder, m_oBrcTop);
				m_oBrcs.push_back(brcOperand);
			}

			if (BOTTOM_BORDER == nBorder)
			{
				Docx2Doc::TableBrc80Operand brc80Operand( Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyBottomBorder, m_oBrc80Bottom);
				m_oBrc80s.push_back(brc80Operand);

				Docx2Doc::TableBrcOperand brcOperand( Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyBottomBorder, m_oBrcBottom);
				m_oBrcs.push_back(brcOperand);
			}

			if (LEFT_BORDER == nBorder)
			{
				Docx2Doc::TableBrc80Operand brc80Operand( Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyLogicalLeftBorder, m_oBrc80Left);
				m_oBrc80s.push_back(brc80Operand);

				Docx2Doc::TableBrcOperand brcOperand( Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyLogicalLeftBorder, m_oBrcLeft);
				m_oBrcs.push_back(brcOperand);
			}

			if (RIGHT_BORDER == nBorder)
			{
				Docx2Doc::TableBrc80Operand brc80Operand(Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyLogicalRightBorder, m_oBrc80Right);
				m_oBrc80s.push_back(brc80Operand);

				Docx2Doc::TableBrcOperand brcOperand(Docx2Doc::ItcFirstLim(m_nIndCellX, (m_nIndCellX + 1)), Docx2Doc::Constants::bordersToApplyLogicalRightBorder, m_oBrcRight);
				m_oBrcs.push_back(brcOperand);
			}
		}

		/*inline unsigned char ColorToIco	(const OOX::Logic::Color& oColor)
		{
			OOX::Logic::ColorsTable colorsTable;

			std::string colorName = colorsTable.fromColor(oColor);

			if (0 == m_oColorsMap.size())
			{
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "auto", 0x00 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "black", 0x01 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "blue", 0x02 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "cyan", 0x03 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "green", 0x04 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "magenta", 0x05 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "red", 0x06 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "yellow", 0x07 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "white", 0x08 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "darkBlue", 0x09 ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "darkCyan", 0x0A ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "darkGreen", 0x0B ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "darkMagenta", 0x0C ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "darkRed", 0x0D ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "darkYellow", 0x0E ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "darkGray", 0x0F ) );
				m_oColorsMap.insert( std::pair<std::string, BYTE>( "lightGray", 0x10 ) );
			}

			return m_oColorsMap[colorName];
		}*/


	private:

		static std::map<std::string, BYTE>			m_oBrcTypeMap;
		static std::map<std::string, BYTE>			m_oColorsMap;

		OOX::CStyle									m_oStyle;

		int											m_bHaveBeginRow;
		int											m_bHaveBeginCol;
		int											m_bHaveEndRow;
		int											m_bHaveEndCol;

		int											m_bNoHBand;
		int											m_bNoVBand;

		int											m_nIndCellX;
		int											m_nIndCellY;

		int											m_nCellsX;
		int											m_nCellsY;

		int											m_nRowBand;
		int											m_nBandCol;

		std::vector<Docx2Doc::TableBrcOperand>		m_oBrcs;
		std::vector<Docx2Doc::TableBrc80Operand>	m_oBrc80s;

		Docx2Doc::Brc								m_oBrcTop;
		Docx2Doc::Brc80MayBeNil						m_oBrc80Top;
		Docx2Doc::Brc								m_oBrcBottom;
		Docx2Doc::Brc80MayBeNil						m_oBrc80Bottom;
		Docx2Doc::Brc								m_oBrcLeft;
		Docx2Doc::Brc80MayBeNil						m_oBrc80Left;
		Docx2Doc::Brc								m_oBrcRight;
		Docx2Doc::Brc80MayBeNil						m_oBrc80Right;

		Docx2Doc::Brc80MayBeNil						m_oBrc80MayBeNilTop;
		Docx2Doc::Brc80MayBeNil						m_oBrc80MayBeNilBottom;
		Docx2Doc::Brc80MayBeNil						m_oBrc80MayBeNilLeft;
		Docx2Doc::Brc80MayBeNil						m_oBrc80MayBeNilRight;

		int										m_bStyleBorders;
		OOX::Logic::CTblBorders					m_oStyleBorders;

		int										m_bExistStyleFirstRow;
		int										m_bStyleFirstRow;
		OOX::Logic::CTcBorders					m_oBordersFirstRow;

		int										m_bExistStyleLastRow;
		int										m_bStyleLastRow;
		OOX::Logic::CTcBorders					m_oBordersLastRow;

		int										m_bExistStyleBand1Horz;
		int										m_bStyleBand1Horz;
		OOX::Logic::CTcBorders					m_oBordersBand1Horz;

		int										m_bExistStyleBand1Vert;
		int										m_bStyleBand1Vert;
		OOX::Logic::CTcBorders					m_oBordersBand1Vert;

		int										m_bExistStyleBand2Horz;
		int										m_bStyleBand2Horz;
		OOX::Logic::CTcBorders					m_oBordersBand2Horz;

		int										m_bExistStyleBand2Vert;
		int										m_bStyleBand2Vert;
		OOX::Logic::CTcBorders					m_oBordersBand2Vert;

		int										m_bExistStyleFirstCol;
		int										m_bStyleFirstCol;
		OOX::Logic::CTcBorders					m_oBordersFirstCol;

		int										m_bExistStyleLastCol;
		int										m_bStyleLastCol;
		OOX::Logic::CTcBorders					m_oBordersLastCol;
	};

	class CTblFill
	{
	public:
		CTblFill (const OOX::Logic::CTbl& oXmlTable, OOX::CStyle oStyle) : m_oStyle (oStyle)
		{
			/*m_bHaveBeginRow		=	oXmlTable.tblPr->firstRow;
			m_bHaveEndRow		=	oXmlTable.tblPr->lastRow;
			m_bHaveBeginCol		=	oXmlTable.tblPr->firstColumn;
			m_bHaveEndCol		=	oXmlTable.tblPr->lastColumn;

			m_bNoHBand			=	oXmlTable.tblPr->noHBand;
			m_bNoVBand			=	oXmlTable.tblPr->noVBand;

			if (m_bHaveBeginRow)
			{
				if (false == m_oStyle.tableStyles->exist(std::string("firstRow")))
					m_bHaveBeginRow		=	0;
			}

			if (m_bHaveEndRow)
			{
				if (false == m_oStyle.tableStyles->exist(std::string("lastRow")))
					m_bHaveEndRow		=	0;
			}

			if (m_bHaveBeginCol)
			{
				if (false == m_oStyle.tableStyles->exist(std::string("firstCol")))
					m_bHaveBeginCol		=	0;
			}

			if (m_bHaveEndCol)
			{
				if (false == m_oStyle.tableStyles->exist(std::string("lastCol")))
					m_bHaveEndCol		=	0;
			}*/

			// TODO : кэширование стилей
		}

		int AddCell (int nX, int nY, int nCX, int nCY, const nullable<ComplexTypes::Word::CShading>& oShading)
		{	
			/*

			ѕриоритет заливки ¤чейки. 

			-	ѕараметры у самой ¤чейки.
			-	ƒополнительные стили у стил¤ таблицы по строкам и столбцам (стиль у строки, затрет стиль столбца).
			-	Ќастройки по умолчанию у стил¤ к таблице.

			*/

			/*Docx2Doc::Shd	oShd;

			int nRowBand	=	1;
			if(m_oStyle.tblPr.is_init())
				nRowBand	=	__max(m_oStyle.tblPr->tblStyleRowBandSize,1);

			int nBandCol	=	1;
			if(m_oStyle.tblPr.is_init())
				nBandCol	=	__max(m_oStyle.tblPr->tblStyleColBandSize,1);

			int bAppend	=	FALSE;

			if (oShading.is_init())
			{
				oShd		=	GetBackGroundShading (oShading);
				bAppend		=	TRUE;
			}
			else
			{
				if (m_oStyle.tcPr.is_init())	//	если у ¤чейки есть настройки по умолчанию
				{				
					if (m_oStyle.tcPr->Shading.is_init())
						oShd	=	GetBackGroundShading (m_oStyle.tcPr->Shading);

					bAppend		=	TRUE;
				}

				// контент (вертикальный набор)

				if (0 == m_bNoVBand)
				{
					if (nX > 0 || (0 == m_bHaveBeginCol))
					{
						int bEven	=	(nX / nBandCol) % 2;
						if (m_bHaveBeginRow)
							bEven	=	((nX-1) / nBandCol) % 2;	//	смещаем, если доступен столбец заголовка

						if (0==bEven)
						{
							if (UpdateShading(std::string("band1Vert"), oShd))
								bAppend	=	TRUE;
						}
						else
						{
							if (UpdateShading(std::string("band2Vert"), oShd))
								bAppend	=	TRUE;
						}
					}
				}

				// контент (горизонтальный набор)

				if (0 == m_bNoHBand)
				{
					if (nY > 0 || (0 == m_bHaveBeginRow))
					{
						int bEven	=	(nY / nRowBand) % 2;
						if (m_bHaveBeginRow)
							bEven	=	((nY-1) / nRowBand) % 2;	//	смещаем, если доступна строка заголовка

						if (0==bEven)
						{
							if (UpdateShading(std::string("band1Horz"), oShd))
								bAppend	=	TRUE;
						}
						else
						{
							if (UpdateShading(std::string("band2Horz"), oShd))
								bAppend	=	TRUE;
						}
					}
				}

				// первый столбец

				if (m_bHaveBeginCol)
				{
					if (0 == nX)
					{
						if (UpdateShading(std::string("firstCol"), oShd))
							bAppend	=	TRUE;
					}
				}

				// последний столбец

				if (m_bHaveEndCol)
				{
					if (nX == nCX)
					{
						if (UpdateShading(std::string("lastCol"), oShd))
							bAppend	=	TRUE;
					}
				}

				// перва¤ строка

				if (m_bHaveBeginRow)
				{
					if (0 == nY)
					{
						if (UpdateShading(std::string("firstRow"), oShd))
							bAppend	=	TRUE;
					}	
				}

				// последн¤¤ строка

				if (m_bHaveEndRow)
				{
					if (nY == nCY)
					{
						if (UpdateShading(std::string("lastRow"), oShd))
							bAppend	=	TRUE;
					}
				}

				// дополнительно можем форматировать угловые элементы

				if (UpdateOneCellFormat(nX, nY, nCX, nCY, oShd))					
					bAppend	=	TRUE;					
			}

			if (bAppend)
			{
				if (nX < 22)
					m_arShd22.push_back(oShd);
				else if (nX < 44)
					m_arShd44.push_back(oShd);
				else if (nX < 63)
					m_arShd63.push_back(oShd);   
			}
			else
			{
				if (nX < 22)
					m_arShd22.push_back(Docx2Doc::Shd());
				else if (nX < 44)
					m_arShd44.push_back(Docx2Doc::Shd());
				else if (nX < 63)
					m_arShd63.push_back(Docx2Doc::Shd());
			}*/

			return TRUE;
		}

		inline int UpdateShading (const std::string& strStyle, Docx2Doc::Shd& oShd)
		{
			/*if (m_oStyle.tableStyles->exist(strStyle))
			{
				const OOX::Logic::CTableStyleProperties& oInternal = m_oStyle.tableStyles->operator [](strStyle);
				if (oInternal.tcPr.is_init() && oInternal.tcPr->Shading.is_init())
				{
					oShd = GetBackGroundShading (oInternal.tcPr->Shading);

					return TRUE;
				}
			}*/

			return FALSE;
		}


		//
		inline const ShdList& GetShd22 () 
		{
			return m_arShd22;
		}

		inline const ShdList& GetShd44 ()
		{
			return m_arShd44;
		}

		inline const ShdList& GetShd63 ()
		{
			return m_arShd63;
		}

	private:
		inline int UpdateOneCellFormat (int nX, int nY, int nCX, int nCY, Docx2Doc::Shd& oShd)
		{
			if ((0 == nX) && (0 == nY))
			{
				if (UpdateShading(std::string("nwCell"), oShd))
					return TRUE;
			}
		
			if ((nCX == nX) && (0 == nY))
			{
				if (UpdateShading(std::string("neCell"), oShd))
					return TRUE;
			}
		
			if ((0 == nX) && (nCY == nY))
			{
				if (UpdateShading(std::string("swCell"), oShd))
					return TRUE;
			}
		
			if ((nCX == nX) && (nCY == nY))
			{
				if (UpdateShading(std::string("seCell"), oShd))
					return TRUE;
			}

			return FALSE;
		}

	private:
		OOX::CStyle	m_oStyle;

		int	m_bHaveBeginRow;
		int	m_bHaveBeginCol;
		int	m_bHaveEndRow;
		int	m_bHaveEndCol;

		int	m_bNoHBand;
		int	m_bNoVBand;

		int		m_nIndCellX;
		int		m_nIndCellY;

		int		m_nCellsX;
		int		m_nCellsY;

		ShdList	m_arShd22;
		ShdList m_arShd44;
		ShdList m_arShd63;
	};
}
