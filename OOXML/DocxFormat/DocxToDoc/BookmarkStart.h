#pragma once

#include "IParagraphItem.h"

namespace Docx2Doc
{
	class BookmarkStart : public IParagraphItem
	{
	public:
		BookmarkStart()
		{
		}

		explicit BookmarkStart (std::wstring& _id, std::wstring& _name) : id(_id), name(_name)
		{
		}

		virtual ~BookmarkStart()
		{
		}

		virtual unsigned long GetTextSize() const
		{
			return 0;
		}

		virtual std::wstring GetAllText() const
		{
			return std::wstring();
		}

		virtual std::vector<Chpx> GetRunProperties( std::vector<unsigned int>* runOffsets ) const
		{
			return std::vector<Chpx>();
		}

		virtual unsigned int PrlSize () const
		{
			return 0;
		}

		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* runOffsets ) const
		{
			std::vector<IParagraphItemPtr> paragraphItems;

			if ( runOffsets != NULL )
			{
				paragraphItems.push_back( IParagraphItemPtr( static_cast<IParagraphItem*>(this->Clone()) ) );
				runOffsets->push_back( 0 );
			}

			return paragraphItems;
		}

		virtual IVirtualConstructor* New() const
		{
			return new BookmarkStart();
		}

		virtual IVirtualConstructor* Clone() const
		{
			return new BookmarkStart(*this);
		}
		//	
		inline std::wstring GetID() const
		{
			return id;
		}

		inline std::wstring GetName() const
		{
			return name;
		}
	
	private:	
		std::wstring id;
		std::wstring name;
	};
}
