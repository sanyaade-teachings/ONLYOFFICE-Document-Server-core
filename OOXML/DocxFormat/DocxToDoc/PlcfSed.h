#pragma once

#include "PLC.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
  class Sed
  {
    private:
	  static const BYTE SIZE_IN_BYTES = 12;
	  BYTE bytes[SIZE_IN_BYTES];

    public:
	  Sed()
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );
	  }

	  explicit Sed( int _fcSepx )
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

		DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(short) ), _fcSepx );
	  }

	  Sed( const Sed& _sed )
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _sed.bytes, SIZE_IN_BYTES );
	  }

	  int GetFcSepx() const
	  {
		return DocFileFormat::FormatUtils::BytesToInt32( (BYTE*)(this->bytes), sizeof(short), SIZE_IN_BYTES );
	  }
  };

  typedef PLC<Sed> PlcfSed;
}
