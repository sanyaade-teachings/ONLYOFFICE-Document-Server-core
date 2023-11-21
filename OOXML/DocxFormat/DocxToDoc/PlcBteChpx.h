
#pragma once

#include "IStreamWriter.h"
#include "../../../MsBinaryFile/Common/Base/FormatUtils.h"

namespace Docx2Doc
{
class PlcBteChpx: public IStreamWriter
{
private:
	std::vector<unsigned int> aFC;
	std::vector<unsigned int> aPnBteChpx;

public:
	PlcBteChpx( const std::vector<unsigned int>& _aFC, const std::vector<unsigned int>& _aPnBteChpx ) : aFC(_aFC), aPnBteChpx(_aPnBteChpx)
	{
	}

	virtual ~PlcBteChpx()
	{
	}

	virtual BYTE* GetBytes( unsigned long* size ) const
	{
		BYTE* bytes = NULL;

		if ( size != NULL )
		{
			*size = ( ( sizeof(unsigned int) * this->aFC.size() ) + ( sizeof(unsigned int) * this->aPnBteChpx.size() ) );
			bytes = new BYTE[*size];

			if ( bytes != NULL )
			{
				memset( bytes, 0, *size );

				unsigned int i = 0;

				for ( i = 0; i < this->aFC.size(); i++ )
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + ( i * sizeof(unsigned int) ) ), (int)this->aFC[i] );
				}

				for ( i = 0; i < this->aPnBteChpx.size(); i++ )
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + ( sizeof(unsigned int) * this->aFC.size() ) + ( i * sizeof(unsigned int) ) ), (int)this->aPnBteChpx[i] );
				}
			}
		}

		return bytes;
	}
};
}
