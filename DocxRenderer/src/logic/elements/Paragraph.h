﻿#pragma once
#include "BaseItem.h"
#include "TextLine.h"
#include "../../../convert_params.h"

namespace NSDocxRenderer
{
	class CParagraph : public COutputObject
	{
	public:
		enum TextAlignmentType
		{
			tatUnknown,
			tatByLeftEdge,
			tatByCenter,
			tatByRightEdge,
			tatByWidth
		};

		// text frame properties
		bool                m_bIsNeedFirstLineIndent{false};
		bool                m_bIsShadingPresent     {false};
		LONG                m_lColorOfShadingFill   {c_iWhiteColor}; //BGR
		TextAlignmentType   m_eTextAlignmentType    {tatUnknown};

		// geometry paragraph
		double m_dLeftBorder {0.0}; // сдвиг относительно левого края страницы/шейпа/таблицы
		double m_dRightBorder{0.0}; // сдвиг относительно правого края страницы/шейпа/таблицы
		double m_dFirstLine  {0.0}; // сдвиг относительно m_dLeftBorder

		double m_dSpaceBefore{0.0}; // по умолчанию выставляется 0, если отсутсвует w:before
		double m_dSpaceAfter {0.0}; // в shape по умолчанию выставляется 8pt, если отсутсвует w:after
		double m_dLineHeight {0.0};

		std::vector<std::shared_ptr<CTextLine>> m_arLines;

		size_t m_nNumLines {0};
		std::wstring m_wsStyleId;

	public:
		CParagraph() : COutputObject(COutputObject::eOutputType::etParagraph) {}
		virtual ~CParagraph();
		virtual void Clear() override final;
		virtual void ToXml(NSStringUtils::CStringBuilder& oWriter) const override final;

		void RemoveHighlightColor();
		void MergeLines();

		static TextAlignmentType DetermineTextAlignmentType(std::shared_ptr<CTextLine> pCurrentLine,
			std::shared_ptr<CTextLine> pNextLine,
			std::shared_ptr<CTextLine> pNextNextLine,
			double dPageWidth,
			bool &bIsUseNextNextLine,
			bool &bIsSingleLineParagraph) noexcept;
	};
}
