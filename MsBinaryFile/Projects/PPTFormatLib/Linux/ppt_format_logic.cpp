﻿/*
 * (c) Copyright Ascensio System SIA 2010-2019
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
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
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

#include "../../../PptFile/Enums/RecordType.cpp"
#include "../../../PptFile/Enums/RecordType.cpp"
#include "../../../PptFile/Enums/RecordType.cpp"
#include "../../../PptFile/Reader/ReadStructures.cpp"
#include "../../../PptFile/Reader/RoundTripExtractor.cpp"
#include "../../../PptFile/Reader/PPTDocumentInfoOneUser.cpp"
#include "../../../PptFile/Reader/Records.cpp"
#include "../../../PptFile/Reader/PPTFileReader.cpp"
#include "../../../PptFile/Reader/SlidePersist.cpp"
#include "../../../PptFile/PPTXWriter/Converter.cpp"
#include "../../../PptFile/PPTXWriter/ShapeWriter.cpp"
#include "../../../PptFile/PPTXWriter/TableWriter.cpp"
#include "../../../PptFile/PPTXWriter/TxBodyConverter.cpp"
#include "../../../PptFile/Records/Drawing/ArtBlip.cpp"
#include "../../../PptFile/Records/Drawing/ShapeContainer.cpp"
#include "../../../PptFile/Records/Animations/TimeVariant.cpp"
#include "../../../PptFile/Records/BlipEntityAtom.cpp"
#include "../../../PptFile/Drawing/Elements.cpp"
#include "../../../PptFile/Drawing/TextAttributesEx.cpp"
#include "../../../PptFile/Converter/Animation/AnimationParser.cpp"
#include "../../../PptFile/Converter/Animation/Animation_1995.cpp"
#include "../../../PptFile/Converter/Animation/TimingUtils.cpp"
#include "../../../PptFile/Converter/Animation/Timing_1995.cpp"
#include "../../../PptFile/Converter/Animation/Timing_2010.cpp"
#include "../../../PptFile/Converter/Animation/hashcode10.cpp"
#include "../../../PptFile/Converter/Animation/intermediate_anim.cpp"
#include "../../../PptFile/Converter/timing.cpp"
#include "../../../PptFile/Converter/transition.cpp"
#include "../../../PptFile/PPTXWriter/BulletsConverter.cpp
