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

#include "ItcFirstLim.h"
#include "Constants.h"

#include "../../../MsBinaryFile/Common/Base/IOperand.h"

namespace Docx2Doc
{
	class CSSA: public IOperand
	{
	private:
		ItcFirstLim itc;
		Constants::Fbrc grfbrc;
		Constants::Fts ftsWidth;
		unsigned short wWidth;

		static const BYTE SIZE_IN_BYTES = 6;
		BYTE bytes[SIZE_IN_BYTES];

	public:
		explicit CSSA( ItcFirstLim _itc, Constants::Fbrc _grfbrc, Constants::Fts _ftsWidth, unsigned short _wWidth ) : itc(_itc), grfbrc(_grfbrc), ftsWidth(_ftsWidth)
		{
			if ( this->ftsWidth == Constants::ftsNil )
			{
				this->wWidth = 0;
			}
			else
			{
				this->wWidth = _wWidth;
			}

			memset( this->bytes, 0, sizeof(this->bytes) );
			memcpy( this->bytes, (void*)(&this->itc), sizeof(this->itc) );
			memcpy( ( this->bytes + sizeof(this->itc) ), &(this->grfbrc), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) ), &(this->ftsWidth), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) + sizeof(BYTE) ), &(this->wWidth), sizeof(this->wWidth) );
		}

		CSSA( const CSSA& _cssa ) : itc(_cssa.itc), grfbrc(_cssa.grfbrc), ftsWidth(_cssa.ftsWidth), wWidth(_cssa.wWidth)
		{
			memset( this->bytes, 0, sizeof(this->bytes) );
			memcpy( this->bytes, (void*)(&this->itc), sizeof(this->itc) );
			memcpy( ( this->bytes + sizeof(this->itc) ), &(this->grfbrc), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) ), &(this->ftsWidth), sizeof(BYTE) );
			memcpy( ( this->bytes + sizeof(this->itc) + sizeof(BYTE) + sizeof(BYTE) ), &(this->wWidth), sizeof(this->wWidth) );
		}

		virtual ~CSSA()
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
	};

	class CSSAOperand: public IOperand
	{
	private:
		CSSA cssa;

		BYTE *bytes;

	public:
		explicit CSSAOperand( const CSSA& _cssa ): cssa(_cssa), bytes(NULL)
		{
			BYTE cssaSize = this->cssa.Size();
			this->bytes = new BYTE[cssaSize + 1];
			memset( this->bytes, 0, ( cssaSize + 1 ) );
			this->bytes[0] = cssaSize;
			memcpy( ( this->bytes + sizeof(BYTE) ), this->cssa.operator BYTE*(), cssaSize );
		}

		CSSAOperand( const CSSAOperand& _CSSAOperand ): cssa(_CSSAOperand.cssa), bytes(NULL)
		{
			BYTE cssaSize = this->cssa.Size();
			this->bytes = new BYTE[cssaSize + 1];
			memset( this->bytes, 0, ( cssaSize + 1 ) );
			this->bytes[0] = cssaSize;
			memcpy( ( this->bytes + sizeof(BYTE) ), this->cssa.operator BYTE*(), cssaSize );
		}

		virtual ~CSSAOperand()
		{
			RELEASEARRAYOBJECTS (bytes);
		}

		virtual operator BYTE*() const
		{
			return this->bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)this->bytes;
		}

		virtual unsigned int Size() const
		{
			return ( this->cssa.Size() + 1 );
		}
	};
}
