/*
 * (c) Copyright Ascensio System SIA 2010-2023
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
