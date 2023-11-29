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
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
	class LSPD : public IOperand
	{
	private:
		static const BYTE SIZE_IN_BYTES = 4;

		short dyaLine;
		short fMultLinespace;

		BYTE bytes[SIZE_IN_BYTES];

	public:
		LSPD() : dyaLine(0), fMultLinespace(0)
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );
		}

		explicit LSPD( short _dyaLine, bool _fMultLinespace = true ) : dyaLine(0), fMultLinespace(0)
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			this->dyaLine = _dyaLine;
			( _fMultLinespace ) ? ( this->fMultLinespace = 0x0001 ) : ( this->fMultLinespace = 0x0000 );

			DocFileFormat::FormatUtils::SetBytes( this->bytes, this->dyaLine );
			DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(this->dyaLine) ), this->fMultLinespace );
		}

		LSPD( const LSPD& _lspd ) : dyaLine(_lspd.dyaLine), fMultLinespace(_lspd.fMultLinespace)
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _lspd.bytes, SIZE_IN_BYTES );
		}

		virtual ~LSPD()
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
			return SIZE_IN_BYTES;
		}
	};
}
