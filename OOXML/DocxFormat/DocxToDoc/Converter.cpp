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

#include "Converter.h"

#include "../../../Common/OfficeFileErrorDescription.h"

#include "../../../OOXML/DocxFormat/Document.h"
#include "../../../OOXML/DocxFormat/Numbering.h"
#include "../../../OOXML/DocxFormat/Styles.h"
#include "../../../OOXML/DocxFormat/Footnote.h"
#include "../../../OOXML/DocxFormat/Endnote.h"
#include "../../../OOXML/DocxFormat/FtnEdn.h"
#include "../../../OOXML/DocxFormat/FontTable.h"
#include "../../../OOXML/DocxFormat/Logic/Table.h"
#include "../../../OOXML/DocxFormat/Logic/Sdt.h"
#include "../../../OOXML/DocxFormat/Logic/FldSimple.h"
#include "../../../OOXML/DocxFormat/Logic/Hyperlink.h"
#include "../../../OOXML/DocxFormat/Logic/ParagraphProperty.h"
#include "../../../OOXML/DocxFormat/Logic/SectionProperty.h"
#include "../../../OOXML/DocxFormat/Logic/Run.h"
#include "../../../OOXML/DocxFormat/Logic/FldChar.h"

#include "../../../MsBinaryFile/DocFile/Global.h"
#include "../../../MsBinaryFile/DocFile/StyleSheetDescription.h"
#include "../../../MsBinaryFile/DocFile/SectionPropertiesMapping.h"
#include "../../../MsBinaryFile/DocFile/TablePropertiesMapping.h"

namespace Docx2Doc
{
	Converter::Converter()
	{
		InitBasicEnums();
		InitLanguageCodes();
	}

	Converter::~Converter()
	{}

	_UINT32 Converter::SaveToFile(const std::wstring & sSrcPath, const std::wstring & sDstPath, const std::wstring & sXMLOptions)
	{
		bool result = false;

		m_Docx.Read(sSrcPath);

		if (m_Docx.m_oMain.document)
		{
			// Fonts
			if (m_Docx.m_oMain.fontTable)
			{
				std::vector<OOX::CFont*> arrFonts = m_Docx.m_oMain.fontTable->m_arrFonts;

				for (size_t i = 0; i < arrFonts.size(); i++)
				{
					m_fontTableMap.insert(std::pair<std::wstring, size_t>(arrFonts[i]->m_sName, i));
				}
			}

			// Numbering
			ConvertNumbering(m_Docx.m_oMain.numbering);

			// Styles
			ConvertStyleSheet(m_Docx.m_oMain.styles);

			// Document
			ConvertDocument(m_Docx.m_oMain.document);

			// FontTable
			ConvertFontTable(m_Docx.m_oMain.fontTable);

			// Write to doc
			bool WriteInformationBlock();
			bool WriteDocument();
			bool WriteFontTable();
			bool WriteStyleSheet();
			bool WriteNumbering();
		}

		return result ? 0 : AVS_FILEUTILS_ERROR_CONVERT;
	}

