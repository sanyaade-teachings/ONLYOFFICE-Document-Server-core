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

#include "../WritingElement.h"
#include "../../Base/Nullable.h"

#include "../../Common/SimpleTypes_Spreadsheet.h"

namespace PPTX
{
	namespace Logic
	{
		class SpTreeElem;
	}
}

namespace OOX
{
	namespace Spreadsheet
	{
		class CFromTo;
		class CPos;
		class CExt;
		class CClientData;

		class CClientData : public WritingElement
		{
		public:
			WritingElement_AdditionMethods(CClientData)
			CClientData();
			virtual ~CClientData();

			virtual void fromXML(XmlUtils::CXmlNode& node);
			virtual std::wstring toXML() const;

			virtual void toXML(NSStringUtils::CStringBuilder& writer) const;
			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader);

			virtual EElementType getType() const;

		private:
			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader);

		public:
			nullable_bool fLocksWithSheet;
			nullable_bool fPrintsWithSheet;
		};

		class CCellAnchor : public WritingElement
		{
		public:
			WritingElement_AdditionMethods(CCellAnchor)
           
			CCellAnchor();
			CCellAnchor(const SimpleTypes::Spreadsheet::ECellAnchorType& oAnchorType);
			CCellAnchor(const SimpleTypes::Spreadsheet::CCellAnchorType& oAnchorType);
			virtual ~CCellAnchor();

			virtual void fromXML(XmlUtils::CXmlNode& node);
			virtual std::wstring toXML() const;

			std::wstring toVmlXML() const;
			virtual void toXML(NSStringUtils::CStringBuilder& writer) const;

			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader);
			virtual EElementType getType () const;

			virtual void setAnchorType (SimpleTypes::Spreadsheet::ECellAnchorType eType);
			virtual SimpleTypes::Spreadsheet::ECellAnchorType getAnchorType () const;

			bool isValid() const;

		private:
			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader);
			void ReadAttributesRequire(XmlUtils::CXmlLiteReader& oReader, std::wstring& sRequire);

		public:
			bool												m_bShapeOle;
			bool												m_bShapeControl;

			SimpleTypes::Spreadsheet::CCellAnchorType			m_oAnchorType;
			nullable<SimpleTypes::Spreadsheet::CCellAnchorType> m_oEditAs;
			nullable<OOX::Spreadsheet::CFromTo>					m_oFrom;
			nullable<OOX::Spreadsheet::CFromTo>					m_oTo;
			nullable<OOX::Spreadsheet::CPos>					m_oPos;
			nullable<OOX::Spreadsheet::CExt>					m_oExt;
			nullable<OOX::Spreadsheet::CClientData>				m_oClientData;

			nullable<PPTX::Logic::SpTreeElem>					m_oElement;

		//для удобства
			nullable<std::wstring>								m_sVmlSpId;
			nullable<int>										m_nId;
		};
	} //Spreadsheet
} // namespace OOX
