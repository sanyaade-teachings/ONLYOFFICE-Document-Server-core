#ifndef DOCX_ELEMENT_NEW_SHAPE_H
#define DOCX_ELEMENT_NEW_SHAPE_H

#include "Common.h"
#include "../resources/VectorGraphics.h"
#include "ElementParagraph.h"

namespace NSDocxRenderer
{
    class CShape : public CBaseItem
    {
        public:
            std::wstring            m_strPath;
            NSStructures::CBrush	m_oBrush;
            NSStructures::CPen		m_oPen;

            double m_dLeft;
            double m_dTop;
            double m_dWidth;
            double m_dHeight;

            bool m_bIsNoFill;
            bool m_bIsNoStroke;

            LONG m_lCoordSizeX;
            LONG m_lCoordSizeY;

            LONG m_lTxId;

            std::vector<CParagraph*> m_arParagraphs;

            CFontManagerLight* m_pManagerLight;

        public:
            CShape();
            virtual ~CShape();
            virtual void Clear();

            CShape(const CShape& oSrc);

            CShape& operator=(const CShape& oSrc);

            void GetDataFromVector(const CVectorGraphics& oVector, const LONG& lType, const LONG& lCoordSize);

            void WritePath(const CVectorGraphics& oVector, const LONG& lType, const LONG& lCoordSize);

            virtual void ToXml(NSStringUtils::CStringBuilder& oWriter);
    };
};

#endif // DOCX_ELEMENT_NEW_SHAPE_H
