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

#include "presentationnodetype.h"

#include <boost/algorithm/string.hpp>
#include <ostream>

namespace cpdoccore { namespace odf_types {

	std::wostream& operator << (std::wostream& _Wostream, const presentation_node_type& _Val)
	{
		switch (_Val.get_type())
		{
		case presentation_node_type::default				: _Wostream << L"default"; break;
		case presentation_node_type::after_previous			: _Wostream << L"after-previous"; break;
		case presentation_node_type::interactive_sequence	: _Wostream << L"interactive-sequence"; break;
		case presentation_node_type::main_sequence			: _Wostream << L"main-sequence"; break;
		case presentation_node_type::on_click				: _Wostream << L"on-click"; break;
		case presentation_node_type::timing_root			: _Wostream << L"timing-root"; break;
		case presentation_node_type::with_previous			: _Wostream << L"with-previous"; break;
		}
		return _Wostream;
	}

	presentation_node_type presentation_node_type::parse(const std::wstring& Str)
	{
			 if (Str == L"default")					return presentation_node_type(default);
		else if (Str == L"after-previous")			return presentation_node_type(after_previous);
		else if (Str == L"interactive-sequence")	return presentation_node_type(interactive_sequence);
		else if (Str == L"main-sequence")			return presentation_node_type(main_sequence);
		else if (Str == L"on-click")				return presentation_node_type(on_click);
		else if (Str == L"timing-root")				return presentation_node_type(timing_root);
		else if (Str == L"with-previous")			return presentation_node_type(with_previous);

		return presentation_node_type::none;
	}

} // namespace odf_types
} // namespace cpdoccore