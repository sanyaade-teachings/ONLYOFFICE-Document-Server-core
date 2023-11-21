#pragma once

#include "Constants.h"
#include "grfhic.h"

#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
  class LFO: public IOperand
  {
    private:
	  static const BYTE SIZE_IN_BYTES = 16;
	  BYTE bytes[SIZE_IN_BYTES];

    public:
	  LFO()
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );
	  }

	  explicit LFO( int _lsid, BYTE _clfolvl, Constants::LFOField _ibstFltAutoNum, grfhic _grfhic )
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

		DocFileFormat::FormatUtils::SetBytes( this->bytes, _lsid );

		this->bytes[sizeof(_lsid) + sizeof(int) + sizeof(int)] = _clfolvl;
		this->bytes[sizeof(_lsid) + sizeof(int) + sizeof(int) + sizeof(_clfolvl)] = (BYTE)_ibstFltAutoNum;
		this->bytes[sizeof(_lsid) + sizeof(int) + sizeof(int) + sizeof(_clfolvl) + sizeof(BYTE)] = (BYTE)_grfhic;
	  }

	  LFO( const LFO& _lFO )
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _lFO.bytes, SIZE_IN_BYTES );
	  }

	  virtual ~LFO()
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
