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

#include "ITextItem.h"
#include "TextItem.h"
#include "PLC.h"

#include "../../../MsBinaryFile/Common/Base/IOperand.h"

namespace Docx2Doc
{
	// BreaK Descriptor (BKD)
	class Tbkd : public IOperand
	{
	public:
		static const int SIZE_IN_BYTES = 6;

		Tbkd () : itxbxs(-1), dcpDepend(0), fMarkDelete(false), fUnk(false), fTextOverflow(false)
		{
			Update ();
		}

		Tbkd (short nItxbxs, short nDcpDepend) : itxbxs(nItxbxs), dcpDepend(nDcpDepend), fMarkDelete(false), fUnk(false), fTextOverflow(false)
		{
			Update ();
		}

		virtual ~Tbkd()
		{

		}

		Tbkd (const Tbkd& oTbkd)
		{
			itxbxs			=	oTbkd.itxbxs;
			dcpDepend		=	oTbkd.dcpDepend;

			fMarkDelete		=	oTbkd.fMarkDelete;
			fUnk			=	oTbkd.fUnk;
			fTextOverflow	=	oTbkd.fTextOverflow;

			memset(bytes, 0, SIZE_IN_BYTES);
			memcpy(bytes, oTbkd.bytes, SIZE_IN_BYTES);
		}

		// IOperand
		virtual operator BYTE*() const
		{
			return (BYTE*)(bytes);
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeof(bytes);
		}

		//
		inline void Update ()
		{
			memset(bytes, 0, SIZE_IN_BYTES);

			unsigned int offset = 0;

			DocFileFormat::FormatUtils::SetBytes((bytes + offset), itxbxs);				offset += sizeof(short);
			DocFileFormat::FormatUtils::SetBytes((bytes + offset), dcpDepend);				offset += sizeof(short);

			DocFileFormat::BitSet oBits(2);
			oBits.SetBit(false,			0);	
			oBits.SetBit(false,			1);
			oBits.SetBit(false,			2);
			oBits.SetBit(false,			3);
			oBits.SetBit(false,			4);
			oBits.SetBit(false,			5);	
			oBits.SetBit(false,			6);
			oBits.SetBit(false,			7);
			oBits.SetBit(false,			8);
			oBits.SetBit(false,			9);
			oBits.SetBit(false,			10);	
			oBits.SetBit(false,			11);

			oBits.SetBit(fMarkDelete,	12);
			oBits.SetBit(fUnk,			13);
			oBits.SetBit(fTextOverflow,	14);

			oBits.SetBit(false,			15);


			DocFileFormat::FormatUtils::SetBytes((bytes + offset),	DocFileFormat::FormatUtils::BytesToInt16 (oBits.GetBytes(), 0, sizeof(unsigned short)));
		}

	private:
		BYTE bytes [SIZE_IN_BYTES];

		short	itxbxs;
		short	dcpDepend;

		bool	fMarkDelete;		//	This value MUST be zero and MUST be ignored.
		bool	fUnk;				//	This value SHOULD<257> be zero and SHOULD<258> be ignored
		bool	fTextOverflow;		//	This value SHOULD<259> be zero and SHOULD<260> be ignored.
	};

	class FTXBXS
	{
	public:

		struct FTXBXSReusable
		{
			int	iNextReuse;
			int cReusable;
		};

		struct FTXBXNonReusable
		{
			int cTxbx;
			int cTxbxEdit;				//	This value MUST be zero and MUST be ignored.
		};

	public:
		static const int SIZE_IN_BYTES = 22;

		FTXBXS () : lid(0), txidUndo(0), fReusable(0), itxbxsDest(-1), reusable01(-1), reusable02(0)
		{
			Update ();
		}

		FTXBXS (int nLid) : lid(nLid), txidUndo(0), fReusable(0), itxbxsDest(-1), reusable01(1), reusable02(0)
		{
			Update ();
		}

		virtual ~FTXBXS()
		{

		}

		FTXBXS (const FTXBXS& oFTXBXS)
		{
			reusable01		=	oFTXBXS.reusable01;
			reusable02		=	oFTXBXS.reusable02;

			fReusable		=	oFTXBXS.fReusable;
			itxbxsDest		=	oFTXBXS.itxbxsDest;
			lid				=	oFTXBXS.lid;
			txidUndo		=	oFTXBXS.txidUndo;

			memset(bytes, 0, SIZE_IN_BYTES);
			memcpy(bytes, oFTXBXS.bytes, SIZE_IN_BYTES);
		}

