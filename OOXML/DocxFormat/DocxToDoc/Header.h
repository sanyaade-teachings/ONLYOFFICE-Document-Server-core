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

#include "Paragraph.h"

namespace Docx2Doc
{
	class Header: public ITextItem
	{
		struct HeaderItemWithOffset
		{
			TextItemPtr headerItem;
			unsigned int headerItemOffset;

			HeaderItemWithOffset():
			headerItem(), headerItemOffset(0)
			{
			}

			HeaderItemWithOffset( const TextItemPtr& _headerItem, unsigned int _headerItemOffset ):
			headerItem(_headerItem), headerItemOffset(_headerItemOffset)
			{
			}
		};

	private:
		std::list<HeaderItemWithOffset> textItems;
		unsigned int headerItemsOffset;

	public:
		explicit Header();
		Header( const Header& _header );
		void AddTextItem( const ITextItem& _textItem );
		virtual ~Header();
		virtual std::wstring GetAllText() const;
		virtual operator std::wstring() const;
		virtual std::vector<TextItemPtr> GetAllParagraphsCopy() const;
		virtual std::vector<ITextItem*> GetAllParagraphs();
		virtual std::vector<PapxInFkp> GetAllParagraphsProperties( std::vector<unsigned int>* allParagraphsOffsets ) const;
		virtual std::vector<Chpx> GetAllRunProperties( std::vector<unsigned int>* allRunsOffsets ) const;
		virtual std::vector<IParagraphItemPtr> GetAllRunsCopy( std::vector<unsigned int>* allRunsOffsets ) const;
		virtual std::vector<IParagraphItemPtr> GetAllParagraphItemsCopy( std::vector<unsigned int>* allParagraphItemsOffsets ) const;
		virtual IVirtualConstructor* New() const;
		virtual IVirtualConstructor* Clone() const;
	};
}
