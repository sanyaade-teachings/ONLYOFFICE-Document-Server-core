#pragma once

#include "IRunItem.h"
#include "CSymbolOperand.h"
#include "Constants.h"

#include "../../../MsBinaryFile/Common/Base/TextMark.h"

namespace Docx2Doc
{
	class EndnoteReference: public IRunItem
	{
	private:
		static const BYTE CFSpec = 1;
		short aEndIdx;

		std::wstring text;
		std::list<Prl> properties;

	public:
		explicit EndnoteReference( short _aEndIdx = 0, unsigned short _ftc = 0, WCHAR _xchar = 0x0000 ):
		aEndIdx(_aEndIdx)
		{
			if ( this->aEndIdx == 0 )
			{
				//!!!TODO!!!
				this->properties.push_back( Prl( (short)DocFileFormat::sprmCSymbol, (BYTE*)CSymbolOperand( _ftc, _xchar ) ) );
			}
			else
			{
				this->text = std::wstring( &TextMark::AutoNumberedEndnoteReference );
				this->properties.push_back( Prl( (short)DocFileFormat::sprmCFSpec, (BYTE*)(&CFSpec) ) );
			}
		}

		EndnoteReference( const EndnoteReference& _endnoteReference ):
		aEndIdx(_endnoteReference.aEndIdx), text(_endnoteReference.text), properties(_endnoteReference.properties)
		{
		}

		short GetIndex() const
		{
			return this->aEndIdx;
		}

		virtual ~EndnoteReference()
		{
		}

		virtual IVirtualConstructor* New() const
		{
			return new EndnoteReference();
		}

		virtual IVirtualConstructor* Clone() const
		{
			return new EndnoteReference(*this);
		}

		virtual unsigned long GetTextSize() const
		{
			return this->text.size();
		}

		virtual std::wstring GetAllText() const
		{
			return this->text;
		}

		virtual std::vector<Prl> GetRunProperties() const
		{
			std::vector<Prl> prls;

			for ( std::list<Prl>::const_iterator iter = this->properties.begin(); iter != this->properties.end(); iter++ )
			{
				prls.push_back( *iter );
			}

			return prls;
		}

		virtual unsigned int PrlSize () const
		{
			return (unsigned int)properties.size();
		}
	};
}
