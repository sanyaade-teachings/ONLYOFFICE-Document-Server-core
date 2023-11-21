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
