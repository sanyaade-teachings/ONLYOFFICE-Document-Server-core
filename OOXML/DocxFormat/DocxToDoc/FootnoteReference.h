#pragma once

#include "IRunItem.h"
#include "CSymbolOperand.h"
#include "Constants.h"

#include "../../../MsBinaryFile/Common/Base/TextMark.h"

namespace Docx2Doc
{
	class FootnoteReference: public IRunItem
	{
	private:
		static const BYTE CFSpec = 1;
		short aFtnIdx;

		std::wstring text;
		std::list<Prl> properties;

	public:
		explicit FootnoteReference( short _aFtnIdx = 0, unsigned short _ftc = 0, WCHAR _xchar = 0x0000 ):
		aFtnIdx(_aFtnIdx)
		{
			if ( this->aFtnIdx == 0 )
			{
				//!!!TODO!!!
				this->properties.push_back( Prl( (short)DocFileFormat::sprmCSymbol, (BYTE*)CSymbolOperand( _ftc, _xchar ) ) );
			}
			else
			{
				this->text = std::wstring( &TextMark::AutoNumberedFootnoteReference );
				this->properties.push_back( Prl( (short)DocFileFormat::sprmCFSpec, (BYTE*)(&CFSpec) ) );
			}
		}

		FootnoteReference( const FootnoteReference& _footnoteReference ):
		aFtnIdx(_footnoteReference.aFtnIdx), text(_footnoteReference.text), properties(_footnoteReference.properties)
		{
		}

		short GetIndex() const
		{
			return this->aFtnIdx;
		}

		virtual ~FootnoteReference()
		{
		}

		virtual IVirtualConstructor* New() const
		{
			return new FootnoteReference();
		}

		virtual IVirtualConstructor* Clone() const
		{
			return new FootnoteReference(*this);
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

		virtual unsigned int PrlSize() const
		{
			return (unsigned int)properties.size();
		}
	};
}
