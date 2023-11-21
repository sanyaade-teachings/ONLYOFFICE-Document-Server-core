#pragma once

#include "ItcFirstLim.h"
#include "Constants.h"

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/IOperand.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
  class CellRangeVertAlign: public IOperand
  {
    private:
	  static const BYTE SIZE_IN_BYTES = 4;
	  BYTE bytes[SIZE_IN_BYTES];

    public:
	  CellRangeVertAlign()
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );
	  }

	  explicit CellRangeVertAlign( const ItcFirstLim& _itc, Constants::VerticalAlign _valign )
	  {
	  	memset( this->bytes, 0, SIZE_IN_BYTES );

		this->bytes[0] = ( SIZE_IN_BYTES - 1 );

		DocFileFormat::FormatUtils::SetBytes( ( this->bytes + sizeof(BYTE) ), (short)_itc );
		this->bytes[sizeof(BYTE) + sizeof(short)] = (BYTE)_valign;
	  }

      CellRangeVertAlign( const CellRangeVertAlign& _cellRangeVertAlign )
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

		memcpy( this->bytes, _cellRangeVertAlign.bytes, SIZE_IN_BYTES );
	  }

	  virtual ~CellRangeVertAlign()
	  {
	  }

	  virtual unsigned int Size() const
	  {
	    return (unsigned int)sizeof(this->bytes);  
	  }

	  virtual operator BYTE*() const
	  {
		return (BYTE*)(this->bytes);
	  }

	  virtual operator const BYTE*() const
	  {
		return (const BYTE*)(this->bytes);
	  }
  };
}