		// IOperand
		virtual operator BYTE*() const
		{
			return (BYTE*)(bytes);
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeof(bytes);
		}

		//
		inline void Update ()
		{
			memset(bytes, 0, SIZE_IN_BYTES);

			unsigned int offset = 0;

			DocFileFormat::FormatUtils::SetBytes((bytes + offset), reusable01);				offset += sizeof(int);
			DocFileFormat::FormatUtils::SetBytes((bytes + offset), reusable02);				offset += sizeof(int);
			DocFileFormat::FormatUtils::SetBytes((bytes + offset), fReusable);				offset += sizeof(short);
			DocFileFormat::FormatUtils::SetBytes((bytes + offset), itxbxsDest);				offset += sizeof(int);
			DocFileFormat::FormatUtils::SetBytes((bytes + offset), lid);					offset += sizeof(int);
			DocFileFormat::FormatUtils::SetBytes((bytes + offset), txidUndo);				offset += sizeof(int);
		}

	private:

		BYTE bytes [SIZE_IN_BYTES];

		// FTXBXSReusable	|| 	FTXBXNonReusable
		int					reusable01;
		int					reusable02;

		short				fReusable;		//	ставим в 0 потому что один TbRef привязан к одному элементу
		int					itxbxsDest;		//	This field MUST be ignored.
		int					lid;			/*

											When fReusable is "false", lid MUST match the OfficeArtFSP.spid shape identifier in an 
											OfficeArtSpContainer structure as specified by [MS-ODRAW] section 2.2.14. Furthermore, 
											the MSOPSText_lTxid property of the OfficeArtSpContainer, as specified in [MS-ODRAW]
											section 2.3.21.1, MUST be a 4-byte integer where the high 2 bytes divided by 0x10000 gives 
											the 1-based index of this FTXBXS structure in its PLC, and where the low 2 bytes are 0x0000.

											*/

		int					txidUndo;		//	This value MUST be zero and MUST be ignored.
	};

	//
	class PlcftxbxTxt : public IOperand
	{
	public:

		PlcftxbxTxt(): bytes(NULL), sizeInBytes(0)
		{
			bytes = new BYTE [sizeInBytes];

			if (bytes)
				memset(bytes, 0, sizeInBytes);
		}

		PlcftxbxTxt(const std::vector<unsigned int>& aCP, const std::vector<FTXBXS>& oFTXBXS) : bytes(NULL), sizeInBytes(0)
		{
			sizeInBytes	=	( (aCP.size() * sizeof(unsigned int) ) + ( oFTXBXS.size() * FTXBXS::SIZE_IN_BYTES ) );

			bytes		=	new BYTE[sizeInBytes];
			if (bytes)
			{
				memset (bytes, 0,sizeInBytes);

				unsigned int offset = 0;
				for ( std::vector<unsigned int>::const_iterator iter = aCP.begin(); iter != aCP.end(); ++iter)
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + offset ), (int)(*iter) );
					offset += sizeof(unsigned int);
				}

