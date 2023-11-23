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

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"

namespace Docx2Doc
{
	class COLORREF : public IOperand
	{
	public:
		static const int cvAuto = 0xFF000000;

		COLORREF() : red(0), green(0), blue(0), fAuto(0xFF)
		{
			this->bytes[0] = this->red;
			this->bytes[1] = this->green;
			this->bytes[2] = this->blue;
			this->bytes[3] = this->fAuto;
		}

		explicit COLORREF( BYTE _red, BYTE _green, BYTE _blue, BYTE _fAuto = 0xFF ) : red(_red), green(_green), blue(_blue), fAuto(_fAuto)
		{
			this->bytes[0] = this->red;
			this->bytes[1] = this->green;
			this->bytes[2] = this->blue;
			this->bytes[3] = this->fAuto;
		}

		explicit COLORREF( unsigned int _value ) : red(0), green(0), blue(0), fAuto(0)
		{
			this->red = ( _value >> 16 ) & 0x000000FF;
			this->green = ( _value >> 8 ) & 0x000000FF;
			this->blue = _value & 0x000000FF;
			this->fAuto = ( _value >> 24 ) & 0x000000FF;

			this->bytes[0] = this->red;
			this->bytes[1] = this->green;
			this->bytes[2] = this->blue;
			this->bytes[3] = this->fAuto;
		}

		COLORREF( const COLORREF& _colorref ) : red(_colorref.red), green(_colorref.green), blue(_colorref.blue), fAuto(_colorref.fAuto)
		{
			this->bytes[0] = this->red;
			this->bytes[1] = this->green;
			this->bytes[2] = this->blue;
			this->bytes[3] = this->fAuto;
		}

		BYTE GetRed() const
		{
			return this->red;
		}

		BYTE GetGreen() const
		{
			return this->green;
		}

		BYTE GetBlue() const
		{
			return this->blue;
		}

		BYTE GetAuto() const
		{
			return this->fAuto;
		}

		virtual ~COLORREF()
		{
		}

		virtual operator BYTE*() const
		{
			return (BYTE*)this->bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)this->bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeof(this->bytes);
		}

	private:

		BYTE red;
		BYTE green;
		BYTE blue;
		BYTE fAuto;

		static const BYTE SIZE_IN_BYTES = 4;

		BYTE bytes[SIZE_IN_BYTES];
	};
}
