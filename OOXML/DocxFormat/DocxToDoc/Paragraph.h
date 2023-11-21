#pragma once

#include "ParagraphItem.h"
#include "TextItem.h"
#include "Prl.h"

namespace Docx2Doc
{
	class Paragraph : public ITextItem
	{
		friend class TableCell;

	private:
		std::list<ParagraphItem> paragraphItems;
		unsigned long runsOffset;
		short style;
		std::list<Prl> properties;

		unsigned int depth;

	protected:
		void SetDepth( unsigned int _depth );
		unsigned int GetDepth() const;

	public:
		typedef std::list<ParagraphItem>::const_iterator const_iterator;
		typedef std::list<ParagraphItem>::iterator iterator;
		typedef std::list<ParagraphItem>::const_reverse_iterator const_reverse_iterator;
		typedef std::list<ParagraphItem>::reverse_iterator reverse_iterator;
		typedef std::list<ParagraphItem>::const_reference const_reference;
		typedef std::list<ParagraphItem>::reference reference;

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
		Paragraph( short _style = 0 );
		void AddParagraphItem( const IParagraphItem& _paragraphItem );
		unsigned long GetTextSize() const;
		virtual ~Paragraph();
		virtual std::wstring GetAllText() const;
		virtual operator std::wstring() const;
		virtual std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const;
		virtual std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const;
		virtual std::vector<TextItemPtr> GetAllParagraphsCopy() const;
		virtual std::vector<ITextItem*> GetAllParagraphs();
		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const;
		virtual std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const;
		virtual IVirtualConstructor* New() const;
		virtual IVirtualConstructor* Clone() const;
		void AddProperty( short sprm, void* operand );
		void AddProperty( const Prl& prl );
		void AddProperties( const std::vector<Prl>& prls );
		void AddOrReplaceProperties( const std::vector<Prl>& prls );
		void RemoveProperty( short sprm, void* operand );
		void RemovePropertyByCode( unsigned short sprm );
		void RemoveAllProperties();
		void SetStyle( short _style );
		short GetStyle() const;
		PapxInFkp GetProperties() const;
		unsigned int GetParagraphPropertiesCount() const;
	};
}