	// Init
	void Converter::InitBasicEnums()
	{
		for (size_t i = 0; i < (sizeof(DocFileFormat::StyleIdentifierMap) / sizeof(DocFileFormat::StyleIdentifierMap[0])); i++)
		{
			m_styleIdDefaultMap.insert(std::pair<std::wstring, size_t>(DocFileFormat::StyleIdentifierMap[i], i));
		}

		for (size_t i = 0; i < (sizeof(DocFileFormat::PageNumberFormatCodeMap) / sizeof(DocFileFormat::PageNumberFormatCodeMap[0])); i++)
		{
			m_numFormatMap.insert(std::pair<std::wstring, size_t>(DocFileFormat::PageNumberFormatCodeMap[i], i));
		}

		for (size_t i = 0; i < (sizeof(DocFileFormat::StyleKindMap) / sizeof(DocFileFormat::StyleKindMap[0])); i++)
		{
			m_styleTypeMap.insert(std::pair<std::wstring, size_t>(DocFileFormat::StyleKindMap[i], i));
		}

		for (size_t i = 0; i < (sizeof(Global::UnderlineCode) / sizeof(Global::UnderlineCode[0])); i++)
		{
			m_kulMap.insert(std::pair<std::wstring, size_t>(Global::UnderlineCode[i], i));
		}

		for (size_t i = 0; i < (sizeof(DocFileFormat::SectionTypeMap) / sizeof(DocFileFormat::SectionTypeMap[0])); i++)
		{
			m_sectionTypeMap.insert(std::pair<std::wstring, size_t>(DocFileFormat::SectionTypeMap[i], i));
		}

		for (size_t i = 0; i < (sizeof(Global::VerticalPositionCode) / sizeof(Global::VerticalPositionCode[0])); i++)
		{
			m_verticalPositionMap.insert(std::pair<std::wstring, size_t>(Global::VerticalPositionCode[i], i));
		}

		for (size_t i = 0; i < (sizeof(Global::HorizontalPositionCode) / sizeof(Global::HorizontalPositionCode[0])); i++)
		{
			m_horizontalPositionMap.insert(std::pair<std::wstring, size_t>(Global::HorizontalPositionCode[i], i));
		}

		for (size_t i = 0; i < (sizeof(Global::TextFrameWrapping) / sizeof(Global::TextFrameWrapping[0])); i++)
		{
			m_textFrameWrappingMap.insert(std::pair<std::wstring, size_t>(Global::TextFrameWrapping[i], i));
		}

		for (size_t i = 0; i < (sizeof(DocFileFormat::WidthType) / sizeof(DocFileFormat::WidthType[0])); i++)
		{
			m_tableWidthMap.insert(std::pair<std::wstring, size_t>(DocFileFormat::WidthType[i], i));
		}

		for (size_t i = 0; i < (sizeof(Global::TabStop) / sizeof(Global::TabStop[0])); i++)
		{
			m_tabStopMap.insert(std::pair<std::wstring, size_t>(Global::TabStop[i], i));
		}

		for (size_t i = 0; i < (sizeof(Global::TabLeader) / sizeof(Global::TabLeader[0])); i++)
		{
			m_tabLeaderMap.insert(std::pair<std::wstring, size_t>(Global::TabLeader[i], i));
		}
	}

