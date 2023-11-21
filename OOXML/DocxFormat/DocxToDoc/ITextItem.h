#pragma once

#include "PapxInFkp.h"
#include "Run.h"

namespace Docx2Doc
{
	struct ITextItem;  

	typedef NSCommon::smart_ptr<ITextItem> TextItemPtr;

	struct ITextItem : public IVirtualConstructor
	{
		virtual std::wstring GetAllText() const = 0;
		virtual operator std::wstring() const = 0;
		virtual std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const = 0;
		virtual std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const = 0;
		virtual std::vector<TextItemPtr> GetAllParagraphsCopy() const = 0;
		virtual std::vector<ITextItem*> GetAllParagraphs() = 0;
		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const = 0;
		virtual std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const = 0;

		virtual ~ITextItem() {}
	};
}
