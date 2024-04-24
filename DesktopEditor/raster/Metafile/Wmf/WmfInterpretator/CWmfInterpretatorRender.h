/*
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

#ifndef CWMFINTERPRETATORRENDER_H
#define CWMFINTERPRETATORRENDER_H

#include "CWmfInterpretatorBase.h"
#include "../../Common/MetaFileRenderer.h"

namespace MetaFile
{
	class CWmfInterpretatorRender : public CWmfInterpretatorBase
	{
	public:
		CWmfInterpretatorRender(IOutputDevice* pIOutputDevice);

		InterpretatorType   GetType() const override;

		void Begin() override;
		void End() override;

		void DrawBitmap(double dX, double dY, double dW, double dH, BYTE* pBuffer, unsigned int unWidth, unsigned int unHeight) override;

		void DrawString(std::wstring& wsText, unsigned int unCharsCount, double dX, double dY, double* pDx,
						int iGraphicsMode = 1, double dXScale = 1, double dYScale = 1) override;

		void DrawDriverString(const std::wstring& wsString, const std::vector<TPointD>& arPoints) override;

		void StartPath() override;
		void MoveTo(double dX, double dY) override;
		void LineTo(double dX, double dY) override;
		void CurveTo(double dX1, double dY1, double dX2, double dY2, double dXe, double dYe) override;
		void ArcTo(double dLeft, double dTop, double dRight, double dBottom, double dStartAngle, double dSweepAngle) override;
		void ClosePath() override;
		void DrawPath(int nType = 0) override;
		void EndPath() override;

		void ResetClip() override;
		void IntersectClip(const TRectD& oClip) override;
		void ExcludeClip(const TRectD& oClip, const TRectD& oBB) override;
		void PathClip(const CPath& oPath, int nClipMode, TXForm* pTransform = NULL) override;
		void StartClipPath(unsigned int unMode, int nFillMode = -1) override;
		void EndClipPath(unsigned int unMode) override;

		void UpdateDC() override;
		void SetTransform(double& dM11, double& dM12, double& dM21, double& dM22, double& dX, double& dY) override;
		void GetTransform(double* pdM11, double* pdM12, double* pdM21, double* pdM22, double* pdX, double* pdY) override;

		CMetaFileRenderer* GetRenderer() const;

	private:
		CMetaFileRenderer *m_pMetaFileRenderer;
	public:
		//Следующие методы ничего не делают
		void HANDLE_META_HEADER(const TWmfPlaceable&, const TWmfHeader&) override {};
		//-----------------------------------------------------------
		// 2.3.1 Bitmap records
		//-----------------------------------------------------------
		void HANDLE_META_BITBLT(const TWmfBitBlt& oWmfBitBlt, CDataStream& oDataStream) override {};
		void HANDLE_META_DIBBITBLT(const TWmfBitBlt& oWmfBitBlt, CDataStream& oDataStream) override {};
		void HANDLE_META_DIBSTRETCHBLT(const TWmfStretchBlt& oWmfStretchBlt, CDataStream& oDataStream) override {};
		void HANDLE_META_SETDIBTODEV(const TWmfSetDibToDev& oWmfSetDibToDev, CDataStream& oDataStream) override {};
		void HANDLE_META_STRETCHBLT(const TWmfStretchBlt& oWmfStretchBlt, CDataStream& oDataStream) override {};
		void HANDLE_META_STRETCHDIB(const TWmfStretchDib& oWmfStretchDib, CDataStream& oDataStream) override {};
		//-----------------------------------------------------------
		// 2.3.2 Control records
		//-----------------------------------------------------------
		void HANDLE_META_EOF() override {};
		//-----------------------------------------------------------
		// 2.3.3 Drawing records
		//-----------------------------------------------------------
		void HANDLE_META_ARC(short shYEndArc, short shXEndArc, short shYStartArc, short shXStartArc, short shBottom, short shRight, short shTop, short shLeft) override {};
		void HANDLE_META_CHORD(short shYEndArc, short shXEndArc, short shYStartArc, short shXStartArc, short shBottom, short shRight, short shTop, short shLeft) override {};
		void HANDLE_META_ELLIPSE(short shBottom, short shRight, short shTop, short shLeft) override {};
		void HANDLE_META_EXTTEXTOUT(short shY, short shX, short shStringLength, unsigned short ushFwOptions, const TRectL& oRectangle, unsigned char* pString, short* pDx) override {};
		void HANDLE_META_FILLREGION(unsigned short ushRegionIndex, unsigned short ushBrushIndex) override {};
		void HANDLE_META_FRAMEREGION(unsigned short ushRegionIndex, unsigned short ushBrushIndex, short shHeight, short shWidth) override {};
		void HANDLE_META_INVERTREGION(unsigned short ushRegionIndex) override {};
		void HANDLE_META_LINETO(short shY, short shX) override {};
		void HANDLE_META_PAINTREGION(unsigned short ushRegionIndex) override {};
		void HANDLE_META_PATBLT(unsigned int unRasterOperation, short shH, short shW, short shY, short shX) override {};
		void HANDLE_META_PIE(short shXRadial1, short shYRadial1, short shXRadial2, short shYRadial2, short shB, short shR, short shT, short shL) override {};
		void HANDLE_META_POLYLINE(const std::vector<TPointS>& arPoints) override {};
		void HANDLE_META_POLYGON(const std::vector<TPointS>& arPoints) override {};
		void HANDLE_META_POLYPOLYGON(const std::vector<std::vector<TPointS>>& arPolygons) override {};
		void HANDLE_META_RECTANGLE(short shB, short shR, short shT, short shL) override {};
		void HANDLE_META_ROUNDRECT(short shH, short shW, short shB, short shR, short shT, short shL) override {};
		void HANDLE_META_SETPIXEL(const TRGBA &oColor, short shY, short shX) override {};
		void HANDLE_META_TEXTOUT(short shStringLength, unsigned char* pString, short shY, short shX) override {};
		//-----------------------------------------------------------
		// 2.3.4 Object records
		//-----------------------------------------------------------
		void HANDLE_META_CREATEBRUSHINDIRECT(const TWmfLogBrush& oBrush) override {};
		void HANDLE_META_CREATEFONTINDIRECT(const CWmfFont& oFont) override {};
		void HANDLE_META_CREATEPALETTE(const CWmfPalette& oPalette) override {};
		void HANDLE_META_CREATEPATTERNBRUSH(const CWmfBrush& oBrush, CDataStream& oDataStream) override {};
		void HANDLE_META_CREATEPENINDIRECT(const CWmfPen& oPen) override {};
		void HANDLE_META_CREATEREGION(const CWmfRegion& oRegion) override {};
		void HANDLE_META_DELETEOBJECT(unsigned short ushIndex) override {};
		void HANDLE_META_DIBCREATEPATTERNBRUSH(unsigned short ushStyle, unsigned short ushColorUsage, const CWmfBrush& oBrush, CDataStream& oDataStream) override {};
		void HANDLE_META_SELECTCLIPREGION(unsigned short ushIndex) override {};
		void HANDLE_META_SELECTOBJECT(unsigned short ushIndex) override {};
		void HANDLE_META_SELECTPALETTE(unsigned short ushIndex) override {};
		//-----------------------------------------------------------
		// 2.3.5 State records
		//-----------------------------------------------------------
		void HANDLE_META_EXCLUDECLIPRECT(short shLeft, short shTop, short shRight, short shBottom) override;
		void HANDLE_META_INTERSECTCLIPRECT(short shLeft, short shTop, short shRight, short shBottom) override;
		void HANDLE_META_MOVETO(short shX, short shY) override {};
		void HANDLE_META_OFFSETCLIPRGN(short shOffsetX, short shOffsetY) override;
		void HANDLE_META_OFFSETVIEWPORTORG(short shXOffset, short shYOffset) override {};
		void HANDLE_META_OFFSETWINDOWORG(short shXOffset, short shYOffset) override {};
		void HANDLE_META_RESTOREDC() override;
		void HANDLE_META_SAVEDC() override {};
		void HANDLE_META_SCALEVIEWPORTEXT(short yDenom, short yNum, short xDenom, short xNum) override {};
		void HANDLE_META_SCALEWINDOWEXT(short yDenom, short yNum, short xDenom, short xNum) override {};
		void HANDLE_META_SETBKCOLOR(const TRGBA& oColor) override {};
		void HANDLE_META_SETBKMODE(unsigned short ushMode) override {};
		void HANDLE_META_SETLAYOUT(unsigned short ushLayout) override {};
		void HANDLE_META_SETMAPMODE(unsigned short ushMapMode) override {};
		void HANDLE_META_SETPOLYFILLMODE(unsigned short ushMode) override {};
		void HANDLE_META_SETROP2(unsigned short ushMode) override {};
		void HANDLE_META_SETSTRETCHBLTMODE(unsigned short ushMode) override {};
		void HANDLE_META_SETTEXTALIGN(unsigned short ushTextAlign) override {};
		void HANDLE_META_SETTEXTCHAREXTRA(unsigned short ushCharSpacing) override {};
		void HANDLE_META_SETTEXTCOLOR(const TRGBA& oColor) override {};
		void HANDLE_META_SETTEXTJUSTIFICATION(unsigned short ushBreakCount, unsigned short ushBreakExtra) override {};
		void HANDLE_META_SETVIEWPORTEXT(short shX, short shY) override {};
		void HANDLE_META_SETVIEWPORTORG(short shX, short shY) override {};
		void HANDLE_META_SETWINDOWEXT(short shX, short shY) override {};
		void HANDLE_META_SETWINDOWORG(short shX, short shY) override {};
		//-----------------------------------------------------------
		// 2.3.6 State records
		//-----------------------------------------------------------
		void HANDLE_META_ESCAPE(unsigned short ushEscapeFunction, unsigned short ushByteCount) override {};
		//-----------------------------------------------------------
		// Неизвестные записи
		//-----------------------------------------------------------
		void HANDLE_META_UNKNOWN(CDataStream& oDataStream) override {};
	};
}

#endif // CWMFINTERPRETATORRENDER_H
