#pragma once

#include "IRunItem.h"
#include "Constants.h"
#include "Plcfld.h"

#include "../../../MsBinaryFile/Common/Base/TextMark.h"

namespace Docx2Doc
{
	static const WCHAR* FldCharTypeBegin	=	_T("begin");
	static const WCHAR* FldCharTypeSeparate =	_T("separate");
	static const WCHAR* FldCharTypeEnd		=	_T("end");

	class FldChar : public IRunItem
	{
	public:
		static const BYTE FldCharBegin			=	0x13;
		static const BYTE FldCharSeparate		=	0x14;
		static const BYTE FldCharEnd			=	0x15;
	public:

		FldChar () : fld()
		{
			text		=	std::wstring(&TextMark::FieldBeginMark);
			properties.push_back(Prl((short)DocFileFormat::sprmCFSpec, (BYTE*)(&CFSpec)));
		}

		explicit FldChar (const std::wstring& charType, BYTE grffld = 0)
		{
			if (charType == std::wstring (FldCharTypeBegin))
			{
				text	=	std::wstring (&TextMark::FieldBeginMark);
				fld		=	Fld (FldCharBegin, grffld); 
			}

			if (charType == std::wstring (FldCharTypeSeparate))
			{
				text	=	std::wstring (&TextMark::FieldSeparator);
				fld		=	Fld (FldCharSeparate, grffld);
			}

			if (charType == std::wstring (FldCharTypeEnd))
			{
				text	=	std::wstring(&TextMark::FieldEndMark);
				fld		=	Fld (FldCharEnd, grffld);
			}

			properties.push_back (Prl((short)DocFileFormat::sprmCFSpec, (BYTE*)(&CFSpec)));
		}

		virtual ~FldChar()
		{

		}

		inline const Fld& GetField() const
		{
			return fld;
		}

		inline BYTE CharType () const
		{
			return fld.GetFieldCharacterType();
		}

		inline void SetFieldCharacterProperties (BYTE grffld)
		{
			fld.SetProperties(grffld);
		}

		// IRunItem

		virtual IVirtualConstructor* New() const
		{
			return new FldChar();
		}

		virtual IVirtualConstructor* Clone() const
		{
			return new FldChar(*this);
		}

		virtual unsigned long GetTextSize() const
		{
			return text.size();
		}

		virtual std::wstring GetAllText() const
		{
			return text;
		}

		virtual std::vector<Prl> GetRunProperties() const
		{
			std::vector<Prl> prls;

			for (std::list<Prl>::const_iterator iter = properties.begin(); iter != this->properties.end(); ++iter)
				prls.push_back( *iter );

			return prls;
		}

		virtual unsigned int PrlSize () const
		{
			return (unsigned int)properties.size();
		}

	private:
		static const BYTE	CFSpec = 1;

		std::wstring		text;
		std::list<Prl>		properties;
		Fld					fld;
	};
}
