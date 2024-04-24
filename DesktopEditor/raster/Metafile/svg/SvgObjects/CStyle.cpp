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

#include "CStyle.h"

namespace SVG
{
	CSvgCalculator::CSvgCalculator()
	    : m_pInternal(new NSCSS::CCssCalculator_Private)
	{
		m_pInternal->SetDpi(96);
		m_pInternal->SetUnitMeasure(NSCSS::UnitMeasure::Pixel);
	}

	CSvgCalculator::~CSvgCalculator()
	{
		if (NULL != m_pInternal)
			delete m_pInternal;
	}

	void CSvgCalculator::AddStyles(const std::wstring &wsStyles)
	{
		m_pInternal->AddStyles(wsStyles);
	}

	void CSvgCalculator::Clear()
	{
		m_pInternal->Clear();
	}

	void CSvgCalculator::SetData(CObject *pSvgObject) const
	{
		if (NULL == pSvgObject)
			return;

		const std::map<std::wstring, NSCSS::CElement *> *pData = m_pInternal->GetData();
		const std::vector<NSCSS::CNode> arSelectors = pSvgObject->GetFullPath();

		if ((NULL == pData || pData->empty()) && arSelectors.empty())
			return;

		std::vector<std::wstring> arWords;
		arWords.reserve(arSelectors.size() * 2);

		std::vector<std::wstring> arNextNodes;
		arNextNodes.reserve(arSelectors.size() * 2);

		for (std::vector<NSCSS::CNode>::const_reverse_iterator oNode = arSelectors.rbegin(); oNode != arSelectors.rend(); ++oNode)
		{
			arWords.push_back(oNode->m_wsName);

			if (!oNode->m_wsClass.empty())
			{
				if (oNode->m_wsClass.find(L' ') != std::wstring::npos)
				{
					std::vector<std::wstring> arClasses = NSCSS::NS_STATIC_FUNCTIONS::GetWordsW(oNode->m_wsClass, L" ");

					if (arClasses.size() > 1)
						arClasses.resize(unique(arClasses.begin(),arClasses.end()) - arClasses.begin());

					arWords.push_back(std::accumulate(arClasses.begin(), arClasses.end(), std::wstring(),
					                  [](std::wstring sRes, const std::wstring& sClass)
					                  {return sRes += L'.' + sClass + L' ';}));
				}
				else
					arWords.push_back(L'.' + oNode->m_wsClass);
			}
			if (!oNode->m_wsId.empty())
				arWords.push_back(L'#' + oNode->m_wsId);
		}

		std::vector<NSCSS::CElement*> arElements;

		for (size_t i = 0; i < arSelectors.size(); ++i)
		{
			std::wstring sName, sId;
			std::vector<std::wstring> arClasses;

			if (arWords.back()[0] == L'#')
			{
				sId = arWords.back();
				arWords.pop_back();
				arNextNodes.push_back(sId);
			}

			if (arWords.back()[0] == L'.')
			{
				arClasses = NSCSS::NS_STATIC_FUNCTIONS::GetWordsW(arWords.back(), L" ");
				arNextNodes.push_back(arWords.back());
				arWords.pop_back();
			}

			sName = arWords.back();
			arWords.pop_back();
			arNextNodes.push_back(sName);

			const std::map<std::wstring, NSCSS::CElement*>::const_iterator oFindName = pData->find(sName);
			std::map<std::wstring, NSCSS::CElement*>::const_iterator oFindId;
			std::vector<NSCSS::CElement*> arFindElements;

			if (!sId.empty())
			{
				oFindId = pData->find(sId);

				if (oFindId != std::end(*pData))
				{
					if (!oFindId->second->Empty())
						arFindElements.push_back(oFindId->second);

					const std::vector<NSCSS::CElement*> arTempPrev = oFindId->second->GetPrevElements(arNextNodes.rbegin() + ((arClasses.empty()) ? 1 : 2), arNextNodes.rend());

					if (!arTempPrev.empty())
						arFindElements.insert(arFindElements.end(), arTempPrev.begin(), arTempPrev.end());
				}
			}

			if (!arClasses.empty())
			{
				for (std::vector<std::wstring>::const_reverse_iterator iClass = arClasses.rbegin(); iClass != arClasses.rend(); ++iClass)
				{
					const std::map<std::wstring, NSCSS::CElement*>::const_iterator oFindClass = pData->find(*iClass);
					if (oFindClass != std::end(*pData))
					{
						if (!oFindClass->second->Empty())
							arFindElements.push_back(oFindClass->second);

						const std::vector<NSCSS::CElement*> arTempPrev = oFindClass->second->GetPrevElements(arNextNodes.rbegin() + 2, arNextNodes.rend());
						const std::vector<NSCSS::CElement*> arTempKins = oFindClass->second->GetNextOfKin(sName);

						if (!arTempPrev.empty())
							arFindElements.insert(arFindElements.end(), arTempPrev.begin(), arTempPrev.end());

						if (!arTempKins.empty())
							arFindElements.insert(arFindElements.end(), arTempKins.begin(), arTempKins.end());
					}
				}
			}

			if (oFindName != std::end(*pData))
			{
				if (!oFindName->second->Empty())
					arFindElements.push_back(oFindName->second);

				const std::vector<NSCSS::CElement*> arTempPrev = oFindName->second->GetPrevElements(arNextNodes.rbegin() + 1, arNextNodes.rend());
				const std::vector<NSCSS::CElement*> arTempKins = oFindName->second->GetNextOfKin(sName, arClasses);

				if (!arTempPrev.empty())
					arFindElements.insert(arFindElements.end(), arTempPrev.begin(), arTempPrev.end());

				if (!arTempKins.empty())
					arFindElements.insert(arFindElements.end(), arTempKins.begin(), arTempKins.end());
			}


			if (arFindElements.size() > 1)
			{
				std::sort(arFindElements.rbegin(), arFindElements.rend(),
				          [](NSCSS::CElement* oFirstElement, NSCSS::CElement* oSecondElement)
				          {
					          return oFirstElement->GetWeight() > oSecondElement->GetWeight();
				          });
			}

			pSvgObject->SetData(arSelectors[i].m_mAttributes, i + 1);
			pSvgObject->SetData(arSelectors[i].m_wsStyle, i + 1, true);

			for (const NSCSS::CElement* oElement : arFindElements)
				pSvgObject->SetData(oElement->GetStyle(), i + 1);
		}
	}
}
