#pragma once

#include "Common.h"
#include "../../../../DesktopEditor/common/Types.h"

namespace OfficeArt
{
#pragma pack(push, 1)
	
  class OfficeArtMetafileHeader
  {
    private:
	  unsigned int cbSize;
	  RECT rcBounds;
	  POINT ptSize;
	  unsigned int cbSave;
	  BYTE compression;
	  const BYTE filter;

    public:
	  OfficeArtMetafileHeader():
	  cbSize(0), rcBounds(), ptSize(), cbSave(0), compression((BYTE)COMPRESSION_METHOD_DEFLATE), filter(0xFE)
	  {
	  }

      explicit OfficeArtMetafileHeader( unsigned int _cbSize, RECT _rcBounds, POINT _ptSize, unsigned int _cbSave, COMPRESSION_METHOD _compression ):
	  cbSize(_cbSize), rcBounds(_rcBounds), ptSize(_ptSize), cbSave(_cbSave), compression((BYTE)_compression), filter(0xFE)
	  {
	  }

	  unsigned int GetUncompressedSize() const
	  {
	    return this->cbSize;
	  }

	  RECT GetClippingRegion() const
	  {
	    return this->rcBounds;
	  }

	  POINT GetSizeToRender() const
	  {
	    return this->ptSize;
	  }

	  unsigned int GetCompressedSize() const
	  {
	    return this->cbSave;
	  }

	  COMPRESSION_METHOD GetCompressionMethod() const
	  {
	    return (COMPRESSION_METHOD)(this->compression);
	  }
  };

#pragma pack(pop)  
}
