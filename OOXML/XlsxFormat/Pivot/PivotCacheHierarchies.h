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
#pragma once
#include "../WritingElement.h"
#include "../FileTypes_Spreadsheet.h"

#include "../../Common/ComplexTypes.h"

namespace OOX
{
namespace Spreadsheet
{
    class CfieldsUsage : public WritingElement
    {
    public:
        WritingElement_AdditionMethods(CfieldsUsage)
        WritingElement_XlsbConstructors(CfieldsUsage)
        CfieldsUsage(){}
        virtual ~CfieldsUsage() {}

        virtual void fromXML(XmlUtils::CXmlNode& node)
        {
        }
        virtual std::wstring toXML() const
        {
            return _T("");
        }
        virtual void toXML(NSStringUtils::CStringBuilder& writer) const;
        virtual void fromXML(XmlUtils::CXmlLiteReader& oReader);
        void ReadAttributes(XmlUtils::CXmlLiteReader& oReader);
        void fromBin(XLS::BaseObjectPtr& obj);
        XLS::BaseObjectPtr toBin();

        
        nullable_int		 m_oCount;
        std::vector<_INT32> m_oFieldUsage;
    };

    class CpivotCacheHierarchy : public WritingElement
    {
    public:
        WritingElement_AdditionMethods(CpivotCacheHierarchy)
        WritingElement_XlsbConstructors(CpivotCacheHierarchy)
        CpivotCacheHierarchy(){}
        virtual ~CpivotCacheHierarchy() {}

        virtual void fromXML(XmlUtils::CXmlNode& node)
        {
        }
        virtual std::wstring toXML() const
        {
            return _T("");
        }
        virtual void toXML(NSStringUtils::CStringBuilder& writer) const;
        virtual void fromXML(XmlUtils::CXmlLiteReader& oReader);
        void ReadAttributes(XmlUtils::CXmlLiteReader& oReader);
        void fromBin(XLS::BaseObjectPtr& obj);
        XLS::BaseObjectPtr toBin();

        nullable_string		m_oUniqueName;
        nullable_string		m_oCaption;
        nullable_int		m_oAttribute;
        nullable_string     m_oDefaultMemberUniqueName;
        nullable_string     m_oAllUniqueName;
        nullable_string     m_oDimensionUniqueName;
        nullable_string     m_oDisplayFolder;
        nullable_int		m_oCount;
        nullable_int		m_oMemberValueDatatype;
        nullable_int		m_oUnbalanced;

        nullable<CfieldsUsage>	m_oFieldsUsage;

    };
    class CpivotCacheHierarchies : public WritingElementWithChilds<CpivotCacheHierarchy>
		{
		public:
			WritingElement_AdditionMethods(CpivotCacheHierarchies)
            WritingElement_XlsbConstructors(CpivotCacheHierarchies)
			CpivotCacheHierarchies(){}
			virtual ~CpivotCacheHierarchies() {}

			virtual void fromXML(XmlUtils::CXmlNode& node)
			{
			}
            virtual std::wstring toXML() const
			{
				return _T("");
			}
			virtual void toXML(NSStringUtils::CStringBuilder& writer) const;
			virtual void fromXML(XmlUtils::CXmlLiteReader& oReader);
            void fromBin(XLS::BaseObjectPtr& obj);
			XLS::BaseObjectPtr toBin();

			nullable<SimpleTypes::CUnsignedDecimalNumber>	m_oCount;
			
		};

}
}
