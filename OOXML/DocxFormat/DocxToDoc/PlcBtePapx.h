
#pragma once

#include "IStreamWriter.h"
#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
class PlcBtePapx: public IStreamWriter
{
private:
	std::vector<unsigned int> aFC;
	std::vector<unsigned int> aPnBtePapx;

public:
	PlcBtePapx( const std::vector<unsigned int>& _aFC, const std::vector<unsigned int>& _aPnBtePapx ):
		aFC(_aFC), aPnBtePapx(_aPnBtePapx)
	{
	}

	virtual ~PlcBtePapx()
	{
	}

	virtual BYTE* GetBytes( unsigned long* size ) const
	{
		BYTE* bytes = NULL;

		if ( size != NULL )
		{
			*size = ( ( sizeof(unsigned int) * this->aFC.size() ) + ( sizeof(unsigned int) * this->aPnBtePapx.size() ) );
			bytes = new BYTE[*size];

			if ( bytes != NULL )
			{
				memset( bytes, 0, *size );

				unsigned int i = 0;

				for ( i = 0; i < this->aFC.size(); i++ )
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + ( i * sizeof(unsigned int) ) ), (int)this->aFC[i] );
				}

				for ( i = 0; i < this->aPnBtePapx.size(); i++ )
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + ( sizeof(unsigned int) * this->aFC.size() ) + ( i * sizeof(unsigned int) ) ), (int)this->aPnBtePapx[i] );
				}
			}
		}

		return bytes;
	}
};
}
