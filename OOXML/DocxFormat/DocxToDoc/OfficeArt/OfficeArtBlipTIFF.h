#pragma once

#include "OfficeArtBlip.h"

// не используется, ms word сохраняет только в png tiff файлы

namespace OfficeArt
{
	class OfficeArtBlipTIFF : public OfficeArtBlip
	{
	public:

		OfficeArtBlipTIFF () : OfficeArtBlip(OfficeArtRecordHeader( 0x0, 0x6E4, 0xF020, 17 )), tag(0), BLIPFileData(NULL), blipFileDataSize(0), bytes(NULL), size(0)
		{
			memset ( rgbUid1, 0, rgbUidsSize );
			memset ( rgbUid2, 0, rgbUidsSize );

			Initialize();
		}

		OfficeArtBlipTIFF (BYTE* _blipFileData, unsigned int _blipFileDataSize, const std::vector<BYTE>& _rgbUid1 = std::vector<BYTE>(), const std::vector<BYTE>& _rgbUid2 = std::vector<BYTE>(), BYTE _tag = 0xFF ):
		OfficeArtBlip(OfficeArtRecordHeader( 0x0, 0x6E4, 0xF020, 17 )), tag(_tag), BLIPFileData(NULL), blipFileDataSize(_blipFileDataSize), bytes(NULL), size(0)
		{
			memset ( rgbUid1, 0, rgbUidsSize );
			memset ( rgbUid2, 0, rgbUidsSize );

			size = _blipFileDataSize;

			if ( _rgbUid2.size() != rgbUidsSize )
			{
				size += 17;

				rh = OfficeArtRecordHeader( 0x0, 0x6E4, 0xF020, size );
			}
			else
			{
				size += 33;

				rh = OfficeArtRecordHeader( 0x0, 0x6E5, 0xF020, size );
			}

			if ( _rgbUid1.size() == rgbUidsSize )
			{
				for ( unsigned int i = 0; i < _rgbUid1.size(); i++ )
				{
					rgbUid1[i] = _rgbUid1[i];
				}
			}

			if ( _rgbUid2.size() == rgbUidsSize )
			{
				for ( unsigned int i = 0; i < _rgbUid2.size(); i++ )
				{
					rgbUid2[i] = _rgbUid2[i];
				}
			}

			if ( ( _blipFileData != NULL ) && ( blipFileDataSize != 0 ) )
			{
				BLIPFileData = new BYTE[blipFileDataSize];

				if ( NULL != BLIPFileData )
				{
					memset (BLIPFileData, 0, blipFileDataSize);
					memcpy (BLIPFileData, _blipFileData, blipFileDataSize);
				}
			}

			Initialize();
		}

		OfficeArtBlipTIFF (const OfficeArtBlipTIFF& oBlipTiff) : OfficeArtBlip(OfficeArtRecordHeader(oBlipTiff.rh)), tag(oBlipTiff.tag), BLIPFileData(NULL), blipFileDataSize(oBlipTiff.blipFileDataSize), bytes(NULL), size(oBlipTiff.size)
		{
			memset( rgbUid1, 0, rgbUidsSize );
			memcpy( rgbUid1, oBlipTiff.rgbUid1, rgbUidsSize );

			memset( rgbUid2, 0, rgbUidsSize );
			memcpy( rgbUid2, oBlipTiff.rgbUid2, rgbUidsSize );

			if ( blipFileDataSize != 0 )
			{
				BLIPFileData = new BYTE[blipFileDataSize];

				if ( NULL != BLIPFileData )
				{
					memset( BLIPFileData, 0, blipFileDataSize );
					memcpy( BLIPFileData, oBlipTiff.BLIPFileData, blipFileDataSize );
				}
			}

			if ( 0 != size )
			{
				bytes = new BYTE[size];

				if ( bytes != NULL )
				{
					memset( bytes, 0, size );
					memcpy( bytes, oBlipTiff.bytes, size );
				}
			}
		}

		virtual operator const BYTE* () const
		{
			return (const BYTE*)(bytes);
		}

		virtual operator BYTE* () const
		{
			return (BYTE*)(bytes);
		}

		virtual unsigned int Size() const
		{
			return size;
		}

		virtual IOfficeArtRecord* New() const
		{
			return new OfficeArtBlipTIFF;
		}

		virtual IOfficeArtRecord* Clone() const
		{
			return new OfficeArtBlipTIFF(*this);
		}

		virtual ~OfficeArtBlipTIFF() 
		{
			RELEASEARRAYOBJECTS(BLIPFileData);
			RELEASEARRAYOBJECTS(bytes);
		}

	private:

		inline void Initialize()
		{
			size = ( sizeof(rh) + rh.GetLength() );

			if ( size != 0 )
			{
				bytes = new BYTE[size];

				if ( NULL != bytes )
				{
					memset( this->bytes, 0, this->size );

					unsigned int offset = 0;

					memcpy( ( this->bytes + offset ), (BYTE*)(this->rh), sizeof(this->rh) );
					offset += sizeof(this->rh);

					memcpy( ( this->bytes + offset ), (BYTE*)(this->rgbUid1), sizeof(this->rgbUid1) );
					offset += sizeof(this->rgbUid1);

					if ( this->rh.GetInstance() == 0x6E5 )
					{
						memcpy( ( this->bytes + offset ), (BYTE*)(this->rgbUid2), sizeof(this->rgbUid2) );
						offset += sizeof(this->rgbUid2);  
					}

					memcpy( ( this->bytes + offset ), &(this->tag), sizeof(this->tag) );
					offset += sizeof(this->tag);

					if ( ( this->BLIPFileData != NULL ) && ( this->blipFileDataSize != 0 ) )
					{
						memcpy( ( this->bytes + offset ), this->BLIPFileData, this->blipFileDataSize );
						offset += this->blipFileDataSize;
					}
				}
			}	      
		}

	private:

		static const BYTE rgbUidsSize = 16;
		
		BYTE			rgbUid1[rgbUidsSize];
		BYTE			rgbUid2[rgbUidsSize];
		BYTE			tag;
		BYTE*			BLIPFileData;
		unsigned int	blipFileDataSize;

		BYTE*			bytes;
		unsigned int	size;
	};
}