				if (bytes)
				{
					for (std::vector<FTXBXS>::const_iterator iter = oFTXBXS.begin(); iter != oFTXBXS.end(); ++iter)
					{
						memcpy ((bytes + offset), (BYTE*)(*iter), iter->Size());
						offset += iter->Size();
					}
				}
			}
		}

		PlcftxbxTxt(const PlcftxbxTxt& oBxTxt) : bytes(NULL), sizeInBytes(oBxTxt.sizeInBytes)
		{
			bytes	=	new BYTE[sizeInBytes];

			if (bytes)
			{
				memset (bytes, 0, sizeInBytes);
				memcpy (bytes, oBxTxt.bytes, sizeInBytes);
			}
		}

		inline bool operator == (const PlcftxbxTxt& oBxTxt)
		{
			return ((sizeInBytes == oBxTxt.sizeInBytes) && (memcmp(bytes, oBxTxt.bytes, sizeInBytes ) == 0));
		}

		inline bool operator != (const PlcftxbxTxt& oBxTxt)
		{
			return !( this->operator == (oBxTxt) );
		}

		inline PlcftxbxTxt& operator = (const PlcftxbxTxt& oBxTxt)
		{
			if (*this != oBxTxt)
			{
				RELEASEARRAYOBJECTS(bytes);

				sizeInBytes	=	oBxTxt.sizeInBytes;
				bytes		=	new BYTE[sizeInBytes];

				if (bytes)
				{
					memcpy(bytes, oBxTxt.bytes, sizeInBytes);
				}  
			}

			return *this;
		}


		// IOperand

		virtual ~PlcftxbxTxt()
		{
			RELEASEARRAYOBJECTS(bytes);
		}

		virtual operator BYTE*() const
		{
			return bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeInBytes;
		}

	private:

		BYTE*			bytes;
		unsigned int	sizeInBytes;
	};

	class PlcfTxbxBkd : public IOperand
	{
	public:

		PlcfTxbxBkd(): bytes(NULL), sizeInBytes(0)
		{
			bytes = new BYTE [sizeInBytes];

			if (bytes)
				memset(bytes, 0, sizeInBytes);
		}

		PlcfTxbxBkd (const std::vector<unsigned int>& aCP, const std::vector<Tbkd>& oTbkd) : bytes(NULL), sizeInBytes(0)
		{
			sizeInBytes	=	( (aCP.size() * sizeof(unsigned int) ) + ( oTbkd.size() * Tbkd::SIZE_IN_BYTES ) );

			bytes		=	new BYTE[sizeInBytes];
			if (bytes)
			{
				memset (bytes, 0,sizeInBytes);

				unsigned int offset = 0;
				for (std::vector<unsigned int>::const_iterator iter = aCP.begin(); iter != aCP.end(); ++iter)
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + offset ), (int)(*iter) );
					offset += sizeof(unsigned int);
				}

				if (bytes)
				{
					for (std::vector<Tbkd>::const_iterator iter = oTbkd.begin(); iter != oTbkd.end(); ++iter)
					{
						memcpy ((bytes + offset), (BYTE*)(*iter), iter->Size());
						offset += iter->Size();
					}
				}
			}
		}

		PlcfTxbxBkd(const PlcfTxbxBkd& oTxbxBkd) : bytes(NULL), sizeInBytes(oTxbxBkd.sizeInBytes)
		{
			bytes	=	new BYTE[sizeInBytes];

			if (bytes)
			{
				memset (bytes, 0, sizeInBytes);
				memcpy (bytes, oTxbxBkd.bytes, sizeInBytes);
			}
		}

		inline bool operator == (const PlcfTxbxBkd& oTxbxBkd)
		{
			return ((sizeInBytes == oTxbxBkd.sizeInBytes) && (memcmp(bytes, oTxbxBkd.bytes, sizeInBytes ) == 0));
		}

		inline bool operator != (const PlcfTxbxBkd& oTxbxBkd)
		{
			return !( this->operator == (oTxbxBkd) );
		}

		inline PlcfTxbxBkd& operator = (const PlcfTxbxBkd& oTxbxBkd)
		{
			if (*this != oTxbxBkd)
			{
				RELEASEARRAYOBJECTS(bytes);

				sizeInBytes	=	oTxbxBkd.sizeInBytes;
				bytes		=	new BYTE[sizeInBytes];

				if (bytes)
				{
					memcpy(bytes, oTxbxBkd.bytes, sizeInBytes);
				}  
			}

			return *this;
		}


		// IOperand

		virtual ~PlcfTxbxBkd()
		{
			RELEASEARRAYOBJECTS(bytes);
		}

		virtual operator BYTE*() const
		{
			return bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeInBytes;
		}

	private:

		BYTE*			bytes;
		unsigned int	sizeInBytes;
	};


	class PlcfHdrtxbxTxt : public IOperand
	{
	public:

		PlcfHdrtxbxTxt(): bytes(NULL), sizeInBytes(0)
		{
			bytes = new BYTE [sizeInBytes];

			if (bytes)
				memset(bytes, 0, sizeInBytes);
		}

		PlcfHdrtxbxTxt(const std::vector<unsigned int>& aCP, const std::vector<FTXBXS>& oFTXBXS) : bytes(NULL), sizeInBytes(0)
		{
			sizeInBytes	=	( (aCP.size() * sizeof(unsigned int) ) + ( oFTXBXS.size() * FTXBXS::SIZE_IN_BYTES ) );

			bytes		=	new BYTE[sizeInBytes];
			if (bytes)
			{
				memset (bytes, 0,sizeInBytes);

				unsigned int offset = 0;
				for ( std::vector<unsigned int>::const_iterator iter = aCP.begin(); iter != aCP.end(); ++iter)
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + offset ), (int)(*iter) );
					offset += sizeof(unsigned int);
				}

				if (bytes)
				{
					for (std::vector<FTXBXS>::const_iterator iter = oFTXBXS.begin(); iter != oFTXBXS.end(); ++iter)
					{
						memcpy ((bytes + offset), (BYTE*)(*iter), iter->Size());
						offset += iter->Size();
					}
				}
			}
		}

		PlcfHdrtxbxTxt(const PlcfHdrtxbxTxt& oBxTxt) : bytes(NULL), sizeInBytes(oBxTxt.sizeInBytes)
		{
			bytes	=	new BYTE[sizeInBytes];

			if (bytes)
			{
				memset (bytes, 0, sizeInBytes);
				memcpy (bytes, oBxTxt.bytes, sizeInBytes);
			}
		}

		inline bool operator == (const PlcfHdrtxbxTxt& oBxTxt)
		{
			return ((sizeInBytes == oBxTxt.sizeInBytes) && (memcmp(bytes, oBxTxt.bytes, sizeInBytes ) == 0));
		}

		inline bool operator != (const PlcfHdrtxbxTxt& oBxTxt)
		{
			return !( this->operator == (oBxTxt) );
		}

		inline PlcfHdrtxbxTxt& operator = (const PlcfHdrtxbxTxt& oBxTxt)
		{
			if (*this != oBxTxt)
			{
				RELEASEARRAYOBJECTS(bytes);

				sizeInBytes	=	oBxTxt.sizeInBytes;
				bytes		=	new BYTE[sizeInBytes];

				if (bytes)
				{
					memcpy(bytes, oBxTxt.bytes, sizeInBytes);
				}  
			}

			return *this;
		}


		// IOperand

		virtual ~PlcfHdrtxbxTxt()
		{
			RELEASEARRAYOBJECTS(bytes);
		}

		virtual operator BYTE*() const
		{
			return bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeInBytes;
		}

	private:

		BYTE*			bytes;
		unsigned int	sizeInBytes;
	};

	class PlcfTxbxHdrBkd : public IOperand
	{
	public:

		PlcfTxbxHdrBkd(): bytes(NULL), sizeInBytes(0)
		{
			bytes = new BYTE[sizeInBytes];

			if (bytes)
				memset(bytes, 0, sizeInBytes);
		}

		PlcfTxbxHdrBkd (const std::vector<unsigned int>& aCP, const std::vector<Tbkd>& oTbkd) : bytes(NULL), sizeInBytes(0)
		{
			sizeInBytes	=	( (aCP.size() * sizeof(unsigned int) ) + ( oTbkd.size() * Tbkd::SIZE_IN_BYTES ) );

			bytes		=	new BYTE[sizeInBytes];
			if (bytes)
			{
				memset (bytes, 0,sizeInBytes);

				unsigned int offset = 0;
				for ( std::vector<unsigned int>::const_iterator iter = aCP.begin(); iter != aCP.end(); ++iter)
				{
					DocFileFormat::FormatUtils::SetBytes( ( bytes + offset ), (int)(*iter) );
					offset += sizeof(unsigned int);
				}

				if (bytes)
				{
					for (std::vector<Tbkd>::const_iterator iter = oTbkd.begin(); iter != oTbkd.end(); ++iter)
					{
						memcpy ((bytes + offset), (BYTE*)(*iter), iter->Size());
						offset += iter->Size();
					}
				}
			}
		}

		PlcfTxbxHdrBkd(const PlcfTxbxHdrBkd& oHdrBkd) : bytes(NULL), sizeInBytes(oHdrBkd.sizeInBytes)
		{
			bytes	=	new BYTE[sizeInBytes];

			if (bytes)
			{
				memset (bytes, 0, sizeInBytes);
				memcpy (bytes, oHdrBkd.bytes, sizeInBytes);
			}
		}

		inline bool operator == (const PlcfTxbxHdrBkd& oHdrBkd)
		{
			return ((sizeInBytes == oHdrBkd.sizeInBytes) && (memcmp(bytes, oHdrBkd.bytes, sizeInBytes ) == 0));
		}

		inline bool operator != (const PlcfTxbxHdrBkd& oHdrBkd)
		{
			return !( this->operator == (oHdrBkd) );
		}

		inline PlcfTxbxHdrBkd& operator = (const PlcfTxbxHdrBkd& oHdrBkd)
		{
			if (*this != oHdrBkd)
			{
				RELEASEARRAYOBJECTS(bytes);

				sizeInBytes	=	oHdrBkd.sizeInBytes;
				bytes		=	new BYTE[sizeInBytes];

				if (bytes)
				{
					memcpy(bytes, oHdrBkd.bytes, sizeInBytes);
				}  
			}

			return *this;
		}


		// IOperand

		virtual ~PlcfTxbxHdrBkd()
		{
			RELEASEARRAYOBJECTS(bytes);
		}

		virtual operator BYTE*() const
		{
			return bytes;
		}

		virtual operator const BYTE*() const
		{
			return (const BYTE*)bytes;
		}

		virtual unsigned int Size() const
		{
			return sizeInBytes;
		}

	private:

		BYTE*			bytes;
		unsigned int	sizeInBytes;
	};

	//
	class CTextBoxRef
	{
	public:

		CTextBoxRef(int nIndex) : m_nIndex(nIndex), m_nID (-1)
		{

		}

		~CTextBoxRef()
		{

		}

		inline void SetID (int nID)
		{
			m_nID	=	nID;
		}
		inline int GetID ()
		{
			return m_nID;
		}
		inline int GetIndex()
		{
			return m_nIndex;
		}

		inline int IsValid()
		{
			return (m_nIndex >= 0);
		}

		inline void AppendTbItems (std::vector<Docx2Doc::TextItem>& oTextItems)
		{
			m_oTextItems	=	oTextItems;
			
			// TODO : временно
			if (1 == oTextItems.size())
			{
				std::wstring strSrc = oTextItems[0]->GetAllText();
				if ((1 == strSrc.length()) && (TextMark::ParagraphEnd == strSrc[0]))
					m_oTextItems.push_back(oTextItems[0]);
			}
		}

		inline const std::vector<TextItem>& GetText ()
		{
			return m_oTextItems;
		}

	private:

		int m_nIndex;
		int m_nID;				//

		std::vector<TextItem>	m_oTextItems;
	};

	//
	class TextBox : public ITextItem
	{
		struct TextBoxItemWithOffset
		{
			TextItemPtr textBoxItem;
			unsigned int textBoxItemOffset;

			TextBoxItemWithOffset() : textBoxItem(), textBoxItemOffset(0)
			{

			}

			TextBoxItemWithOffset(const TextItemPtr& oTextBoxItem, unsigned int nTextBoxItemOffset) : textBoxItem(oTextBoxItem), textBoxItemOffset(nTextBoxItemOffset)
			{

			}
		};

	public:

		TextBox (short aFtnIdx = 0);
		TextBox (const TextBox& oTextBox);
		void AddTextItem(const ITextItem& oTextItem);
		short GetIndex() const;
		virtual ~TextBox();
		virtual std::wstring GetAllText() const;
		virtual operator std::wstring() const;
		virtual std::vector<TextItemPtr> GetAllParagraphsCopy() const;
		virtual std::vector<ITextItem*> GetAllParagraphs();
		virtual std::vector<PapxInFkp> GetAllParagraphsProperties(std::vector<unsigned int>* allParagraphsOffsets) const;
		virtual std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets) const;
		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy(std::vector<unsigned int>* allRunsOffsets) const;
		virtual std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy(std::vector<unsigned int>* allParagraphItemsOffsets) const;
		virtual IVirtualConstructor* New() const;
		virtual IVirtualConstructor* Clone() const;

	private:

		std::list<TextBoxItemWithOffset> textItems;
		unsigned int textBoxItemsOffset;
		short aFtnIdx;
	};
}