	void Converter::InitLanguageCodes()
	{
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"af-ZA", DocFileFormat::LanguageCode( DocFileFormat::Afrikaans)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sq-AL", DocFileFormat::LanguageCode( DocFileFormat::Albanian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"am-ET", DocFileFormat::LanguageCode( DocFileFormat::Amharic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-DZ", DocFileFormat::LanguageCode( DocFileFormat::ArabicAlgeria)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-BH", DocFileFormat::LanguageCode( DocFileFormat::ArabicBahrain)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-EG", DocFileFormat::LanguageCode( DocFileFormat::ArabicEgypt)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-IQ", DocFileFormat::LanguageCode( DocFileFormat::ArabicIraq)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-JO", DocFileFormat::LanguageCode( DocFileFormat::ArabicJordan)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-KW", DocFileFormat::LanguageCode( DocFileFormat::ArabicKuwait)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-LB", DocFileFormat::LanguageCode( DocFileFormat::ArabicLebanon)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-LY", DocFileFormat::LanguageCode( DocFileFormat::ArabicLibya)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-MA", DocFileFormat::LanguageCode( DocFileFormat::ArabicMorocco)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-OM", DocFileFormat::LanguageCode( DocFileFormat::ArabicOman)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-QA", DocFileFormat::LanguageCode( DocFileFormat::ArabicQatar)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-SA", DocFileFormat::LanguageCode( DocFileFormat::ArabicSaudiArabia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-SY", DocFileFormat::LanguageCode( DocFileFormat::ArabicSyria)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-TN", DocFileFormat::LanguageCode( DocFileFormat::ArabicTunisia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-AE", DocFileFormat::LanguageCode( DocFileFormat::ArabicUAE)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ar-YE", DocFileFormat::LanguageCode( DocFileFormat::ArabicYemen)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"hy-AM", DocFileFormat::LanguageCode( DocFileFormat::Armenian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"as-IN", DocFileFormat::LanguageCode( DocFileFormat::Assamese)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"az-AZ-cyrl", DocFileFormat::LanguageCode( DocFileFormat::AzeriCyrillic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"az-AZ-latn", DocFileFormat::LanguageCode( DocFileFormat::AzeriLatin)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"eu-ES", DocFileFormat::LanguageCode( DocFileFormat::Basque)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"be-BY", DocFileFormat::LanguageCode( DocFileFormat::Belarusian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"bn-IN", DocFileFormat::LanguageCode( DocFileFormat::Bengali)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"bn-BD", DocFileFormat::LanguageCode( DocFileFormat::BengaliBangladesh)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"bg-BG", DocFileFormat::LanguageCode( DocFileFormat::Bulgarian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"my-MM", DocFileFormat::LanguageCode( DocFileFormat::Burmese)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ca-ES", DocFileFormat::LanguageCode( DocFileFormat::Catalan)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"zh-HK", DocFileFormat::LanguageCode( DocFileFormat::ChineseHongKong)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"zh-MO", DocFileFormat::LanguageCode( DocFileFormat::ChineseMacao)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"zh-CN", DocFileFormat::LanguageCode( DocFileFormat::ChinesePRC)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"zh-SG", DocFileFormat::LanguageCode( DocFileFormat::ChineseSingapore)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"zh-TW", DocFileFormat::LanguageCode( DocFileFormat::ChineseTaiwan)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"hr-HR", DocFileFormat::LanguageCode( DocFileFormat::Croatian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"cs-CZ", DocFileFormat::LanguageCode( DocFileFormat::Czech)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"da-DK", DocFileFormat::LanguageCode( DocFileFormat::Danish)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"dv-MV", DocFileFormat::LanguageCode( DocFileFormat::Divehi)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"nl-BE", DocFileFormat::LanguageCode( DocFileFormat::DutchBelgium)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"nl-NL", DocFileFormat::LanguageCode( DocFileFormat::DutchNetherlands)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-AU", DocFileFormat::LanguageCode( DocFileFormat::EnglishAustralia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-BZ", DocFileFormat::LanguageCode( DocFileFormat::EnglishBelize)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-CA", DocFileFormat::LanguageCode( DocFileFormat::EnglishCanada)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-DO", DocFileFormat::LanguageCode( DocFileFormat::EnglishCaribbean)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-HK", DocFileFormat::LanguageCode( DocFileFormat::EnglishHongKong)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-IN", DocFileFormat::LanguageCode( DocFileFormat::EnglishIndia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-ID", DocFileFormat::LanguageCode( DocFileFormat::EnglishIndonesia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-IE", DocFileFormat::LanguageCode( DocFileFormat::EnglishIreland)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-JM", DocFileFormat::LanguageCode( DocFileFormat::EnglishJamaica)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-MY", DocFileFormat::LanguageCode( DocFileFormat::EnglishMalaysia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-NZ", DocFileFormat::LanguageCode( DocFileFormat::EnglishNewZealand)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-PH", DocFileFormat::LanguageCode( DocFileFormat::EnglishPhilippines)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-SG", DocFileFormat::LanguageCode( DocFileFormat::EnglishSingapore)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-ZA", DocFileFormat::LanguageCode( DocFileFormat::EnglishSouthAfrica)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-TT", DocFileFormat::LanguageCode( DocFileFormat::EnglishTrinidadAndTobago)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-UK", DocFileFormat::LanguageCode( DocFileFormat::EnglishUK)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-US", DocFileFormat::LanguageCode( DocFileFormat::EnglishUS)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"en-ZW", DocFileFormat::LanguageCode( DocFileFormat::EnglishZimbabwe)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"et-EE", DocFileFormat::LanguageCode( DocFileFormat::Estonian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fo-FO", DocFileFormat::LanguageCode( DocFileFormat::Faeroese)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fi-FI", DocFileFormat::LanguageCode( DocFileFormat::Finnish)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-BE", DocFileFormat::LanguageCode( DocFileFormat::FrenchBelgium)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-CM", DocFileFormat::LanguageCode( DocFileFormat::FrenchCameroon)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-CA", DocFileFormat::LanguageCode( DocFileFormat::FrenchCanada)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-CD", DocFileFormat::LanguageCode( DocFileFormat::FrenchCongoDRC)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-CI", DocFileFormat::LanguageCode( DocFileFormat::FrenchCotedIvoire)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-FR", DocFileFormat::LanguageCode( DocFileFormat::FrenchFrance)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-HT", DocFileFormat::LanguageCode( DocFileFormat::FrenchHaiti)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-LU", DocFileFormat::LanguageCode( DocFileFormat::FrenchLuxembourg)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-ML", DocFileFormat::LanguageCode( DocFileFormat::FrenchMali)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-MC", DocFileFormat::LanguageCode( DocFileFormat::FrenchMonaco)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-MA", DocFileFormat::LanguageCode( DocFileFormat::FrenchMorocco)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-RE", DocFileFormat::LanguageCode( DocFileFormat::FrenchReunion)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-SN", DocFileFormat::LanguageCode( DocFileFormat::FrenchSenegal)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-CH", DocFileFormat::LanguageCode( DocFileFormat::FrenchSwitzerland)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fr-DO", DocFileFormat::LanguageCode( DocFileFormat::FrenchWestIndies)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"fy-NL", DocFileFormat::LanguageCode( DocFileFormat::FrisianNetherlands)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"mk-MK", DocFileFormat::LanguageCode( DocFileFormat::FYROMacedonian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ga-IE", DocFileFormat::LanguageCode( DocFileFormat::GaelicIreland)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"gd-UK", DocFileFormat::LanguageCode( DocFileFormat::GaelicScotland)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"gl-ES", DocFileFormat::LanguageCode( DocFileFormat::Galician)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ka-GE", DocFileFormat::LanguageCode( DocFileFormat::Georgian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"de-AT", DocFileFormat::LanguageCode( DocFileFormat::GermanAustria)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"de-DE", DocFileFormat::LanguageCode( DocFileFormat::GermanGermany)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"de-LI", DocFileFormat::LanguageCode( DocFileFormat::GermanLiechtenstein)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"de-LU", DocFileFormat::LanguageCode( DocFileFormat::GermanLuxembourg)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"de-CH", DocFileFormat::LanguageCode( DocFileFormat::GermanSwitzerland)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"el-GR", DocFileFormat::LanguageCode( DocFileFormat::Greek)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"gn-BR", DocFileFormat::LanguageCode( DocFileFormat::Guarani)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"gu-IN", DocFileFormat::LanguageCode( DocFileFormat::Gujarati)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ha-NG", DocFileFormat::LanguageCode( DocFileFormat::Hausa)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"he-IL", DocFileFormat::LanguageCode( DocFileFormat::Hebrew)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"hi-IN", DocFileFormat::LanguageCode( DocFileFormat::Hindi)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"hu-HU", DocFileFormat::LanguageCode( DocFileFormat::Hungarian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"is-IS", DocFileFormat::LanguageCode( DocFileFormat::Icelandic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"id-ID", DocFileFormat::LanguageCode( DocFileFormat::Indonesian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"iu-CA", DocFileFormat::LanguageCode( DocFileFormat::Inuktitut)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"it-IT", DocFileFormat::LanguageCode( DocFileFormat::ItalianItaly)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"it-CH", DocFileFormat::LanguageCode( DocFileFormat::ItalianSwitzerland)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ja-JP", DocFileFormat::LanguageCode( DocFileFormat::Japanese)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"kn-ID", DocFileFormat::LanguageCode( DocFileFormat::Kannada)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ks-ID", DocFileFormat::LanguageCode( DocFileFormat::Kashmiri)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ks-PK", DocFileFormat::LanguageCode( DocFileFormat::KashmiriArabic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"kk-KZ", DocFileFormat::LanguageCode( DocFileFormat::Kazakh)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ko-KR", DocFileFormat::LanguageCode( DocFileFormat::Korean)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ky-KG", DocFileFormat::LanguageCode( DocFileFormat::Kyrgyz)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"lo-LA", DocFileFormat::LanguageCode( DocFileFormat::Lao)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"la", DocFileFormat::LanguageCode( DocFileFormat::Latin)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"lv-LV", DocFileFormat::LanguageCode( DocFileFormat::Latvian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"lt-LT", DocFileFormat::LanguageCode( DocFileFormat::Lithuanian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ms-MY", DocFileFormat::LanguageCode( DocFileFormat::Malay)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ms-BN", DocFileFormat::LanguageCode( DocFileFormat::MalayBruneiDarussalam)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ml-ID", DocFileFormat::LanguageCode( DocFileFormat::Malayalam)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"mt-MT", DocFileFormat::LanguageCode( DocFileFormat::Maltese)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"mi-NZ", DocFileFormat::LanguageCode( DocFileFormat::Maori)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"mr-ID", DocFileFormat::LanguageCode( DocFileFormat::Marathi)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"mn-MN", DocFileFormat::LanguageCode( DocFileFormat::Mongolian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ne-NP", DocFileFormat::LanguageCode( DocFileFormat::Nepali)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ne-ID", DocFileFormat::LanguageCode( DocFileFormat::NepaliIndia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"nb-NO", DocFileFormat::LanguageCode( DocFileFormat::NorwegianBokmal)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"nn-NO", DocFileFormat::LanguageCode( DocFileFormat::NorwegianNynorsk)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"or-ID", DocFileFormat::LanguageCode( DocFileFormat::Oriya)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ps-PK", DocFileFormat::LanguageCode( DocFileFormat::Pashto)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"pl-PL", DocFileFormat::LanguageCode( DocFileFormat::Polish)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"pt-BR", DocFileFormat::LanguageCode( DocFileFormat::PortugueseBrazil)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"pt-PT", DocFileFormat::LanguageCode( DocFileFormat::PortuguesePortugal)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"pa-ID", DocFileFormat::LanguageCode( DocFileFormat::Punjabi)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"pa-PK", DocFileFormat::LanguageCode( DocFileFormat::PunjabiPakistan)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"qu-BO", DocFileFormat::LanguageCode( DocFileFormat::QuechuaBolivia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"qu-EC", DocFileFormat::LanguageCode( DocFileFormat::QuechuaEcuador)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"qu-PE", DocFileFormat::LanguageCode( DocFileFormat::QuechuaPeru)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"rm-CH", DocFileFormat::LanguageCode( DocFileFormat::RhaetoRomanic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ro-MD", DocFileFormat::LanguageCode( DocFileFormat::RomanianMoldova)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ro-RO", DocFileFormat::LanguageCode( DocFileFormat::RomanianRomania)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ru-MD", DocFileFormat::LanguageCode( DocFileFormat::RussianMoldova)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ru-RU", DocFileFormat::LanguageCode( DocFileFormat::RussianRussia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"se-FI", DocFileFormat::LanguageCode( DocFileFormat::SamiLappish)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sa-ID", DocFileFormat::LanguageCode( DocFileFormat::Sanskrit)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sr-YU-cyrl", DocFileFormat::LanguageCode( DocFileFormat::SerbianCyrillic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sr-YU-latn", DocFileFormat::LanguageCode( DocFileFormat::SerbianLatin)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sd-PK", DocFileFormat::LanguageCode( DocFileFormat::SindhiArabic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sd-ID", DocFileFormat::LanguageCode( DocFileFormat::SindhiDevanagari)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"si-ID", DocFileFormat::LanguageCode( DocFileFormat::Sinhalese)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sk-SK", DocFileFormat::LanguageCode( DocFileFormat::Slovak)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sl-SI", DocFileFormat::LanguageCode( DocFileFormat::Slovenian)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"so-SO", DocFileFormat::LanguageCode( DocFileFormat::Somali)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-AR", DocFileFormat::LanguageCode( DocFileFormat::SpanishArgentina)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-BO", DocFileFormat::LanguageCode( DocFileFormat::SpanishBolivia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-CL", DocFileFormat::LanguageCode( DocFileFormat::SpanishChile)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-CO", DocFileFormat::LanguageCode( DocFileFormat::SpanishColombia)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-CR", DocFileFormat::LanguageCode( DocFileFormat::SpanishCostaRica)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-DO", DocFileFormat::LanguageCode( DocFileFormat::SpanishDominicanRepublic)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-EC", DocFileFormat::LanguageCode( DocFileFormat::SpanishEcuador)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-SV", DocFileFormat::LanguageCode( DocFileFormat::SpanishElSalvador)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-GT", DocFileFormat::LanguageCode( DocFileFormat::SpanishGuatemala)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-HN", DocFileFormat::LanguageCode( DocFileFormat::SpanishHonduras)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-MX", DocFileFormat::LanguageCode( DocFileFormat::SpanishMexico)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-NI", DocFileFormat::LanguageCode( DocFileFormat::SpanishNicaragua)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-PA", DocFileFormat::LanguageCode( DocFileFormat::SpanishPanama)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-PY", DocFileFormat::LanguageCode( DocFileFormat::SpanishParaguay)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-PE", DocFileFormat::LanguageCode( DocFileFormat::SpanishPeru)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-PR", DocFileFormat::LanguageCode( DocFileFormat::SpanishPuertoRico)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-ES", DocFileFormat::LanguageCode( DocFileFormat::SpanishSpainTraditionalSort)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-UY", DocFileFormat::LanguageCode( DocFileFormat::SpanishUruguay)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"es-VE", DocFileFormat::LanguageCode( DocFileFormat::SpanishVenezuela)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sw-TZ", DocFileFormat::LanguageCode( DocFileFormat::Swahili)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sv-FI", DocFileFormat::LanguageCode( DocFileFormat::SwedishFinland)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"sv-SE", DocFileFormat::LanguageCode( DocFileFormat::SwedishSweden)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"tg-TJ", DocFileFormat::LanguageCode( DocFileFormat::Tajik)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"ta-ID", DocFileFormat::LanguageCode( DocFileFormat::Tamil)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"tt-RU", DocFileFormat::LanguageCode( DocFileFormat::Tatar)));
		m_languageCodeMap.insert(std::pair<std::wstring, DocFileFormat::LanguageCode>(L"te-ID", DocFileFormat::LanguageCode( DocFileFormat::Telugu)));
	}

	// Converting
	void Converter::ConvertNumbering(OOX::CNumbering* pNumbering)
	{
		if (pNumbering)
		{
			if (!pNumbering->m_arrNum.size() || !pNumbering->m_arrAbstractNum.size())
				return;
		}
	}

	void Converter::ConvertDocument(OOX::CDocument* pDocument)
	{
		if (pDocument)
		{
			// Convert items
			for (size_t i = 0; i < pDocument->m_arrItems.size(); i++)
			{
				// Paragraph
				if (pDocument->m_arrItems[i]->getType() == OOX::EElementType::et_w_p)
				{
					XmlUtils::CXmlNode oNode;
					oNode.FromXmlString(pDocument->m_arrItems[i]->toXML());

					OOX::Logic::CParagraph oParagraph;
					oParagraph.fromXML(oNode);

					std::wstring sId = GetStyleID(oParagraph);
				}
				// Table
				if (pDocument->m_arrItems[i]->getType() == OOX::EElementType::et_w_tbl)
				{
					int x = 1;
				}
				// Std
				if (pDocument->m_arrItems[i]->getType() == OOX::EElementType::et_w_sdt)
				{
					int x = 1;
				}
			}
		}
	}

	void Converter::ConvertStyleSheet(OOX::CStyles* pStyles)
	{
		if (pStyles)
		{
			std::vector<OOX::CStyle*> arrStyles = pStyles->m_arrStyle;
			for (size_t i = 0; i < arrStyles.size(); i++)
			{
				std::wstring sId = arrStyles[i]->m_sStyleId.get();
				int x = 1;
			}
		}
	}

	void Converter::ConvertFontTable(OOX::CFontTable* pFontTable)
	{
		if (pFontTable)
		{
			for (size_t i = 0; i < pFontTable->m_arrFonts.size(); i++)
			{
				//DocFileFormat::
			}
		}
	}

	std::wstring Converter::GetStyleID(const OOX::Logic::CParagraph& oParagraph)
	{
		std::wstring sId;

		if (oParagraph.m_oParagraphProperty->IsNoEmpty() && oParagraph.m_oParagraphProperty->m_oPStyle.IsInit())
		{
			sId = oParagraph.m_oParagraphProperty->m_oPStyle->ToString();
		}
		else
		{
			// set default, Normal
		}

		return sId;
	}

	// Write to doc
	bool Converter::WriteInformationBlock()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteDocument()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteNumbering()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteStyleSheet()
	{
		bool bResult = false;
		return bResult;
	}

	bool Converter::WriteFontTable()
	{
		bool bResult = false;
		return bResult;
	}
}
