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

#include "CUse.h"
#include "../CSvgFile.h"

namespace SVG
{
	CUse::CUse(XmlUtils::CXmlNode &oNode, CRenderedObject *pParent)
		: CRenderedObject(oNode, pParent)
	{
		m_wsHref = oNode.GetAttribute(L"href", oNode.GetAttribute(L"xlink:href"));

		m_oX     .SetValue(oNode.GetAttribute(L"x"));
		m_oY     .SetValue(oNode.GetAttribute(L"y"));
		m_oWidth .SetValue(oNode.GetAttribute(L"width"));
		m_oHeight.SetValue(oNode.GetAttribute(L"height"));
	}

	CUse::~CUse()
	{}

	void CUse::SetData(const std::map<std::wstring, std::wstring> &mAttributes, unsigned short ushLevel, bool bHardMode)
	{
		CRenderedObject::SetData(mAttributes, ushLevel, bHardMode);

		SetStroke(mAttributes, ushLevel, bHardMode);
		SetFill(mAttributes, ushLevel, bHardMode);
	}

	bool CUse::Draw(IRenderer *pRenderer, const CSvgFile *pFile, CommandeMode oMode, const TSvgStyles* pOtherStyles) const
	{
		if (NULL == pRenderer || !m_oTransformtaion.m_bDraw)
			return false;
		
		Aggplus::CMatrix oTransform;
		
		if (!StartPath(pRenderer, pFile, oTransform))
			return false;
		
		double dM11, dM12, dM21, dM22, dDx, dDy;
		pRenderer->GetTransform(&dM11, &dM12, &dM21, &dM22, &dDx, &dDy);

		Aggplus::CMatrix oNewTransform(dM11, dM12, dM21, dM22, dDx, dDy);
		oNewTransform.Translate(m_oX.ToDouble(NSCSS::Pixel), m_oY.ToDouble(NSCSS::Pixel));

		pRenderer->SetTransform(oNewTransform.sx(), oNewTransform.shy(), oNewTransform.shx(), oNewTransform.sy(), oNewTransform.tx(), oNewTransform.ty());

		const CRenderedObject *pFoundObj = dynamic_cast<CRenderedObject*>(pFile->GetMarkedObject(m_wsHref));

		if (NULL != pFoundObj)
		{
			if (NULL != pOtherStyles)
			{
				TSvgStyles oNewStyles(m_oStyles);
				oNewStyles += *pOtherStyles;
				pFoundObj->Draw(pRenderer, pFile, oMode, &oNewStyles);
			}
			else
				pFoundObj->Draw(pRenderer, pFile, oMode, &m_oStyles);
		}
		
		EndPath(pRenderer, pFile, oTransform);

		return true;
	}

	TBounds CUse::GetBounds() const
	{
		return TBounds{0., 0., 0., 0.};
	}
}
