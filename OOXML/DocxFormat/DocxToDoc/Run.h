#pragma once

#include "IParagraphItem.h"
#include "RunItem.h"
#include "Text.h"
#include "Picture.h"
#include "EndnoteRef.h"
#include "EndnoteReference.h"
#include "FootnoteRef.h"
#include "FootnoteReference.h"
#include "FldChar.h"

namespace Docx2Doc
{
	class Run : public IParagraphItem
	{
	protected:
		std::list<RunItem> items;
		std::list<Prl> properties;

	public:
		typedef std::list<RunItem>::const_iterator const_iterator;
		typedef std::list<RunItem>::iterator iterator;
		typedef std::list<RunItem>::const_reverse_iterator const_reverse_iterator;
		typedef std::list<RunItem>::reverse_iterator reverse_iterator;
		typedef std::list<RunItem>::const_reference const_reference;
		typedef std::list<RunItem>::reference reference;

		const_iterator begin() const;
		const_iterator end() const;
		iterator begin();
		iterator end();
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_reference front() const;
		const_reference back() const;
		reference front();
		reference back();

	public:
		Run();
		Run( const IRunItem& _runItem );
		Run( const Run& _run );
		virtual ~Run();
		Run& operator = ( const Run& _run );
		void AddRunItem( const IRunItem& _runItem );
		virtual unsigned long GetTextSize() const;
		virtual std::wstring GetAllText() const;
		virtual std::vector<Chpx> GetRunProperties( std::vector<unsigned int>* runOffsets ) const;
		virtual unsigned int PrlSize() const;
		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* runOffsets ) const;
		virtual IVirtualConstructor* New() const;
		virtual IVirtualConstructor* Clone() const;
		void AddProperty( short sprm, void* operand );
		void AddProperty( const Prl& prl );
		void AddProperties( const std::vector<Prl>& prls );
		void AddOrReplaceProperties( const std::vector<Prl>& prls );
		void RemoveProperty( short sprm, void* operand );
		void RemovePropertyByCode( unsigned short sprm );
		void RemoveAllProperties();
	};
}
