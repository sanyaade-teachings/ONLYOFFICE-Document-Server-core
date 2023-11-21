#pragma once

#include "../../../../DesktopEditor/common/Types.h"
#include "IOfficeArtAbstractContainer.h"
#include "IOfficeArtRecord.h"

namespace OfficeArt
{
	class OfficeArtWordDrawing : public IOfficeArtAbstractContainer<IOfficeArtRecord>
	{
	public:

		OfficeArtWordDrawing(unsigned char type = 0) : dgglbl(type), bytes(NULL), size(sizeof(dgglbl))
		{
			Initialize();
		}

		OfficeArtWordDrawing(const OfficeArtWordDrawing& _container) : dgglbl(_container.dgglbl), officeArtRecords(_container.officeArtRecords), size(_container.size), bytes(NULL)
		{
			if ( size != 0 )
			{
				bytes = new BYTE[size];

				if (bytes)
				{
					memset (bytes, 0, size);
					memcpy (bytes, _container.bytes, size);
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
			return this->size;
		}

		virtual IOfficeArtRecord* New() const
		{
			return new OfficeArtWordDrawing;
		}

		virtual IOfficeArtRecord* Clone() const
		{
			return new OfficeArtWordDrawing (*this);
		}

		virtual void PushBack(const IOfficeArtRecord& _officeArtRecord)
		{
			officeArtRecords.push_back(OfficeArtRecordPtr(_officeArtRecord.Clone()));

			Initialize();
		}

		virtual unsigned int Count() const
		{
			return (unsigned int) officeArtRecords.size();
		}

		virtual void Clear()
		{
			officeArtRecords.clear();

			Initialize();
		}

		virtual ~OfficeArtWordDrawing() 
		{
			RELEASEARRAYOBJECTS (bytes);
		}

	private:

		inline void Initialize()
		{
			size = 0;

			for (std::list<OfficeArtRecordPtr>::const_iterator iter = officeArtRecords.begin(); iter != officeArtRecords.end(); ++iter)
			{
				size += (*iter)->Size();
			}

			size += sizeof(dgglbl);

			RELEASEARRAYOBJECTS (bytes);

			if (0 != size)
			{
				bytes = new BYTE[size];
				if (bytes)
				{
					memset (bytes, 0, size);

					unsigned int offset = 0;

					memcpy( (bytes + offset ), &dgglbl, sizeof(dgglbl) );
					offset += sizeof(dgglbl);

					for (std::list<OfficeArtRecordPtr>::const_iterator iter = officeArtRecords.begin(); iter != officeArtRecords.end(); ++iter)
					{
						const IOfficeArtRecord* officeArtRecord = iter->operator->();
						if (officeArtRecord)
						{
							memcpy( (bytes + offset), (BYTE*)(*officeArtRecord), officeArtRecord->Size());
							offset += officeArtRecord->Size();
						}
					}
				}
			}
		}

	protected:

		unsigned char					dgglbl;
		std::list<OfficeArtRecordPtr>	officeArtRecords;

		BYTE*							bytes;
		unsigned int					size;
	};
}
