#pragma once

#include "Constants.h"
#include "STTB.h"

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
	union FFID
	{
	private:
		struct
		{
			BYTE prq:2;
			BYTE fTrueType:1;
			BYTE unused1:1;
			BYTE ff:3;
			BYTE unused2:1;
		} FFIDStruct;
		BYTE FFIDByte;

	public:
		FFID():
		  FFIDByte(0)
		  {
		  }

		  FFID( BYTE _ffid ):
		  FFIDByte(_ffid)
		  {
		  }

		  explicit FFID( Constants::CharacterPitch _characterPitch, bool _isTrueTypeFont, Constants::FontFamilyType _fontFamilyType ):
		  FFIDByte(0)
		  {
			  this->FFIDStruct.prq = (unsigned short)_characterPitch;
			  ( _isTrueTypeFont ) ? ( this->FFIDStruct.fTrueType = 1 ) : ( this->FFIDStruct.fTrueType = 0 );
			  this->FFIDStruct.ff = (unsigned short)_fontFamilyType;
		  }

		  operator BYTE() const
		  {
			  return this->FFIDByte;
		  }
	};

	struct PANOSE
	{
		BYTE bFamilyType;
		BYTE bSerifStyle;
		BYTE bWeight;
		BYTE bProportion;
		BYTE bContrast;
		BYTE bStrokeVariation;
		BYTE bArmStyle;
		BYTE bLetterform;
		BYTE bMidline;
		BYTE bHeight;

		PANOSE():
		bFamilyType(PAN_ANY), bSerifStyle(PAN_ANY), bWeight(PAN_ANY), bProportion(PAN_ANY),
			bContrast(PAN_ANY), bStrokeVariation(PAN_ANY), bArmStyle(PAN_ANY), bLetterform(PAN_ANY),
			bMidline(PAN_ANY), bHeight(PAN_ANY)
		{
		}

		explicit PANOSE( BYTE _bFamilyType, BYTE _bSerifStyle, BYTE _bWeight, BYTE _bProportion, BYTE _bContrast,
			BYTE _bStrokeVariation, BYTE _bArmStyle, BYTE _bLetterform, BYTE _bMidline, BYTE _bHeight ):
		bFamilyType(_bFamilyType), bSerifStyle(_bSerifStyle), bWeight(_bWeight), bProportion(_bProportion),
			bContrast(_bContrast), bStrokeVariation(_bStrokeVariation), bArmStyle(_bArmStyle), bLetterform(_bLetterform),
			bMidline(_bMidline), bHeight(_bHeight)
		{
		}
	};

	class FFN: public IOperand
	{
	private:
		FFID ffid;
		short wWeight;
		BYTE chs;
		BYTE ixchSzAlt;
		PANOSE panose;
		FONTSIGNATURE fs;
		std::wstring xszFfn;
		std::wstring xszAlt;

		BYTE* bytes;
		unsigned int sizeInBytes;

		void SetBytes()
		{
			this->sizeInBytes = ( sizeof(this->ffid) + sizeof(this->wWeight) + sizeof(this->chs) + 
				sizeof(this->ixchSzAlt) + sizeof(this->panose) + sizeof(this->fs) + 
				( sizeof(WCHAR) * ( this->xszFfn.size() + 1 ) ) );

			if ( this->ixchSzAlt != 0 )
			{
				this->sizeInBytes += ( sizeof(WCHAR) * ( this->xszAlt.size() + 1 ) );
			}

			this->bytes = new BYTE[this->sizeInBytes];

			if ( this->bytes != NULL )
			{
				memset( this->bytes, 0, this->sizeInBytes );

				this->bytes[0] = (BYTE)this->ffid;
				DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(this->ffid) ), this->wWeight );
				this->bytes[3] = this->chs;
				this->bytes[4] = this->ixchSzAlt;
				this->bytes[5] = this->panose.bFamilyType;
				this->bytes[6] = this->panose.bSerifStyle;
				this->bytes[7] = this->panose.bWeight;
				this->bytes[8] = this->panose.bProportion;
				this->bytes[9] = this->panose.bContrast;
				this->bytes[10] = this->panose.bStrokeVariation;
				this->bytes[11] = this->panose.bArmStyle;
				this->bytes[12] = this->panose.bLetterform;
				this->bytes[13] = this->panose.bMidline;
				this->bytes[14] = this->panose.bHeight;

				memcpy( ( this->bytes + sizeof(this->ffid) + sizeof(this->wWeight) + sizeof(this->chs) +
					sizeof(this->ixchSzAlt) + sizeof(this->panose) ), &(this->fs), sizeof(this->fs) );

				memcpy( ( this->bytes + sizeof(this->ffid) + sizeof(this->wWeight) + sizeof(this->chs) +
					sizeof(this->ixchSzAlt) + sizeof(this->panose) + sizeof(this->fs) ), this->xszFfn.c_str(), ( sizeof(WCHAR) * ( this->xszFfn.size() + 1 ) ) );

				if ( this->ixchSzAlt != 0 )
				{
					memcpy( ( this->bytes + sizeof(this->ffid) + sizeof(this->wWeight) + sizeof(this->chs) +
						sizeof(this->ixchSzAlt) + sizeof(this->panose) + sizeof(this->fs) + ( sizeof(WCHAR) * ( this->xszFfn.size() + 1 ) ) ), this->xszAlt.c_str(), ( sizeof(WCHAR) * ( this->xszAlt.size() + 1 ) ) );
				}
			}
		}

	public:

		FFN() :  ffid(), wWeight(0), chs(ANSI_CHARSET), ixchSzAlt(0), panose(), bytes(NULL), sizeInBytes(0)
		{
			memset( &(this->fs), 0, sizeof(this->fs) );

			this->SetBytes();
		}

		explicit FFN( const FFID& _ffid, short _wWeight, BYTE _chs, const PANOSE& _panose, const FONTSIGNATURE& _fs, const std::wstring& _xszFfn, const std::wstring& _xszAlt = std::wstring( _T( "" ) ) ) : ffid(_ffid), chs(_chs), panose(_panose), xszFfn(_xszFfn), xszAlt(_xszAlt), bytes(NULL), sizeInBytes(0)
		{
			memcpy( &(this->fs), &_fs, sizeof(FONTSIGNATURE) );

			if ( _wWeight < 0 )
			{
				this->wWeight = 0;
			}
			else if ( _wWeight > 1000 )
			{
				this->wWeight = 1000;
			}
			else
			{
				this->wWeight = _wWeight;
			}

			if ( !_xszAlt.empty() )
			{
				this->ixchSzAlt = ( this->xszFfn.size() + 1 );
			}
			else
			{
				this->ixchSzAlt = 0;
			}

			this->SetBytes();
		}

		FFN( const FFN& _ffn ) : ffid(_ffn.ffid), wWeight(_ffn.wWeight), chs(_ffn.chs), ixchSzAlt(_ffn.ixchSzAlt), panose(_ffn.panose), xszFfn(_ffn.xszFfn), xszAlt(_ffn.xszAlt), bytes(NULL), sizeInBytes(_ffn.sizeInBytes)
		{
			memcpy( &(this->fs), &(_ffn.fs), sizeof(FONTSIGNATURE) );

			this->SetBytes();
		}

		virtual ~FFN()
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
			return this->sizeInBytes;
		}
	};

	typedef STTB<FFN> SttbfFfn;
}
