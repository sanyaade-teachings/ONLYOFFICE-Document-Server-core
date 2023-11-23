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

#include "COLORREF.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
class Brc: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 8;

	BYTE bytes[SIZE_IN_BYTES];

public:
	Brc()
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );
	}

	explicit Brc( const COLORREF& _cv, BYTE _dptLineWidth, BYTE _brcType, BYTE _dptSpace, bool fShadow, bool fFrame )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		BYTE cvSize = _cv.Size();

		memcpy( this->bytes, (BYTE*)_cv, cvSize );

		BYTE dptLineWidth = 2;

		if ( _dptLineWidth > 2 )
		{
			dptLineWidth = _dptLineWidth;
		}

		this->bytes[cvSize] = dptLineWidth;
		this->bytes[cvSize + sizeof(dptLineWidth)] = _brcType;
		
		unsigned short dptSpaceAndFlags = 0;
		dptSpaceAndFlags |= _dptSpace; //Set dptSpace

		if ( fShadow )
		{
			dptSpaceAndFlags |= 0x20; //Set fShadow
		}

		if ( fFrame )
		{
			dptSpaceAndFlags |= 0x40; //Set fFrame
		}

		DocFileFormat::FormatUtils::SetBytes( ( this->bytes + cvSize + sizeof(dptLineWidth) + sizeof(_brcType) ), dptSpaceAndFlags );
	}

	explicit Brc( const BYTE* _bytes )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		if ( _bytes != NULL )
		{
			memcpy( this->bytes, _bytes, SIZE_IN_BYTES );
		}
	}

	Brc( const Brc& _brc )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _brc.bytes, SIZE_IN_BYTES );
	}

	Brc& operator = ( const Brc& _brc )
	{
		if ( this != &_brc )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _brc.bytes, SIZE_IN_BYTES );
		}

		return *this;
	}

	virtual ~Brc()
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

class BrcOperand: public IOperand
{
private:
	static const BYTE SIZE_IN_BYTES = 9;

	BYTE bytes[SIZE_IN_BYTES];

public:
	BrcOperand()
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );
	}

	explicit BrcOperand( const Brc& _brc )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );

		memcpy( ( this->bytes + sizeof(BYTE) ), (BYTE*)_brc, _brc.Size() );
	}

	BrcOperand( const BrcOperand& _brcOperand )
	{
		memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _brcOperand.bytes, SIZE_IN_BYTES );
	}

	BrcOperand& operator = ( const BrcOperand& _brcOperand )
	{
		if ( this != &_brcOperand )
		{
			memset( this->bytes, 0, SIZE_IN_BYTES );

			memcpy( this->bytes, _brcOperand.bytes, SIZE_IN_BYTES );
		}

		return *this;
	}

	virtual ~BrcOperand()
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
}
