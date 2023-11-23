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

#include "../../../DesktopEditor/common/Types.h"
#include "../../../MsBinaryFile/Common/Base/Singleton.h"

#include "../../../Common/cfcpp/Stream/stream.h"

namespace Docx2Doc
{
	class BinaryStorage
	{
		struct BinaryStorageData
		{
			BYTE* data;
			unsigned int size;

			BinaryStorageData():
			data(NULL), size(0)
			{
			}

			BinaryStorageData( const BYTE* _data, unsigned int _size ):
			data(NULL), size(0)
			{
				if ( ( _data != NULL ) && ( _size != NULL ) )
				{
					this->size = _size;

					this->data = new BYTE[this->size];

					if ( this->data != NULL )
					{
						memset( this->data, 0, this->size );

						memcpy( this->data, _data, this->size );
					}
				}
			}

			BinaryStorageData( const BinaryStorageData& _binaryStorageData ) : data(NULL), size(0)
			{
				if ( ( _binaryStorageData.data != NULL ) && ( _binaryStorageData.size != NULL ) )
				{
					this->size = _binaryStorageData.size;

					this->data = new BYTE[this->size];

					if ( this->data != NULL )
					{
						memset( this->data, 0, this->size );

						memcpy( this->data, _binaryStorageData.data, this->size );
					}
				}
			}

			~BinaryStorageData()
			{
				RELEASEARRAYOBJECTS (data);
			}
		};

	protected:
		//CFCPP::IStorage* pIStorage;
		void* pIStorage;
		CFCPP::IStream* pIStream;

		std::list<BinaryStorageData> data;
		unsigned long offset;
		unsigned long startOffset;
		bool ownStream;

	public:
		explicit BinaryStorage( unsigned long _startOffset = 0, CFCPP::IStream* _pIStream = NULL ) :
		pIStream(_pIStream), pIStorage(NULL), offset(_startOffset), startOffset(_startOffset), ownStream(false)
		{
		}

		long BindToStorage( /*IStorage*/void* _pIStorage, const wchar_t* _stream )
		{
			/*HRESULT res = S_FALSE;

			this->pIStorage = _pIStorage;

			if ( this->pIStorage != NULL )
			{
				if ( ( this->pIStream != NULL ) && ( this->ownStream ) )
				{
					this->pIStream->Release();
					this->pIStream = NULL;
				}

				res = this->pIStorage->OpenStream( _stream, NULL, ( STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE ), NULL, &(this->pIStream) );

				if ( FAILED( res ) )
				{
					res = this->pIStorage->CreateStream( _stream, ( STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE ), NULL, NULL, &(this->pIStream) );
				}
			}

			if ( SUCCEEDED( res ) )
			{
				this->ownStream = true;
			}

			return res;*/

			return 0;
		}

		virtual ~BinaryStorage()
		{
			if ( ( this->pIStream != NULL ) && ( this->ownStream ) )
			{
				//this->pIStream->Release();
				this->pIStream = NULL;
			}
		}

		unsigned long PushData( const BYTE* _data, unsigned int _size )
		{
			this->data.push_back( BinaryStorageData( _data, _size ) );

			unsigned long dataOffset = this->offset;

			this->offset += _size;

			return dataOffset;
		}

		unsigned long ClearData()
		{
			this->data.clear();

			this->offset = this->startOffset;

			return this->offset;
		}

		long WriteData()
		{
			/*long res = S_OK;
			ULONG writtenSize;

			LARGE_INTEGER pos = { 0, 0 };

			pos.HighPart = 0;
			pos.LowPart = this->startOffset;

			if ( this->pIStream != NULL )
			{
				for ( list<BinaryStorageData>::const_iterator iter = this->data.begin(); iter != this->data.end(); iter++ )
				{
					res = this->pIStream->Seek( pos, STREAM_SEEK_SET, NULL );
					res = this->pIStream->Write( iter->data, iter->size, &writtenSize );
					pos.LowPart += iter->size;
				}
			}
			else
			{
				res = S_FALSE;
			}

			return res;*/

			return 0;
		}
	};

	class BinaryStorageSingleton: public Singleton<BinaryStorageSingleton>, public BinaryStorage
	{
	protected:
		BinaryStorageSingleton(): BinaryStorage() {};
		virtual ~BinaryStorageSingleton() {};
		friend class Singleton<BinaryStorageSingleton>;
	};
}
