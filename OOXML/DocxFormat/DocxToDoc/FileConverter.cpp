
//#include <AtlConv.h>

#include "ParagraphItem.h"
#include "DocxToDocUtils.h"
//#include "ShapeBuilder.h"
#include "PropertyReader.h"

#include "FileConverter.h"

#define AVS_ERROR_UNEXPECTED -1

using namespace Docx2Doc;

namespace DOCXTODOC
{
	CFileTransformer::CFileTransformer ()
	{
		m_pDOCFile				=	NULL;

		m_bHaveSeparateFldChar	=	false;
		m_bIsInlineShape		=	FALSE;

		m_bIsHaveRunPr			=	FALSE;

		m_pDOCFile				=	new Docx2Doc::CDocFile();

		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "af-ZA" ), Docx2Doc::LID( DocFileFormat::Afrikaans ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sq-AL" ), Docx2Doc::LID( DocFileFormat::Albanian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "am-ET" ), Docx2Doc::LID( DocFileFormat::Amharic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-DZ" ), Docx2Doc::LID( DocFileFormat::ArabicAlgeria ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-BH" ), Docx2Doc::LID( DocFileFormat::ArabicBahrain ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-EG" ), Docx2Doc::LID( DocFileFormat::ArabicEgypt ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-IQ" ), Docx2Doc::LID( DocFileFormat::ArabicIraq ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-JO" ), Docx2Doc::LID( DocFileFormat::ArabicJordan ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-KW" ), Docx2Doc::LID( DocFileFormat::ArabicKuwait ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-LB" ), Docx2Doc::LID( DocFileFormat::ArabicLebanon ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-LY" ), Docx2Doc::LID( DocFileFormat::ArabicLibya ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-MA" ), Docx2Doc::LID( DocFileFormat::ArabicMorocco ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-OM" ), Docx2Doc::LID( DocFileFormat::ArabicOman ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-QA" ), Docx2Doc::LID( DocFileFormat::ArabicQatar ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-SA" ), Docx2Doc::LID( DocFileFormat::ArabicSaudiArabia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-SY" ), Docx2Doc::LID( DocFileFormat::ArabicSyria ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-TN" ), Docx2Doc::LID( DocFileFormat::ArabicTunisia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-AE" ), Docx2Doc::LID( DocFileFormat::ArabicUAE ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ar-YE" ), Docx2Doc::LID( DocFileFormat::ArabicYemen ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "hy-AM" ), Docx2Doc::LID( DocFileFormat::Armenian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "as-IN" ), Docx2Doc::LID( DocFileFormat::Assamese ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "az-AZ-cyrl" ), Docx2Doc::LID( DocFileFormat::AzeriCyrillic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "az-AZ-latn" ), Docx2Doc::LID( DocFileFormat::AzeriLatin ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "eu-ES" ), Docx2Doc::LID( DocFileFormat::Basque ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "be-BY" ), Docx2Doc::LID( DocFileFormat::Belarusian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "bn-IN" ), Docx2Doc::LID( DocFileFormat::Bengali ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "bn-BD" ), Docx2Doc::LID( DocFileFormat::BengaliBangladesh ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "bg-BG" ), Docx2Doc::LID( DocFileFormat::Bulgarian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "my-MM" ), Docx2Doc::LID( DocFileFormat::Burmese ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ca-ES" ), Docx2Doc::LID( DocFileFormat::Catalan ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "zh-HK" ), Docx2Doc::LID( DocFileFormat::ChineseHongKong ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "zh-MO" ), Docx2Doc::LID( DocFileFormat::ChineseMacao ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "zh-CN" ), Docx2Doc::LID( DocFileFormat::ChinesePRC ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "zh-SG" ), Docx2Doc::LID( DocFileFormat::ChineseSingapore ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "zh-TW" ), Docx2Doc::LID( DocFileFormat::ChineseTaiwan ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "hr-HR" ), Docx2Doc::LID( DocFileFormat::Croatian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "cs-CZ" ), Docx2Doc::LID( DocFileFormat::Czech ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "da-DK" ), Docx2Doc::LID( DocFileFormat::Danish ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "dv-MV" ), Docx2Doc::LID( DocFileFormat::Divehi ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "nl-BE" ), Docx2Doc::LID( DocFileFormat::DutchBelgium ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "nl-NL" ), Docx2Doc::LID( DocFileFormat::DutchNetherlands ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-AU" ), Docx2Doc::LID( DocFileFormat::EnglishAustralia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-BZ" ), Docx2Doc::LID( DocFileFormat::EnglishBelize ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-CA" ), Docx2Doc::LID( DocFileFormat::EnglishCanada ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-DO" ), Docx2Doc::LID( DocFileFormat::EnglishCaribbean ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-HK" ), Docx2Doc::LID( DocFileFormat::EnglishHongKong ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-IN" ), Docx2Doc::LID( DocFileFormat::EnglishIndia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-ID" ), Docx2Doc::LID( DocFileFormat::EnglishIndonesia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-IE" ), Docx2Doc::LID( DocFileFormat::EnglishIreland ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-JM" ), Docx2Doc::LID( DocFileFormat::EnglishJamaica ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-MY" ), Docx2Doc::LID( DocFileFormat::EnglishMalaysia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-NZ" ), Docx2Doc::LID( DocFileFormat::EnglishNewZealand ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-PH" ), Docx2Doc::LID( DocFileFormat::EnglishPhilippines ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-SG" ), Docx2Doc::LID( DocFileFormat::EnglishSingapore ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-ZA" ), Docx2Doc::LID( DocFileFormat::EnglishSouthAfrica ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-TT" ), Docx2Doc::LID( DocFileFormat::EnglishTrinidadAndTobago ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-UK" ), Docx2Doc::LID( DocFileFormat::EnglishUK ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-US" ), Docx2Doc::LID( DocFileFormat::EnglishUS ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "en-ZW" ), Docx2Doc::LID( DocFileFormat::EnglishZimbabwe ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "et-EE" ), Docx2Doc::LID( DocFileFormat::Estonian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fo-FO" ), Docx2Doc::LID( DocFileFormat::Faeroese ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fi-FI" ), Docx2Doc::LID( DocFileFormat::Finnish ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-BE" ), Docx2Doc::LID( DocFileFormat::FrenchBelgium ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-CM" ), Docx2Doc::LID( DocFileFormat::FrenchCameroon ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-CA" ), Docx2Doc::LID( DocFileFormat::FrenchCanada ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-CD" ), Docx2Doc::LID( DocFileFormat::FrenchCongoDRC ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-CI" ), Docx2Doc::LID( DocFileFormat::FrenchCotedIvoire ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-FR" ), Docx2Doc::LID( DocFileFormat::FrenchFrance ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-HT" ), Docx2Doc::LID( DocFileFormat::FrenchHaiti ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-LU" ), Docx2Doc::LID( DocFileFormat::FrenchLuxembourg ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-ML" ), Docx2Doc::LID( DocFileFormat::FrenchMali ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-MC" ), Docx2Doc::LID( DocFileFormat::FrenchMonaco ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-MA" ), Docx2Doc::LID( DocFileFormat::FrenchMorocco ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-RE" ), Docx2Doc::LID( DocFileFormat::FrenchReunion ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-SN" ), Docx2Doc::LID( DocFileFormat::FrenchSenegal ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-CH" ), Docx2Doc::LID( DocFileFormat::FrenchSwitzerland ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fr-DO" ), Docx2Doc::LID( DocFileFormat::FrenchWestIndies ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "fy-NL" ), Docx2Doc::LID( DocFileFormat::FrisianNetherlands ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "mk-MK" ), Docx2Doc::LID( DocFileFormat::FYROMacedonian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ga-IE" ), Docx2Doc::LID( DocFileFormat::GaelicIreland ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "gd-UK" ), Docx2Doc::LID( DocFileFormat::GaelicScotland ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "gl-ES" ), Docx2Doc::LID( DocFileFormat::Galician ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ka-GE" ), Docx2Doc::LID( DocFileFormat::Georgian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "de-AT" ), Docx2Doc::LID( DocFileFormat::GermanAustria ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "de-DE" ), Docx2Doc::LID( DocFileFormat::GermanGermany ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "de-LI" ), Docx2Doc::LID( DocFileFormat::GermanLiechtenstein ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "de-LU" ), Docx2Doc::LID( DocFileFormat::GermanLuxembourg ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "de-CH" ), Docx2Doc::LID( DocFileFormat::GermanSwitzerland ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "el-GR" ), Docx2Doc::LID( DocFileFormat::Greek ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "gn-BR" ), Docx2Doc::LID( DocFileFormat::Guarani ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "gu-IN" ), Docx2Doc::LID( DocFileFormat::Gujarati ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ha-NG" ), Docx2Doc::LID( DocFileFormat::Hausa ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "he-IL" ), Docx2Doc::LID( DocFileFormat::Hebrew ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "hi-IN" ), Docx2Doc::LID( DocFileFormat::Hindi ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "hu-HU" ), Docx2Doc::LID( DocFileFormat::Hungarian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "is-IS" ), Docx2Doc::LID( DocFileFormat::Icelandic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "id-ID" ), Docx2Doc::LID( DocFileFormat::Indonesian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "iu-CA" ), Docx2Doc::LID( DocFileFormat::Inuktitut ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "it-IT" ), Docx2Doc::LID( DocFileFormat::ItalianItaly ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "it-CH" ), Docx2Doc::LID( DocFileFormat::ItalianSwitzerland ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ja-JP" ), Docx2Doc::LID( DocFileFormat::Japanese ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "kn-ID" ), Docx2Doc::LID( DocFileFormat::Kannada ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ks-ID" ), Docx2Doc::LID( DocFileFormat::Kashmiri ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ks-PK" ), Docx2Doc::LID( DocFileFormat::KashmiriArabic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "kk-KZ" ), Docx2Doc::LID( DocFileFormat::Kazakh ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ko-KR" ), Docx2Doc::LID( DocFileFormat::Korean ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ky-KG" ), Docx2Doc::LID( DocFileFormat::Kyrgyz ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "lo-LA" ), Docx2Doc::LID( DocFileFormat::Lao ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "la" ), Docx2Doc::LID( DocFileFormat::Latin ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "lv-LV" ), Docx2Doc::LID( DocFileFormat::Latvian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "lt-LT" ), Docx2Doc::LID( DocFileFormat::Lithuanian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ms-MY" ), Docx2Doc::LID( DocFileFormat::Malay ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ms-BN" ), Docx2Doc::LID( DocFileFormat::MalayBruneiDarussalam ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ml-ID" ), Docx2Doc::LID( DocFileFormat::Malayalam ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "mt-MT" ), Docx2Doc::LID( DocFileFormat::Maltese ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "mi-NZ" ), Docx2Doc::LID( DocFileFormat::Maori ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "mr-ID" ), Docx2Doc::LID( DocFileFormat::Marathi ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "mn-MN" ), Docx2Doc::LID( DocFileFormat::Mongolian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ne-NP" ), Docx2Doc::LID( DocFileFormat::Nepali ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ne-ID" ), Docx2Doc::LID( DocFileFormat::NepaliIndia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "nb-NO" ), Docx2Doc::LID( DocFileFormat::NorwegianBokmal ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "nn-NO" ), Docx2Doc::LID( DocFileFormat::NorwegianNynorsk ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "or-ID" ), Docx2Doc::LID( DocFileFormat::Oriya ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ps-PK" ), Docx2Doc::LID( DocFileFormat::Pashto ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "pl-PL" ), Docx2Doc::LID( DocFileFormat::Polish ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "pt-BR" ), Docx2Doc::LID( DocFileFormat::PortugueseBrazil ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "pt-PT" ), Docx2Doc::LID( DocFileFormat::PortuguesePortugal ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "pa-ID" ), Docx2Doc::LID( DocFileFormat::Punjabi ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "pa-PK" ), Docx2Doc::LID( DocFileFormat::PunjabiPakistan ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "qu-BO" ), Docx2Doc::LID( DocFileFormat::QuechuaBolivia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "qu-EC" ), Docx2Doc::LID( DocFileFormat::QuechuaEcuador ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "qu-PE" ), Docx2Doc::LID( DocFileFormat::QuechuaPeru ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "rm-CH" ), Docx2Doc::LID( DocFileFormat::RhaetoRomanic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ro-MD" ), Docx2Doc::LID( DocFileFormat::RomanianMoldova ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ro-RO" ), Docx2Doc::LID( DocFileFormat::RomanianRomania ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ru-MD" ), Docx2Doc::LID( DocFileFormat::RussianMoldova ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ru-RU" ), Docx2Doc::LID( DocFileFormat::RussianRussia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "se-FI" ), Docx2Doc::LID( DocFileFormat::SamiLappish ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sa-ID" ), Docx2Doc::LID( DocFileFormat::Sanskrit ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sr-YU-cyrl" ), Docx2Doc::LID( DocFileFormat::SerbianCyrillic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sr-YU-latn" ), Docx2Doc::LID( DocFileFormat::SerbianLatin ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sd-PK" ), Docx2Doc::LID( DocFileFormat::SindhiArabic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sd-ID" ), Docx2Doc::LID( DocFileFormat::SindhiDevanagari ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "si-ID" ), Docx2Doc::LID( DocFileFormat::Sinhalese ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sk-SK" ), Docx2Doc::LID( DocFileFormat::Slovak ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sl-SI" ), Docx2Doc::LID( DocFileFormat::Slovenian ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "so-SO" ), Docx2Doc::LID( DocFileFormat::Somali ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-AR" ), Docx2Doc::LID( DocFileFormat::SpanishArgentina ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-BO" ), Docx2Doc::LID( DocFileFormat::SpanishBolivia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-CL" ), Docx2Doc::LID( DocFileFormat::SpanishChile ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-CO" ), Docx2Doc::LID( DocFileFormat::SpanishColombia ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-CR" ), Docx2Doc::LID( DocFileFormat::SpanishCostaRica ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-DO" ), Docx2Doc::LID( DocFileFormat::SpanishDominicanRepublic ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-EC" ), Docx2Doc::LID( DocFileFormat::SpanishEcuador ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-SV" ), Docx2Doc::LID( DocFileFormat::SpanishElSalvador ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-GT" ), Docx2Doc::LID( DocFileFormat::SpanishGuatemala ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-HN" ), Docx2Doc::LID( DocFileFormat::SpanishHonduras ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-MX" ), Docx2Doc::LID( DocFileFormat::SpanishMexico ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-NI" ), Docx2Doc::LID( DocFileFormat::SpanishNicaragua ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-PA" ), Docx2Doc::LID( DocFileFormat::SpanishPanama ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-PY" ), Docx2Doc::LID( DocFileFormat::SpanishParaguay ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-PE" ), Docx2Doc::LID( DocFileFormat::SpanishPeru ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-PR" ), Docx2Doc::LID( DocFileFormat::SpanishPuertoRico ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-ES" ), Docx2Doc::LID( DocFileFormat::SpanishSpainTraditionalSort ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-UY" ), Docx2Doc::LID( DocFileFormat::SpanishUruguay ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "es-VE" ), Docx2Doc::LID( DocFileFormat::SpanishVenezuela ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sw-TZ" ), Docx2Doc::LID( DocFileFormat::Swahili ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sv-FI" ), Docx2Doc::LID( DocFileFormat::SwedishFinland ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "sv-SE" ), Docx2Doc::LID( DocFileFormat::SwedishSweden ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "tg-TJ" ), Docx2Doc::LID( DocFileFormat::Tajik ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "ta-ID" ), Docx2Doc::LID( DocFileFormat::Tamil ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "tt-RU" ), Docx2Doc::LID( DocFileFormat::Tatar ) ) );
		lidMap.insert( std::pair<std::string, Docx2Doc::LID>( std::string( "te-ID" ), Docx2Doc::LID( DocFileFormat::Telugu ) ) );

		for (unsigned short i = 0; i < ( sizeof(Docx2Doc::StyleIDs) / sizeof(Docx2Doc::StyleIDs[0]) ); i++ )
		{
			predefinedStyleIDMap.insert( std::pair<std::string, unsigned short>( Docx2Doc::StyleIDs[i], i ) );
		}

		styleTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::StyleType>( std::string( "paragraph" ), Docx2Doc::Constants::styleTypeParagraph ) );
		styleTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::StyleType>( std::string( "character" ), Docx2Doc::Constants::styleTypeCharacter ) );
		styleTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::StyleType>( std::string( "table" ), Docx2Doc::Constants::styleTypeTable ) );
		styleTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::StyleType>( std::string( "numbering" ), Docx2Doc::Constants::styleTypeNumbering ) );

		for ( unsigned short i = 0; i < ( sizeof(Docx2Doc::NumberFormatCodes) / sizeof(Docx2Doc::NumberFormatCodes[0]) ); i++ )
		{
			numFmtMap.insert( std::pair<std::string, Docx2Doc::Constants::MSONFC>( Docx2Doc::NumberFormatCodes[i], (Docx2Doc::Constants::MSONFC)i ) );
		}

		kulMap.insert( std::pair<std::string, BYTE>( std::string( "none" ), 0x00 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "single" ), 0x01 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "words" ), 0x02 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "double" ), 0x03 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dotted" ), 0x04 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "thick" ), 0x06 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dash" ), 0x07 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dotDash" ), 0x09 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dotDotDash" ), 0x0A ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "wave" ), 0x0B ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dottedHeavy" ), 0x14 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dashedHeavy" ), 0x17 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dashDotHeavy" ), 0x19 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dashDotDotHeavy" ), 0x1A ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "wavyHeavy" ), 0x1B ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dashLong" ), 0x27 ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "wavyDouble" ), 0x2B ) );
		kulMap.insert( std::pair<std::string, BYTE>( std::string( "dashLongHeavy" ), 0x37 ) );

		sectionBreakTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::SBkcOperand>( std::string( "continuous" ), Docx2Doc::Constants::bkcContinuous ) );
		sectionBreakTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::SBkcOperand>( std::string( "nextColumn" ), Docx2Doc::Constants::bkcNewColumn ) );
		sectionBreakTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::SBkcOperand>( std::string( "nextPage" ), Docx2Doc::Constants::bkcNewPage ) );
		sectionBreakTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::SBkcOperand>( std::string( "evenPage" ), Docx2Doc::Constants::bkcEvenPage ) );
		sectionBreakTypeMap.insert( std::pair<std::string, Docx2Doc::Constants::SBkcOperand>( std::string( "oddPage" ), Docx2Doc::Constants::bkcOddPage ) );

		verticalPositionCodeMap.insert( std::make_pair( "margin", 0x00 ) );
		verticalPositionCodeMap.insert( std::make_pair( "page", 0x01 ) );
		verticalPositionCodeMap.insert( std::make_pair( "text", 0x02 ) );
		verticalPositionCodeMap.insert( std::make_pair( "none", 0x03 ) );

		horizontalPositionCodeMap.insert( std::make_pair( "text", 0x00 ) );
		horizontalPositionCodeMap.insert( std::make_pair( "margin", 0x01 ) );
		horizontalPositionCodeMap.insert( std::make_pair( "page", 0x02 ) );
		horizontalPositionCodeMap.insert( std::make_pair( "none", 0x03 ) );

		textFrameWrappingMap.insert( std::make_pair( "auto", 0x00 ) );
		textFrameWrappingMap.insert( std::make_pair( "notBeside", 0x01 ) );
		textFrameWrappingMap.insert( std::make_pair( "around", 0x02 ) );
		textFrameWrappingMap.insert( std::make_pair( "none", 0x03 ) );
		textFrameWrappingMap.insert( std::make_pair( "tight", 0x04 ) );
		textFrameWrappingMap.insert( std::make_pair( "through", 0x05 ) );

		tableCellWidthMap.insert( std::make_pair( "nil", Docx2Doc::Constants::ftsNil ) );
		tableCellWidthMap.insert( std::make_pair( "auto", Docx2Doc::Constants::ftsAuto ) );
		tableCellWidthMap.insert( std::make_pair( "pct", Docx2Doc::Constants::ftsPercent ) );
		tableCellWidthMap.insert( std::make_pair( "dxa", Docx2Doc::Constants::ftsDxa ) );

		customTabStopAlignment.insert( std::make_pair( "left", Docx2Doc::Constants::jcLeft ) );
		customTabStopAlignment.insert( std::make_pair( "center", Docx2Doc::Constants::jcCenter ) );
		customTabStopAlignment.insert( std::make_pair( "right", Docx2Doc::Constants::jcRight ) );
		customTabStopAlignment.insert( std::make_pair( "decimal", Docx2Doc::Constants::jcDecimal ) );
		customTabStopAlignment.insert( std::make_pair( "bar", Docx2Doc::Constants::jcBar ) );
		customTabStopAlignment.insert( std::make_pair( "clear", (Docx2Doc::Constants::TabJC)0x05 ) );
		customTabStopAlignment.insert( std::make_pair( "num", Docx2Doc::Constants::jcList ) );

		customTabStopLeader.insert( std::make_pair( "none", Docx2Doc::Constants::tlcNone ) );
		customTabStopLeader.insert( std::make_pair( "dot", Docx2Doc::Constants::tlcDot ) );
		customTabStopLeader.insert( std::make_pair( "hyphen", Docx2Doc::Constants::tlcHyphen ) );
		customTabStopLeader.insert( std::make_pair( "underscore", Docx2Doc::Constants::tlcUnderscore ) );
		customTabStopLeader.insert( std::make_pair( "heavy", Docx2Doc::Constants::tlcHeavy ) );
		customTabStopLeader.insert( std::make_pair( "middleDot", Docx2Doc::Constants::tlcMiddleDot ) );
	}

	CFileTransformer::~CFileTransformer ()
	{
		Docx2Doc::BinaryStorageSingleton* pBin	=	Docx2Doc::BinaryStorageSingleton::Instance();
		if (pBin)
			pBin->FreeInstance();

		/*Docx2Doc::COArtStorage* pStorage = Docx2Doc::COArtStorage::Instance();
		if (pStorage)
			pStorage->FreeInstance();*/

		RELEASEOBJECT (m_pDOCFile);
	}
}

namespace DOCXTODOC
{
	long CFileTransformer::Convert (const WCHAR* ooxFolder, const WCHAR* docFile)
	{
		LONG hrStatus = AVS_ERROR_UNEXPECTED;

		if ( (NULL != ooxFolder) && (NULL != docFile) && m_pDOCFile )
		{
			try
			{
				inputFolder.Read(ooxFolder);

				SHORT index = 0;

				size_t count = (*inputFolder.find<OOX::Document>().find<OOX::CFontTable>().Fonts).size();
				std::vector<OOX::CFont>& items = (*inputFolder.find<OOX::Document>().find<OOX::CFontTable>().Fonts);

				for (size_t j = 0; j < count; ++j)	
				{
					m_mapFontTableMap.insert(std::pair<std::string, short>(items[j].Name, index++));
				}

				if (inputFolder.find<OOX::Document>().exist<OOX::CNumbering>())
					ConvertNumbering( inputFolder.find<OOX::Document>().find<OOX::CNumbering>() );

				ConvertStyleSheet (inputFolder.find<OOX::Document>().find<OOX::CStyles>());

				ConvertDocument (inputFolder.find<OOX::Document>());
				ConvertFontTable(inputFolder.find<OOX::Document>().find<OOX::CFontTable>());

				hrStatus = m_pDOCFile->SaveToFile (docFile);
			}
			catch (...)
			{
				hrStatus = AVS_ERROR_UNEXPECTED;
			}
		}

		return hrStatus;
	}
}

namespace DOCXTODOC
{
	void CFileTransformer::ConvertDocument (const OOX::Document& oXmlDoc)
	{
		ConvertContent (*oXmlDoc.Items);

		// TODO : если список в конце документа, то добавляется брэйк (бага)

		Docx2Doc::Paragraph paragraph;
		paragraph.AddParagraphItem (Docx2Doc::Run());
		m_pDOCFile->AddTextItem (paragraph);

		m_pDOCFile->AddSectionProperties (ConvertSectionProperties(oXmlDoc.SectorProperty));
	}

	void CFileTransformer::ConvertContent (const std::vector<OOX::Logic::TextItem>& oXmlItems)
	{
		//m_oOArtBuilder.SetLocation (MAIN_DOCUMENT);

		for (size_t i = 0; i < oXmlItems.size(); ++i)
		{
			const OOX::Logic::TextItem& oXmlItem = oXmlItems[i];

			if (oXmlItem.is<OOX::Logic::CParagraph>())
			{
				const OOX::Logic::CParagraph& docxParagraph	=	oXmlItem.as<OOX::Logic::CParagraph>();
				if (ValidParagraph(docxParagraph))
				{
					Docx2Doc::Paragraph docParagraph	=	ConvertParagraph<OOX::Document>(docxParagraph);

					m_pDOCFile->AddTextItem (docParagraph);

					if (docxParagraph.Property.is_init() && docxParagraph.Property->SectorProperty.is_init())
					{
						m_pDOCFile->AddTextItem (Docx2Doc::SectionBreak());
						m_pDOCFile->AddSectionProperties(ConvertSectionProperties( docxParagraph.Property->SectorProperty));
					}
				}
			}

			if (oXmlItem.is<OOX::Logic::CTbl>())
			{
				Docx2Doc::Table oDocTable = CreateTable<OOX::Document>(oXmlItem.as<OOX::Logic::CTbl>());
				m_pDOCFile->AddTextItem (oDocTable);
			}

			if (oXmlItem.is<OOX::Logic::CSdt>())
			{
				ConvertContent(*oXmlItem.as<OOX::Logic::CSdt>().Content->Items);
			}
		}  
	}

	template<class T> Docx2Doc::Paragraph CFileTransformer::ConvertParagraph (const OOX::Logic::CParagraph& oXmlParagraph)
	{
		PrlList styleRunPr;
		PrlList styleParPr;

		std::string style	=	GetStyleID (oXmlParagraph);

		Docx2Doc::Paragraph oParagraph;
		oParagraph.SetStyle (m_mapStyleSheetMap [style]);

		styleRunPr			=	GetRunPropertiesFromStyleHierarchy (style);
		styleParPr			=	GetParagraphPropertiesFromStyleHierarchy (style, &styleRunPr);

		// retrieve run properties
		m_bIsHaveRunPr			=	FALSE;

		PrlList defaultRunPr;
		if (oXmlParagraph.m_oParagraphProperty && oXmlParagraph.m_oParagraphProperty->m_oRPr.is_init())
		{
			defaultRunPr		=	ConvertRunProperties(*oXmlParagraph.m_oParagraphProperty->m_oRPr);

			CPrCopier copier(&styleRunPr, &defaultRunPr);
		}

		m_bHaveSeparateFldChar	=	false;

		int haveGoBack			=	FALSE;	//TODO : some content

		for (size_t i = 0; i < oXmlParagraph.Items->size(); ++i)
		{
			const OOX::Logic::CParagraphItem& oParagraphItem	= oXmlParagraph.Items->operator[](i);

			std::wstring strRunType;

			if (oParagraphItem.is<OOX::Logic::CRun>())
			{
				Docx2Doc::Run oAddRun = ConvertRun<T>(oParagraphItem.as<OOX::Logic::CRun>(), styleRunPr, strRunType);

				if (m_bIsInlineShape)
				{
					//Docx2Doc::Picture oPicture (std::wstring(L"c:\\man.png"), 0, 0, 1000, 1000);
					//oParagraph.AddParagraphItem(Docx2Doc::Run(oPicture));

					//oParagraph.AddParagraphItem(m_oInlineShape);
				}
				else
				{
					oParagraph.AddParagraphItem(oAddRun);
				}

				//Docx2Doc::Picture oPicture (std::wstring(L"c:\\man.png"), 0, 0, 5000, 5000);
				//oParagraph.AddParagraphItem(Docx2Doc::Run(oPicture));

				m_bIsInlineShape	=	FALSE;
			}
			else if (oParagraphItem.is<OOX::Logic::CHyperlink>())
			{
				oParagraph.AddParagraphItem (ConvertHyperlink<T>(oParagraphItem.as<OOX::Logic::CHyperlink>(), styleRunPr));
			}
			else if (oParagraphItem.is<OOX::Logic::CBookmarkStart>())
			{
				const OOX::Logic::CBookmarkStart& oBookMark = oParagraphItem.as<OOX::Logic::CBookmarkStart>();
				if (std::wstring(_T("_GoBack")) == oBookMark.m_sName.get())
				{
					haveGoBack	=	TRUE;
					continue;
				}

				oParagraph.AddParagraphItem (Docx2Doc::BookmarkStart(oBookMark.m_oId->ToString(), oBookMark.m_sName.get()));
			}
			else if (oParagraphItem.is<OOX::Logic::CBookmarkEnd>())
			{
				if (haveGoBack)
				{
					haveGoBack	=	FALSE;
					continue;
				}

				const OOX::Logic::CBookmarkEnd& oBookMark = oParagraphItem.as<OOX::Logic::CBookmarkEnd>();
				oParagraph.AddParagraphItem (OOX::Logic::CBookmarkEnd(oBookMark.m_oId->ToString()));
			}
			else if (oParagraphItem.is<OOX::Logic::CFldSimple>())
			{
				// TODO: 

				ConvertFldSimple<T>(oParagraphItem.as<OOX::Logic::CFldSimple>(), styleRunPr, oParagraph, strRunType);
			}
			/*else if (oParagraphItem.is<OOX::Logic::Insert>())
			{
				const OOX::Logic::Insert& insertElement = oParagraphItem.as<OOX::Logic::Insert>();

				if (!insertElement.Runs->empty())
				{
					size_t count = (*insertElement.Runs).size();
					const std::vector<OOX::Logic::CRun>& items = (*insertElement.Runs);

					for (size_t j = 0; j < count; ++j)	
					{
						oParagraph.AddParagraphItem(ConvertRun<T>(items[j], styleRunPr, strRunType));
					}
				}
			}
			else if (oParagraphItem.is<OOX::Logic::Delete>())
			{
				const OOX::Logic::Delete& deleteElement = oParagraphItem.as<OOX::Logic::Delete>();

				if (!deleteElement.Runs->empty())
				{
					size_t count = (*deleteElement.Runs).size();
					const std::vector<OOX::Logic::CRun>& items = (*deleteElement.Runs);

					for (size_t j = 0; j < count; ++j)	
					{			
						oParagraph.AddParagraphItem(ConvertRun<T>(items[j], styleRunPr, strRunType));
					}
				}
			}*/

			UpdateItemByCondition<Docx2Doc::Paragraph> (&oParagraph, strRunType);
		}

		if (oXmlParagraph.Items->empty())
		{
			// Have some other properties

			Docx2Doc::Run run;
			run.AddProperties(styleRunPr);

			if (oXmlParagraph.m_oParagraphProperty && oXmlParagraph.m_oParagraphProperty->m_oRPr.is_init())
			{
				run.AddOrReplaceProperties(styleRunPr);
			}

			oParagraph.AddParagraphItem(run);
		}

		oParagraph.AddProperties (ConvertParagraphProperties (inputFolder.find<OOX::Document>().find<OOX::CStyles>().Default->ParagraphProperty));
		oParagraph.AddOrReplaceProperties (styleParPr);

		if (oXmlParagraph.m_oParagraphProperty)
		{
			oParagraph.AddOrReplaceProperties(ConvertParagraphProperties (*oXmlParagraph.m_oParagraphProperty));
		}

		return oParagraph;
	}
}

namespace DOCXTODOC
{
	int CFileTransformer::ValidParagraph (const OOX::Logic::CParagraph& oXmlParagraph)
	{
		// NOT IMPEMENT

		return TRUE;
	}

	PrlList CFileTransformer::GetParagraphPropertiesFromStyleHierarchy(const std::string& styleID, PrlList* styleDocRunLinkProperties )
	{
		PrlList allParagraphProperties;

		const OOX::CStyle styleById = this->inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetStyleById(styleID);

		if (styleById.m_oBasedOn.is_init())
		{
			allParagraphProperties = this->GetParagraphPropertiesFromStyleHierarchy(*styleById.m_oBasedOn, styleDocRunLinkProperties);
		}

		if ( styleById.m_oParPr.is_init() )
		{
			PrlList styleParagraphProperties = ConvertParagraphProperties(*styleById.m_oParPr);

			for (size_t i = 0; i < styleParagraphProperties.size(); ++i)
				allParagraphProperties.push_back(styleParagraphProperties[i]);
		}

		if ((styleById.m_oLink.is_init()) && (styleDocRunLinkProperties != NULL))
		{
			PrlList styleDocRunLinkPropertiesHierarchy = GetRunPropertiesFromStyleHierarchy( *styleById.m_oLink );

			for (size_t i = 0; i < styleDocRunLinkPropertiesHierarchy.size(); ++i)
				styleDocRunLinkProperties->push_back(styleDocRunLinkPropertiesHierarchy[i]);
		}

		return allParagraphProperties;
	}

	PrlList CFileTransformer::GetRunPropertiesFromStyleHierarchy(const std::wstring& styleID)
	{
		PrlList allRunProperties;

		const OOX::CStyle styleById = inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetStyleById( styleID );

		if ( styleById.m_oBasedOn.is_init() )
		{
			allRunProperties = GetRunPropertiesFromStyleHierarchy(styleById.m_oBasedOn->ToString2());
		}

		if ( styleById.m_oRunPr.is_init() )
		{
			PrlList styleRunProperties = this->ConvertRunProperties( *styleById.m_oRunPr );

			for (size_t i = 0; i < styleRunProperties.size(); ++i)
				allRunProperties.push_back(styleRunProperties[i]);
		}

		return allRunProperties;
	}

	PrlList CFileTransformer::GetTablePropertiesFromStyleHierarchy (const std::wstring& styleID)
	{
		PrlList allTableProperties;

		const OOX::CStyle styleById = inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetStyleById( styleID );

		if ( styleById.m_oBasedOn.is_init() )
		{
			allTableProperties = GetTablePropertiesFromStyleHierarchy(*styleById.m_oBasedOn);
		}

		if ( styleById.m_oTblPr.is_init() )
		{
			PrlList styleTableProperties = ConvertTableProperties(*styleById.m_oTblPr);

			for (size_t i = 0; i < styleTableProperties.size(); ++i)
				allTableProperties.push_back(styleTableProperties[i]);
		}

		return allTableProperties;
	}

	std::string CFileTransformer::GetFontNameByThemeName (const std::wstring& themeName)
	{
		std::string fontName;

		/*const OOX::Theme::File& themeFile = this->inputFolder.find<OOX::Document>().find<OOX::Theme::File>();

		if ( themeFile.themeElements.is_init() && themeFile.themeElements->fontScheme.is_init() )
		{
			const OOX::Theme::FontScheme& fontScheme = *themeFile.themeElements->fontScheme;

			std::string major = "major";
			std::string minor = "minor";

			std::string hAnsi = "HAnsi";
			std::string eastAsia = "EastAsia";
			std::string bidi = "Bidi";

			if ( fontScheme.majorFont.is_init() && ( search( themeName.begin(), themeName.end(), major.begin(), major.end() ) != themeName.end() ) )
			{
				const OOX::Theme::MajorFont& majorFont = *fontScheme.majorFont;

				if ( ( majorFont.latin.is_init() ) && ( search( themeName.begin(), themeName.end(), hAnsi.begin(), hAnsi.end() ) != themeName.end() ) )
				{
					fontName = *majorFont.latin;    
				}
				else if ( majorFont.ea.is_init() && ( search( themeName.begin(), themeName.end(), eastAsia.begin(), eastAsia.end() ) != themeName.end() ) )
				{
					fontName = *majorFont.ea;    
				}
				else if ( majorFont.cs.is_init() && ( search( themeName.begin(), themeName.end(), bidi.begin(), bidi.end() ) != themeName.end() ) )
				{
					fontName = *majorFont.cs;    
				}
			}
			else if ( search( themeName.begin(), themeName.end(), minor.begin(), minor.end() ) != themeName.end() )
			{
				const OOX::Theme::MinorFont& minorFont = *fontScheme.minorFont;

				if ( minorFont.latin.is_init() && ( search( themeName.begin(), themeName.end(), hAnsi.begin(), hAnsi.end() ) != themeName.end() ) )
				{
					fontName = *minorFont.latin;    
				}
				else if ( minorFont.ea.is_init() && ( search( themeName.begin(), themeName.end(), eastAsia.begin(), eastAsia.end() ) != themeName.end() ) )
				{
					fontName = *minorFont.ea;    
				}
				else if ( minorFont.cs.is_init() && ( search( themeName.begin(), themeName.end(), bidi.begin(), bidi.end() ) != themeName.end() ) )
				{
					fontName = *minorFont.cs;    
				}
			}
		}*/

		return fontName;
	}

	template<class T> void CFileTransformer::ConvertFldSimple(const OOX::Logic::CFldSimple& fldSimpleDocx, const PrlList& styleDocRunProperties, Docx2Doc::Paragraph& docParagraph, std::wstring& strRunType)
	{
		std::wstring::size_type findIndex = std::wstring::npos;

		findIndex = fldSimpleDocx.m_sInstr.get().find(L"PAGE");

		if ( findIndex != std::wstring::npos )
		{
			docParagraph.AddParagraphItem( Docx2Doc::Run( Docx2Doc::FldChar( Docx2Doc::FldCharTypeBegin, Docx2Doc::Constants::fltPAGE ) ) );
			docParagraph.AddParagraphItem( Docx2Doc::Run( Docx2Doc::FldChar( Docx2Doc::FldCharTypeSeparate ) ) );
			docParagraph.AddParagraphItem( ConvertRun<T>( *fldSimpleDocx.Run, styleDocRunProperties, strRunType ) );
			docParagraph.AddParagraphItem( Docx2Doc::Run( Docx2Doc::FldChar( Docx2Doc::FldCharTypeEnd ) ) );
		}

		findIndex = fldSimpleDocx.m_sInstr.get().find(L"SYMBOL");

		if ( findIndex != std::wstring::npos )
		{
			Docx2Doc::Run fldSymbolRun;

			fldSymbolRun.AddRunItem( Docx2Doc::Text(fldSimpleDocx.m_sInstr.get()));
			fldSymbolRun.AddProperties( styleDocRunProperties );

			strRunType = _T( "SYMBOL" );

			docParagraph.AddParagraphItem( Docx2Doc::Run( Docx2Doc::FldChar( Docx2Doc::FldCharTypeBegin, Docx2Doc::Constants::fltSYMBOL ) ) );
			docParagraph.AddParagraphItem( fldSymbolRun );
			docParagraph.AddParagraphItem( Docx2Doc::Run( Docx2Doc::FldChar( Docx2Doc::FldCharTypeSeparate ) ) );
			docParagraph.AddParagraphItem( Docx2Doc::Run( Docx2Doc::FldChar( Docx2Doc::FldCharTypeEnd ) ) );
		}  
	}

	template<class T> Docx2Doc::Hyperlink CFileTransformer::ConvertHyperlink (const OOX::Logic::CHyperlink& docxHyperlink, const PrlList& styleDocRunProperties )
	{
		Docx2Doc::Hyperlink docHyperlink;

		if (docxHyperlink.m_oId.is_init())
		{
			OOX::HyperLink* hyperlink = NULL;
			const OOX::RId& rid = docxHyperlink.m_oId;

			if (typeid(T) != typeid(OOX::Document))
			{
				if (inputFolder.find<OOX::Document>().find<T>().exist(rid))
				{
					hyperlink = dynamic_cast<OOX::CHyperLink*>(inputFolder.find<OOX::Document>().find<T>()[rid].get());
				}
			}
			else
			{
				if (inputFolder.find<OOX::Document>().exist(rid))
				{
					hyperlink = dynamic_cast<OOX::HyperLink*>(inputFolder.find<OOX::Document>()[rid].get());
				}
			}

			if ( hyperlink != NULL )
			{
				std::wstring hyperlinkURL = hyperlink->Uri().wstring();

				docHyperlink.SetURL( hyperlinkURL.c_str() );
			}
		}

		if (docxHyperlink.m_sAnchor.is_init())
		{
			docHyperlink.SetLocationInTheFile(docxHyperlink.m_sAnchor.get());
		}

		size_t count = (*docxHyperlink.Runs).size();
		const std::vector<OOX::Logic::CRun>& items = (*docxHyperlink.Runs);

		for (size_t i = 0; i < count; ++i)	
		{			
			std::wstring strRunType;
			docHyperlink.AddRun(ConvertRun<T>(items[i], styleDocRunProperties, strRunType));
			UpdateItemByCondition<Docx2Doc::Hyperlink>(&docHyperlink, strRunType);
		}

		return docHyperlink;
	}

	template<class T> void CFileTransformer::UpdateItemByCondition (T* docItem, const std::wstring& condition)
	{
		if ( ( docItem != NULL ) && ( !condition.empty() ) )
		{
			static bool haveSeparator = false;

			Docx2Doc::FldChar* fldChar = NULL;

			int findComplete	=	FALSE;

			for (T::reverse_iterator riter = docItem->rbegin(); riter != docItem->rend(); ++riter)
			{
				if (riter->is<Docx2Doc::CRun>())
				{
					Docx2Doc::Run& run = riter->as<Docx2Doc::CRun>();

					for (Docx2Doc::Run::reverse_iterator runRIter = run.rbegin(); runRIter != run.rend(); ++runRIter)
					{
						if ( runRIter->is<Docx2Doc::FldChar>() )
						{
							fldChar = &runRIter->as<Docx2Doc::FldChar>();

							findComplete	=	TRUE;
							break;
						}
					}

					if (findComplete)
						break;
				}
			}

			if ( NULL == fldChar )
				return;

			BYTE charType	=	fldChar->CharType();

			if (condition == std::wstring(L"HYPERLINK"))
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties(Docx2Doc::Constants::fltHYPERLINK);
				}
			}
			else if ( condition == std::wstring( L"PAGEREF" ))
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties( Docx2Doc::Constants::fltPAGEREF );
				}
			}
			else if ( condition == std::wstring( L"TOC" ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties( Docx2Doc::Constants::fltTOC );
				}
			}
			else if ( condition == std::wstring( L"PAGE" ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties( Docx2Doc::Constants::fltPAGE );
				}  
			}
			else if ( condition == std::wstring( L"SYMBOL" ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties( Docx2Doc::Constants::fltSYMBOL );
				}  
			}
			else if ( condition == std::wstring( _T( "ADDRESSBLOCK" ) ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties( Docx2Doc::Constants::fltADDRESSBLOCK );
				}  
			}
			else if ( condition == std::wstring( _T( "GREETINGLINE" ) ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties( Docx2Doc::Constants::fltGREETINGLINE );
				}  
			}
			else if ( condition == std::wstring( _T( "MERGEFIELD" ) ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharBegin )
				{
					fldChar->SetFieldCharacterProperties( Docx2Doc::Constants::fltMERGEFIELD );
				}  
			}
			else if ( condition == std::wstring( _T( "separate" ) ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharSeparate )
				{
					//fldChar->SetFieldCharacterProperties(0);
					haveSeparator = true;
				}
			}
			else if ( condition == std::wstring( _T( "end" ) ) )
			{
				if (charType == Docx2Doc::FldChar::FldCharEnd )
				{
					fldChar->SetFieldCharacterProperties( (BYTE)Docx2Doc::grffldEnd( false, false, false, false, false, false, false, haveSeparator ) );

					haveSeparator = false;
				}
			}
		}  
	}

	//
	Docx2Doc::Constants::VerticalMergeFlag CFileTransformer::ConvertTableVerticalMergeFlag (const nullable<OOX::Logic::CVMerge>& vMerge)
	{
		Docx2Doc::Constants::VerticalMergeFlag vmf = Docx2Doc::Constants::fvmClear;

		if ( vMerge.is_init() )
		{
			if ( vMerge->Value.is_init() )
			{
				if ( *vMerge->Value == std::string( "restart" ) )
				{
					vmf = Docx2Doc::Constants::fvmRestart;
				}
				else if ( *vMerge->Value == std::string( "continue" ) )
				{
					vmf = Docx2Doc::Constants::fvmMerge;
				}
			}
			else
			{
				vmf = Docx2Doc::Constants::fvmMerge;
			}
		}

		return vmf;
	}

	const PrlList CFileTransformer::ConvertRunProperties (const OOX::Logic::CRunProperty& docxRunProperties)
	{
		m_bIsHaveRunPr	=	TRUE;

		PrlList docRunProperties;

		if ( docxRunProperties.m_oBold.is_init() )
		{
			BYTE bold = ( ( docxRunProperties.m_oBold ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFBold, &bold ) );
		}

		if ( docxRunProperties.m_oItalic.is_init() )
		{
			BYTE italic = ( ( *docxRunProperties.m_oItalic ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFItalic, &italic ) );
		}

		if ( docxRunProperties.m_oU.is_init() && *docxRunProperties.Under && docxRunProperties.UnderType.is_init() )
		{
			BYTE under = this->kulMap[*docxRunProperties.UnderType];

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCKul, &under ) );
		}

		if ( docxRunProperties.m_oStrike.is_init() )
		{
			BYTE strike = ( ( *docxRunProperties.m_oStrike ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFStrike, &strike ) );
		}

		if ( docxRunProperties.m_oDStrike.is_init() )
		{
			BYTE dStrike = ( ( *docxRunProperties.m_oDStrike ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFDStrike, &dStrike ) );
		}

		if ( docxRunProperties.m_oSmallCaps.is_init() )
		{
			BYTE smallCaps = ( ( *docxRunProperties.m_oSmallCaps ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFSmallCaps, &smallCaps ) );
		}

		if ( docxRunProperties.m_oCaps.is_init() )
		{
			BYTE caps = ( ( *docxRunProperties.m_oCaps ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFCaps, &caps ) );
		}

		if ( docxRunProperties.m_oEmboss.is_init() )
		{
			BYTE emboss = ( ( *docxRunProperties.m_oEmboss ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFEmboss, &emboss ) );
		}

		if ( docxRunProperties.m_oImprint.is_init() )
		{
			BYTE imprint = ( ( *docxRunProperties.m_oImprint ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFImprint, &imprint ) );
		}

		if ( docxRunProperties.m_oOutline.is_init() )
		{
			BYTE outline = ( ( *docxRunProperties.m_oOutline ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFOutline, &outline ) );
		}

		if ( docxRunProperties.m_oShadow.is_init() )
		{
			BYTE shadow = ( ( *docxRunProperties.m_oShadow ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFShadow, &shadow ) );
		}

		if ( docxRunProperties.m_oVanish.is_init() )
		{
			BYTE vanish = ( ( *docxRunProperties.m_oVanish ) ? ( 1 ) : ( 0 ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCFVanish, &vanish ) );
		}

		if ( docxRunProperties.FontSize.is_init() )
		{
			unsigned short fontSize = (unsigned short)docxRunProperties.FontSize;
			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCHps, (BYTE*)&fontSize ) );
			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCHpsBi, (BYTE*)&fontSize ) );
		}

		if (docxRunProperties.FontColor.is_init())
		{
			int colorIntValue	=	Docx2Doc::COLORREF::cvAuto;
			if (false == docxRunProperties.FontColor->isAuto())
				colorIntValue	=	HexString2Int( docxRunProperties.FontColor->Tostd::string() );

			Docx2Doc::COLORREF color (colorIntValue);

			docRunProperties.push_back (Docx2Doc::Prl((short)DocFileFormat::sprmCCv, color));
		}

		if ( docxRunProperties.m_oHighlight.is_init() )
		{
			BYTE ico = DOCXDOCUTILS::ColorToIco (*docxRunProperties.m_oHighlight);
			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCHighlight, &ico ) );
		}

		if ( docxRunProperties.Shading.is_init() && docxRunProperties.Shading->fill.is_init() )
		{
			int colorIntValue	=	0;
			int fillAuto		=	0x00;

			if (docxRunProperties.Shading->fill == "auto")
			{
				fillAuto = Docx2Doc::COLORREF::cvAuto;
			}
			else
			{
				colorIntValue = HexString2Int( *docxRunProperties.Shading->fill );
			}

			Docx2Doc::SHDOperand shdOperand (
				Docx2Doc::Shd( Docx2Doc::COLORREF( (int)( 0 | fillAuto ) ),
				Docx2Doc::COLORREF( colorIntValue | fillAuto ),
				0 ) );

			docRunProperties.push_back (Docx2Doc::Prl( (short)DocFileFormat::sprmCShd, shdOperand ));
		}

		if ( docxRunProperties.m_oRFonts.is_init() )
		{
			short fontIndex = 0;

			if ( docxRunProperties.m_oRFonts->m_sAscii.is_init() && !docxRunProperties.m_oRFonts->m_oAsciiTheme.is_init() )
			{
				std::wstring strFontName	= docxRunProperties.m_oRFonts->m_sAscii.get();
				if (strFontName.length())
				{			
					AddInternalFont (strFontName);

					fontIndex	=	m_mapFontTableMap[strFontName];

					docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgFtc0, (BYTE*)&fontIndex ) );
				}
			}
			else if ( docxRunProperties.rFonts->AsciiTheme.is_init() )
			{
				std::string fontNameByThemeName = GetFontNameByThemeName(docxRunProperties.rFonts->AsciiTheme);

				if ( !fontNameByThemeName.empty() )
				{
					std::map<std::string, short>::const_iterator findResult = m_mapFontTableMap.find( fontNameByThemeName );

					if ( findResult != m_mapFontTableMap.end() )
					{
						fontIndex = findResult->second;
					}

					docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgFtc0, (byte*)&fontIndex ) );
				}
			}

			if (docxRunProperties.rFonts->Cs.is_init() && !docxRunProperties.rFonts->Cstheme.is_init())
			{
				std::string strFontName	= docxRunProperties.rFonts->Cs;
				if (strFontName.length())
				{			
					AddInternalFont (strFontName);

					fontIndex	=	m_mapFontTableMap[strFontName];

					docRunProperties.push_back (Docx2Doc::Prl( (short)DocFileFormat::sprmCRgFtc1, (BYTE*)&fontIndex));
				}
			}
			else if ( docxRunProperties.rFonts->Cstheme.is_init() )
			{
				std::string fontNameByThemeName = this->GetFontNameByThemeName( docxRunProperties.rFonts->Cstheme );

				if ( !fontNameByThemeName.empty() )
				{
					std::map<std::string, short>::const_iterator findResult = m_mapFontTableMap.find( fontNameByThemeName );

					if ( findResult != m_mapFontTableMap.end() )
					{
						fontIndex = findResult->second;
					}

					docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgFtc1, (BYTE*)&fontIndex ) );
				}
			}

			if ( docxRunProperties.rFonts->hAnsi.is_init() && !docxRunProperties.rFonts->HAnsiTheme.is_init() )
			{
				std::string strFontName	= docxRunProperties.rFonts->hAnsi;
				if (strFontName.length())
				{			
					AddInternalFont (strFontName);

					fontIndex	=	m_mapFontTableMap[docxRunProperties.rFonts->hAnsi];

					docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgFtc2, (byte*)&fontIndex ) );
				}
			}
			else if ( docxRunProperties.rFonts->HAnsiTheme.is_init() )
			{
				std::string fontNameByThemeName = GetFontNameByThemeName( docxRunProperties.rFonts->HAnsiTheme );

				if ( !fontNameByThemeName.empty() )
				{
					std::map<std::string, short>::const_iterator findResult = m_mapFontTableMap.find( fontNameByThemeName );

					if (findResult != m_mapFontTableMap.end())
					{
						fontIndex = findResult->second;
					}

					docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgFtc2, (BYTE*)&fontIndex ) );
				}
			}
		}

		if ( docxRunProperties.Lang.is_init() )
		{
			if ( docxRunProperties.Lang->Value.is_init() )
			{
				Docx2Doc::LID lid = lidMap[docxRunProperties.Lang->Value];
				docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgLid0_80, (BYTE*)lid ) );
				docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgLid0, (BYTE*)lid ) );
			}

			if ( docxRunProperties.Lang->EastAsia.is_init() )
			{
				Docx2Doc::LID lid = lidMap[docxRunProperties.Lang->EastAsia];
				docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgLid1_80, (BYTE*)lid ) );
				docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCRgLid1, (BYTE*)lid ) );
			}

			if ( docxRunProperties.Lang->Bidi.is_init() )
			{
				Docx2Doc::LID lid = lidMap[docxRunProperties.Lang->Bidi];
				docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCLidBi, (BYTE*)lid ) );
			}
		}

		if ( docxRunProperties.Spacing.is_init() )
		{
			short CDxaSpace = Docx2Doc::XAS( *docxRunProperties.Spacing );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCDxaSpace, (BYTE*)&CDxaSpace ) );
		}

		if ( docxRunProperties.Index.is_init() )
		{
			std::string index = docxRunProperties.Index->Tostd::string();
			BYTE CIss = (BYTE)Docx2Doc::Constants::superSubScriptNormalText;

			if ( index == std::string( "superscript" ) )
			{
				CIss = (BYTE)Docx2Doc::Constants::superSubScriptSuperscript;
			}
			else if ( index == std::string( "subscript" ) )
			{
				CIss = (BYTE)Docx2Doc::Constants::superSubScriptSubscript;
			}

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCIss, (BYTE*)&CIss ) );
		}

		if ( docxRunProperties.Kern.is_init() )
		{
			int kern = *docxRunProperties.Kern;

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCHpsKern, (BYTE*)&kern ) );
		}

		if ( docxRunProperties.Position.is_init() )
		{
			int position = *docxRunProperties.Position;

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCHpsPos, (BYTE*)&position ) );
		}

		if ( docxRunProperties.Scale.is_init() )
		{
			unsigned short scale = *docxRunProperties.Scale;

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCCharScale, (BYTE*)&scale ) );
		}

		if ( docxRunProperties.Border.is_init() )
		{
			DOCXDOCUTILS::CTblBorders oBorder;
			std::map<std::string, BYTE>& oBrcMap	=	oBorder.GetBrcMap ();

			unsigned int brc80 =  (unsigned int)Docx2Doc::Brc80(
				docxRunProperties.Border->Bdr->Sz.get_value_or_default(), 
				oBrcMap[*docxRunProperties.Border->Bdr->Value], 
				DOCXDOCUTILS::ColorToIco (docxRunProperties.Border->Bdr->Color.get_value_or_default()), 
				docxRunProperties.Border->Bdr->Space.get_value_or_default(), 
				false, 
				false );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCBrc80, (BYTE*)(&brc80) ) );

			Docx2Doc::BrcOperand brcOperand( Docx2Doc::Brc(
				Docx2Doc::COLORREF( HexString2Int( docxRunProperties.Border->Bdr->Color.get_value_or_default().Tostd::string() ) ),
				docxRunProperties.Border->Bdr->Sz.get_value_or_default(), 
				oBrcMap[*docxRunProperties.Border->Bdr->Value],
				docxRunProperties.Border->Bdr->Space.get_value_or_default(), 
				false, 
				false ) );

			docRunProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmCBrc, (BYTE*)brcOperand ) );
		}

		return docRunProperties;
	}

	const PrlList CFileTransformer::ConvertParagraphProperties (const OOX::Logic::ParagraphProperty& docxParagraphProperties) 
	{
		PrlList docParagraphProperties;

		if ( docxParagraphProperties.Align.is_init() )
		{
			BYTE justification	=	DOCXDOCUTILS::AlignFromString (docxParagraphProperties.Align->Tostd::string());

			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPJc, &justification ) );
			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPJc80, &justification ) );
		}

		if ( docxParagraphProperties.Shading.is_init() && docxParagraphProperties.Shading->fill.is_init() )
		{
			int colorIntValue = 0;
			int fillAuto = 0x00;

			if ( *docxParagraphProperties.Shading->fill == "auto" )
			{
				fillAuto = Docx2Doc::COLORREF::cvAuto;
			}
			else
			{
				colorIntValue = HexString2Int( *docxParagraphProperties.Shading->fill );
			}  

			Docx2Doc::SHDOperand shdOperand( Docx2Doc::Shd( Docx2Doc::COLORREF( (int)( 0 | fillAuto ) ),
				Docx2Doc::COLORREF( colorIntValue | fillAuto ),
				0 ) );

			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPShd, shdOperand ) );
		}

		if ( docxParagraphProperties.Spacing.is_init() )
		{
			if ( docxParagraphProperties.Spacing->After.is_init() )
			{
				unsigned short pDyaAfter = (unsigned short)(*docxParagraphProperties.Spacing->After);

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDyaAfter, (BYTE*)(&pDyaAfter) ) );
			}

			if ( docxParagraphProperties.Spacing->Before.is_init() )
			{
				unsigned short pDyaBefore = (unsigned short)(*docxParagraphProperties.Spacing->Before);

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDyaBefore, (BYTE*)(&pDyaBefore) ) );
			}

			if ( ( docxParagraphProperties.Spacing->Line.is_init() ) && ( docxParagraphProperties.Spacing->LineRule.is_init() ) )
			{
				bool lineRule = false;
				short line = 0;

				line = (short)(*docxParagraphProperties.Spacing->Line);

				if ( *docxParagraphProperties.Spacing->LineRule == std::string( "exact" ) )
				{
					line = -line;
				}
				else if ( *docxParagraphProperties.Spacing->LineRule == std::string( "auto" ) )
				{
					lineRule = true;
				}

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDyaLine, (BYTE*)Docx2Doc::LSPD( line, lineRule ) ) );
			}

			if ( docxParagraphProperties.Spacing->BeforeAutospacing.is_init() )
			{
				Bool8 beforeAutospacing = 0x00;

				if ( *docxParagraphProperties.Spacing->BeforeAutospacing )
				{
					beforeAutospacing = 0x01;
				}

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPFDyaBeforeAuto, &beforeAutospacing ) );
			}

			if ( docxParagraphProperties.Spacing->AfterAutospacing.is_init() )
			{
				Bool8 afterAutospacing = 0x00;

				if ( *docxParagraphProperties.Spacing->AfterAutospacing )
				{
					afterAutospacing = 0x01;
				}

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPFDyaAfterAuto, &afterAutospacing ) );
			}
		}

		if ( docxParagraphProperties.Ind.is_init() )
		{
			if ( docxParagraphProperties.Ind->Left.is_init() )
			{
				short pDxaLeft = Docx2Doc::XAS( (short)(*docxParagraphProperties.Ind->Left) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaLeft, (BYTE*)(&pDxaLeft) ) );
				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaLeft80, (BYTE*)(&pDxaLeft) ) );
			}

			if ( docxParagraphProperties.Ind->Right.is_init() )
			{
				short pDxaRight = Docx2Doc::XAS( (short)(*docxParagraphProperties.Ind->Right) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaRight, (BYTE*)(&pDxaRight) ) );
				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaRight80, (BYTE*)(&pDxaRight) ) );
			}

			if ( docxParagraphProperties.Ind->Hanging.is_init() )
			{
				short pDxaLeft1 = ( ( Docx2Doc::XAS( (short)(*docxParagraphProperties.Ind->Hanging) ) ) * ( -1 ) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaLeft1, (BYTE*)(&pDxaLeft1) ) );
				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaLeft180, (BYTE*)(&pDxaLeft1) ) );
			}

			if ( docxParagraphProperties.Ind->FirstLine.is_init() )
			{
				short pDxaLeft1 = Docx2Doc::XAS( (short)(*docxParagraphProperties.Ind->FirstLine) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaLeft1, (BYTE*)(&pDxaLeft1) ) );
				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPDxaLeft180, (BYTE*)(&pDxaLeft1) ) );
			}
		}

		if (docxParagraphProperties.NumPr.is_init())
		{
			if (docxParagraphProperties.NumPr->Ilvl.is_init())
			{
				BYTE pIlvl	=	(BYTE)(*docxParagraphProperties.NumPr->Ilvl);
				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPIlvl, (BYTE*)(&pIlvl) ) );
			}

			if ( docxParagraphProperties.NumPr->NumId.is_init() )
			{
				int nNumID	=	(*docxParagraphProperties.NumPr->NumId);
				SHORT pIlfo	=	idIndexMap [nNumID];

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPIlfo, (BYTE*)(&pIlfo) ) );
			}
		}

		if ( docxParagraphProperties.OutlineLvl.is_init() )
		{
			BYTE POutLvl = *docxParagraphProperties.OutlineLvl;

			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPOutLvl, &POutLvl ) );
		}

		if ( *docxParagraphProperties.KeepLines )
		{
			Bool8 PFKeep = 0x01;

			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPFKeep, &PFKeep ) );
		}

		if ( *docxParagraphProperties.KeepNext )
		{
			Bool8 PFKeepFollow = 0x01;

			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPFKeepFollow, &PFKeepFollow ) );
		}

		if (*docxParagraphProperties.pageBreakBefore)
		{
			Bool8 PFPageBreakBefore = 0x01;
			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPFPageBreakBefore, &PFPageBreakBefore ) );
		}

		if ( *docxParagraphProperties.ContextualSpacing )
		{
			Bool8 PFContextualSpacing = 0x01;
			docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPFContextualSpacing, &PFContextualSpacing ) );
		}

		if ( docxParagraphProperties.ParagraphBorder.is_init() )
		{
			DOCXDOCUTILS::CTblBorders oBorder;
			std::map<std::string, BYTE>& oBrcMap	=	oBorder.GetBrcMap ();

			if ( docxParagraphProperties.ParagraphBorder->Top.is_init() )
			{
				unsigned int brc80Top =  (unsigned int)Docx2Doc::Brc80( docxParagraphProperties.ParagraphBorder->Top->Bdr->Sz.get_value_or_default(),
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Top->Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxParagraphProperties.ParagraphBorder->Top->Bdr->Color.get_value_or_default()), 
					docxParagraphProperties.ParagraphBorder->Top->Bdr->Space.get_value_or_default(), 
					false, 
					false );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcTop80, (BYTE*)(&brc80Top) ) );

				Docx2Doc::BrcOperand brcOperandTop( Docx2Doc::Brc( Docx2Doc::COLORREF( HexString2Int( docxParagraphProperties.ParagraphBorder->Top->Bdr->Color.get_value_or_default().Tostd::string() ) ),
					docxParagraphProperties.ParagraphBorder->Top->Bdr->Sz.get_value_or_default(), 
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Top->Bdr->Value],
					docxParagraphProperties.ParagraphBorder->Top->Bdr->Space.get_value_or_default(), 
					false, 
					false ) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcTop, (BYTE*)brcOperandTop ) );
			}

			if ( docxParagraphProperties.ParagraphBorder->Bottom.is_init() )
			{
				unsigned int brc80Bottom =  (unsigned int)Docx2Doc::Brc80( docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Sz.get_value_or_default(),
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Color.get_value_or_default()), 
					docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Space.get_value_or_default(), 
					false, 
					false );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcBottom80, (BYTE*)(&brc80Bottom) ) );

				Docx2Doc::BrcOperand brcOperandBottom( Docx2Doc::Brc( Docx2Doc::COLORREF( HexString2Int( docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Color.get_value_or_default().Tostd::string() ) ),
					docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Sz.get_value_or_default(), 
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Value],
					docxParagraphProperties.ParagraphBorder->Bottom->Bdr->Space.get_value_or_default(),
					false, 
					false ) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcBottom, (BYTE*)brcOperandBottom ) );
			}

			if ( docxParagraphProperties.ParagraphBorder->Left.is_init() )
			{
				unsigned int brc80Left =  (unsigned int)Docx2Doc::Brc80( docxParagraphProperties.ParagraphBorder->Left->Bdr->Sz.get_value_or_default(),
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Left->Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxParagraphProperties.ParagraphBorder->Left->Bdr->Color.get_value_or_default()), 
					docxParagraphProperties.ParagraphBorder->Left->Bdr->Space.get_value_or_default(), 
					false, 
					false );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcLeft80, (BYTE*)(&brc80Left) ) );

				Docx2Doc::BrcOperand brcOperandLeft( Docx2Doc::Brc( Docx2Doc::COLORREF( HexString2Int( docxParagraphProperties.ParagraphBorder->Left->Bdr->Color.get_value_or_default().Tostd::string() ) ),
					docxParagraphProperties.ParagraphBorder->Left->Bdr->Sz.get_value_or_default(), 
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Left->Bdr->Value],
					docxParagraphProperties.ParagraphBorder->Left->Bdr->Space.get_value_or_default(),
					false, 
					false ) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcLeft, (BYTE*)brcOperandLeft ) );
			}

			if ( docxParagraphProperties.ParagraphBorder->Right.is_init() )
			{
				unsigned int brc80Right =  (unsigned int)Docx2Doc::Brc80( docxParagraphProperties.ParagraphBorder->Right->Bdr->Sz.get_value_or_default(),
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Right->Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxParagraphProperties.ParagraphBorder->Right->Bdr->Color.get_value_or_default()), 
					docxParagraphProperties.ParagraphBorder->Right->Bdr->Space.get_value_or_default(), 
					false, 
					false );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcRight80, (BYTE*)(&brc80Right) ) );

				Docx2Doc::BrcOperand brcOperandRight( Docx2Doc::Brc( Docx2Doc::COLORREF( HexString2Int( docxParagraphProperties.ParagraphBorder->Right->Bdr->Color.get_value_or_default().Tostd::string() ) ),
					docxParagraphProperties.ParagraphBorder->Right->Bdr->Sz.get_value_or_default(), 
					oBrcMap[*docxParagraphProperties.ParagraphBorder->Right->Bdr->Value],
					docxParagraphProperties.ParagraphBorder->Right->Bdr->Space.get_value_or_default(),
					false, 
					false ) );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPBrcRight, (BYTE*)brcOperandRight ) );
			}
		}

		if ( docxParagraphProperties.TextFrameProperties.is_init() )
		{
			if ( docxParagraphProperties.TextFrameProperties->HAnchor.is_init() && docxParagraphProperties.TextFrameProperties->VAnchor.is_init() )
			{
				BYTE positionCodeOperand = Docx2Doc::PositionCodeOperand( this->verticalPositionCodeMap[*docxParagraphProperties.TextFrameProperties->VAnchor], this->horizontalPositionCodeMap[*docxParagraphProperties.TextFrameProperties->HAnchor] );
				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPPc, &positionCodeOperand ) );
			}

			if ( docxParagraphProperties.TextFrameProperties->Wrap.is_init() )
			{
				BYTE PWr = this->textFrameWrappingMap[*docxParagraphProperties.TextFrameProperties->Wrap];
				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPWr, &PWr ) );
			}

			if ( docxParagraphProperties.TextFrameProperties->X.is_init() )
			{
				short PDxaAbs = Docx2Doc::XAS_plusOne ((short)(*docxParagraphProperties.TextFrameProperties->X));
				docParagraphProperties.push_back (Docx2Doc::Prl((short)DocFileFormat::sprmPDxaAbs, (BYTE*)(&PDxaAbs)));
			}

			if ( docxParagraphProperties.TextFrameProperties->Y.is_init() )
			{
				short PDyaAbs = Docx2Doc::YAS_plusOne ((short)*docxParagraphProperties.TextFrameProperties->Y);
				docParagraphProperties.push_back (Docx2Doc::Prl((short)DocFileFormat::sprmPDyaAbs, (BYTE*)(&PDyaAbs)));
			}

			if ( docxParagraphProperties.TextFrameProperties->H.is_init() )
			{
				unsigned short PWHeightAbs = Docx2Doc::YAS_nonNeg ((unsigned short)*docxParagraphProperties.TextFrameProperties->H);
				docParagraphProperties.push_back (Docx2Doc::Prl ((short)DocFileFormat::sprmPWHeightAbs, (BYTE*)(&PWHeightAbs)));
			}

			if ( docxParagraphProperties.TextFrameProperties->W.is_init() )
			{
				unsigned short PDxaWidth = Docx2Doc::XAS_nonNeg ((unsigned short)*docxParagraphProperties.TextFrameProperties->W);
				docParagraphProperties.push_back (Docx2Doc::Prl((short)DocFileFormat::sprmPDxaWidth, (BYTE*)(&PDxaWidth)));
			}

			if ( docxParagraphProperties.TextFrameProperties->HSpace.is_init() )
			{
				unsigned short PDxaFromText = Docx2Doc::XAS_nonNeg((unsigned short)*docxParagraphProperties.TextFrameProperties->HSpace);
				docParagraphProperties.push_back(Docx2Doc::Prl((short)DocFileFormat::sprmPDxaFromText, (BYTE*)(&PDxaFromText)));
			}

			if ( docxParagraphProperties.TextFrameProperties->VSpace.is_init() )
			{
				unsigned short PDyaFromText = Docx2Doc::YAS_nonNeg((unsigned short)*docxParagraphProperties.TextFrameProperties->VSpace);
				docParagraphProperties.push_back (Docx2Doc::Prl( (short)DocFileFormat::sprmPDyaFromText, (BYTE*)(&PDyaFromText)));
			}
		}

		if ( docxParagraphProperties.Tabs.is_init() )
		{
			std::vector<Docx2Doc::TBD> tbds;
			std::vector<Docx2Doc::XAS> xass;

			size_t count = (*docxParagraphProperties.Tabs->Tabs).size();
			const std::vector<OOX::Logic::TabProperty>& items = (*docxParagraphProperties.Tabs->Tabs);

			for (size_t i = 0; i < count; ++i)	
			{			
				Docx2Doc::Constants::TabJC TabStopAlign = customTabStopAlignment[*(items[i]).Val];
				if (0x05 == (int)TabStopAlign)	// 0x05 означает clear, т.е. No Tab Stop
					continue;

				Docx2Doc::TBD tbd(TabStopAlign, customTabStopLeader[items[i].Leader.get_value_or_default()]);
				tbds.push_back(tbd);

				Docx2Doc::XAS xas((short)(*(items[i]).Pos));
				xass.push_back(xas);
			}

			if (xass.size() > 0 && tbds.size() > 0)
			{
				Docx2Doc::PChgTabsAdd pChgTabsAdd( xass, tbds );
				Docx2Doc::PChgTabsPapxOperand pChgTabsPapxOperand( Docx2Doc::PChgTabsDel(), pChgTabsAdd );

				docParagraphProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmPChgTabsPapx, (BYTE*)pChgTabsPapxOperand ) );
			}
		}

		return docParagraphProperties;
	}
}

namespace DOCXTODOC	//	LEVELS
{
	void CFileTransformer::ConvertNumbering (const OOX::Numbering& oXmlNumbering)
	{
		if (oXmlNumbering.AbstractNums->size() == 0 || oXmlNumbering.Nums->size() == 0)
			return;

		Docx2Doc::PlfLst plfLst	(ConvertAbstractNums(*oXmlNumbering.AbstractNums));
		std::vector<Docx2Doc::LVL> lvls = ConvertLVLs (oXmlNumbering, *oXmlNumbering.AbstractNums);
		Docx2Doc::ListFormattingInformation lfi (plfLst, lvls);

		m_pDOCFile->SetListFormattingInformation (lfi);
		m_pDOCFile->SetListFormattingOverrideInformation (ConvertNums(*oXmlNumbering.Nums));
	}

	const std::vector<Docx2Doc::LSTF> CFileTransformer::ConvertAbstractNums (const std::vector<OOX::Numbering::AbstractNum>& arrNums)
	{
		// Fill LSTF ( The LSTF structure contains formatting properties that apply to an entire list. )

		std::vector<Docx2Doc::LSTF> arrLSTF;

		int nId	=	1;	//	уникальный индентификатор для списка, любое число от 1 ~ 0xFFFFFFFF

		size_t count = arrNums.size();
		for (size_t j = 0; j < count; ++j)
		{
			const OOX::Numbering::AbstractNum& number = arrNums[j];

			if (number.Nsid.is_init())
			{
				nId			=	HexString2Int (number.Nsid.get_value_or_default());
			}
			else
			{
				for (std::map<int, int>::const_iterator it = idLsidMap.begin(); it != idLsidMap.end(); ++it)
				{
					nId		=	std::max(it->second, nId);
				}

				++nId;
			}

			idLsidMap.insert(std::make_pair(number.Id, nId));

			Docx2Doc::Tplc* tplc = Docx2Doc::TplcFactory::CreateTplc (HexString2Int(number.Tmpl.get_value_or_default()));

			bool fSimpleList	=	false;
			bool fAutoNum		=	false;
			bool fHybrid		=	false;

			if ((*number.MultiLevelType) == std::string("hybridMultilevel"))
				fHybrid			=	true; 
			if ((*number.MultiLevelType) == std::string("singleLevel"))
				fSimpleList		=	true;  

			arrLSTF.push_back (Docx2Doc::LSTF (nId, tplc, fSimpleList, fAutoNum, fHybrid, Docx2Doc::grfhic(), NULL /*!!!TODO!!!*/));

			RELEASEOBJECT(tplc);
		}

		return arrLSTF;
	}

	const std::vector<Docx2Doc::LVL> CFileTransformer::ConvertLVLs(const OOX::Numbering& oXmlNumbering, const std::vector<OOX::Numbering::AbstractNum>& arAbstractNums)
	{
		std::vector<Docx2Doc::LVL> oLevels;

		size_t numsCount = arAbstractNums.size();
		for (size_t j = 0; j < numsCount; ++j)
		{
			const OOX::Numbering::AbstractNum& oAbstractNum = arAbstractNums[j];
			size_t levCount = oAbstractNum.Levels->size();
			for (size_t i = 0; i < levCount; ++i)
			{
				const OOX::Numbering::Level& oLevel = oAbstractNum.Levels->operator [](i);
				oLevels.push_back (ConvertLVL(oLevel));
			}

			// 
			if (0 == levCount)
			{
				if (oAbstractNum.numStyleLink.is_init())
				{
					int nInd = FindAbstractNumIdWithStyleRef (oXmlNumbering, oAbstractNum.numStyleLink);
					if ((nInd >= 0) && (nInd < (int)numsCount))
					{
						for (size_t i = 0; i < numsCount; ++i)
						{
							const OOX::Numbering::AbstractNum& oFindNum = arAbstractNums[i];
							if (nInd == oFindNum.Id)
							{
								size_t levCount = oFindNum.Levels->size();
								for (size_t m = 0; m < levCount; ++m)
								{
									const OOX::Numbering::Level& oLevel = oFindNum.Levels->operator [](m);
									oLevels.push_back (ConvertLVL(oLevel));
								}

								break;
							}
						}
					}
				}
			}
		}

		return oLevels;
	}

	const Docx2Doc::LVL CFileTransformer::ConvertLVL (const OOX::Numbering::Level& _level)
	{
		Docx2Doc::Constants::MSONFC nfc = this->numFmtMap[_level.NumFmt->Tostd::string()];
		Docx2Doc::Constants::LevelJustification jc =
			(Docx2Doc::Constants::LevelJustification)DOCXDOCUTILS::AlignFromString (_level.Align.get_value_or(OOX::Logic::Align( std::string( "left" ) ) ).Tostd::string());
		bool fTentative = ( ( _level.Tentative.get_value_or( 0 ) == 1 ) ? ( true ) : ( false ) );
		Docx2Doc::Constants::CharacterFollows ixchFollow = Docx2Doc::Constants::characterFollowsTab;

		if ( _level.Suffix.is_init() )
		{
			if ( *_level.Suffix == std::string( "tab" ) )
			{
				ixchFollow = Docx2Doc::Constants::characterFollowsTab;
			}
			else if ( *_level.Suffix == std::string( "space" ) )
			{
				ixchFollow = Docx2Doc::Constants::characterFollowsSpace;
			}
			else
			{
				ixchFollow = Docx2Doc::Constants::characterFollowsNothing;
			}
		}

		Docx2Doc::LVLF lvlf( *_level.Start, nfc, jc, false, false, false, false, fTentative, ixchFollow, 0, 0, Docx2Doc::grfhic() /*!!!TODO!!!*/ );

		PrlList grpprlPapx;
		PrlList grpprlChpx;

		if ( _level.ParagraphProperty.is_init() )
		{
			grpprlPapx = ConvertParagraphProperties( *_level.ParagraphProperty );  
		}

		if ( _level.RunProperty.is_init() )
		{
			grpprlChpx = ConvertRunProperties( *_level.RunProperty );  
		}

		return Docx2Doc::LVL( lvlf, grpprlPapx, grpprlChpx, this->ConvertLvlText( *_level.Text, nfc  ) );
	}

	const Docx2Doc::PlfLfo CFileTransformer::ConvertNums (const std::vector<OOX::Numbering::Num>& oXmlNums)
	{
		std::vector<Docx2Doc::LFO> lfos;
		std::vector<Docx2Doc::LFOData> lfoDatas;

		short listIndex = 1;

		for (size_t i = 0; i < oXmlNums.size(); ++i)
		{
			const OOX::Numbering::Num& oXmlNum = oXmlNums[i];
			idIndexMap.insert( std::make_pair( *oXmlNum.NumId, listIndex++ ) );

			std::vector<Docx2Doc::LFOLVL> rgLfoLvl;

			for (size_t j = 0; j < oXmlNum.LevelOverrides->size(); ++j)
			{
				const OOX::Numbering::LevelOverride& levelOverride = oXmlNum.LevelOverrides->operator[](j);
				Docx2Doc::LVL lvl;

				bool bHaveLVL = false;
				if (levelOverride.Level.is_init())
				{
					lvl			=	ConvertLVL(*levelOverride.Level);
					bHaveLVL	=	true;
				}

				int iStartAt	=	0;
				bool fStartAt	=	false;

				if (levelOverride.StartOverride.is_init())
				{
					iStartAt	=	*levelOverride.StartOverride;
					fStartAt	=	true;
				}

				rgLfoLvl.push_back( Docx2Doc::LFOLVL(iStartAt, *levelOverride.Ilvl, fStartAt, Docx2Doc::grfhic(), bHaveLVL ? &lvl : NULL));
			}

			int NumId = idLsidMap[oXmlNum.AbstractNumId];

			lfos.push_back(Docx2Doc::LFO(NumId, rgLfoLvl.size(), Docx2Doc::Constants::lfoFieldNotUsed00, Docx2Doc::grfhic()));
			lfoDatas.push_back(Docx2Doc::LFOData(0xFFFFFFFF, rgLfoLvl));
		}

		return Docx2Doc::PlfLfo(lfos, lfoDatas);
	}

	const Docx2Doc::Xst CFileTransformer::ConvertLvlText (const std::string& strLvlText, Docx2Doc::Constants::MSONFC oMsoNfc)
	{
		std::wstring wstr(strLvlText.size(), 0);
		utf8_decode(strLvlText.begin(), strLvlText.end(), wstr.begin());

		if (wstr == std::wstring(L"%1"))
			return Docx2Doc::Xst(true);

		std::wstring::iterator result = wstr.begin();
		std::wstring::iterator newResult = wstr.begin();

		newResult = find( wstr.begin(), wstr.end(), _T( '%' ) );
		std::wstring docPlaceHolderValue = std::wstring( wstr.begin(), newResult );
		result = newResult;

		while (result != wstr.end())
		{
			newResult	=	find( ( result + 1 ), wstr.end(), _T( '%' ) );
			if(result + 1 != wstr.end() && result + 2 != wstr.end())
			{
				std::wstring placeHolderString = std::wstring( ( result + 1 ), ( result + 2 ) );
				int placeHolderValue = _wtoi( placeHolderString.c_str() );
				docPlaceHolderValue += ( placeHolderValue - 1 );
				docPlaceHolderValue += std::wstring( ( result + 2 ), newResult );
			}

			result		=	newResult;
		}

		unsigned short cch = docPlaceHolderValue.size();
		if (Docx2Doc::Constants::msonfcBullet == oMsoNfc)
			cch = 0x0001;

		return Docx2Doc::Xst(docPlaceHolderValue.c_str(), cch);
	}

	int CFileTransformer::FindAbstractNumIdWithStyleRef (const OOX::Numbering& oXmlNumbering, const std::string& refLink)	
	{
		const OOX::Styles::Style& oStyle = inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetStyleById(refLink);
		if (oStyle.ParagraphProperty.is_init())
		{
			if (oStyle.ParagraphProperty->NumPr.is_init())
			{
				if (oStyle.ParagraphProperty->NumPr->NumId.is_init())
				{
					int nInd = oStyle.ParagraphProperty->NumPr->NumId;
					size_t length = oXmlNumbering.Nums->size();
					for (size_t i = 0; i < length; ++i)
					{
						if (nInd == oXmlNumbering.Nums->operator [](i).NumId)
						{
							return oXmlNumbering.Nums->operator [](i).AbstractNumId;
						}
					}
				}
			}
		}

		return -1;
	}
}

namespace DOCXTODOC	//	STYLES
{
	void CFileTransformer::ConvertStyleSheet (const OOX::Styles& oStyleSheet)
	{
		std::vector<Docx2Doc::LSD> mpstiilsd;

		//if ( _styleSheet.LattentStyles.is_init() )
		mpstiilsd = ConvertLatentStyles( /**_styleSheet.LattentStyles*/ );

		std::vector<Docx2Doc::LPStd> rglpstd = ConvertStyleDefinitions (*oStyleSheet.Named);

		short ftcAsci	= 0;
		short ftcFE		= 0;
		short ftcOther	= 0;

		if (oStyleSheet.Default->RunProperty->rFonts.is_init() )
		{
			if (oStyleSheet.Default->RunProperty->rFonts->ascii.is_init() )
				ftcAsci		=	m_mapFontTableMap [oStyleSheet.Default->RunProperty->rFonts->ascii];

			if (oStyleSheet.Default->RunProperty->rFonts->Cs.is_init() )
				ftcFE		=	m_mapFontTableMap [oStyleSheet.Default->RunProperty->rFonts->Cs];

			if (oStyleSheet.Default->RunProperty->rFonts->hAnsi.is_init() )
				ftcOther	=	m_mapFontTableMap [oStyleSheet.Default->RunProperty->rFonts->hAnsi];
		}

		Docx2Doc::Stshif stshif (rglpstd.size(), true, mpstiilsd.size(), ftcAsci, ftcFE, ftcOther);
		Docx2Doc::StshiLsd stshiLsd (mpstiilsd);

		// MUST be ignored.  
		Docx2Doc::LPStshiGrpPrl grpprlChpStandard (ConvertRunProperties(*oStyleSheet.Default->RunProperty));
		Docx2Doc::LPStshiGrpPrl grpprlPapStandard (ConvertParagraphProperties(*oStyleSheet.Default->ParagraphProperty));
		Docx2Doc::STSHIB stshib (grpprlChpStandard, grpprlPapStandard);

		Docx2Doc::LPStshi lpStshi (Docx2Doc::STSHI(stshif, 0, stshiLsd, stshib));

		m_pDOCFile->SetStyleSheet (Docx2Doc::STSH(lpStshi, rglpstd));
	}

	std::vector<Docx2Doc::LPStd> CFileTransformer::ConvertStyleDefinitions (const std::vector<OOX::Styles::Style>& arrStyles)
	{
		std::vector<Docx2Doc::LPStd> styleDefinitions(15);
		short styleIndex = 15;

		for (size_t i = 0; i < arrStyles.size(); ++i)
		{
			const OOX::Styles::Style& oXmlStyle	=	arrStyles[i];

			unsigned short sti	=	predefinedStyleIDMap[*oXmlStyle.StyleId];
			short istd			=	DOCXDOCUTILS::StiToIstd ((short)sti);

			if ( istd == -1 )
				istd = styleIndex++;

			m_mapStyleSheetMap.insert(std::pair<std::string, short>(oXmlStyle.StyleId,istd));
		}

		for (size_t i = 0; i < arrStyles.size(); ++i)
		{
			const OOX::Styles::Style& oXmlStyle	=	arrStyles[i];
			unsigned short sti	=	predefinedStyleIDMap[*oXmlStyle.StyleId];
			short istd			=	DOCXDOCUTILS::StiToIstd ((short)sti);

			Docx2Doc::Constants::StyleType styleType;
			std::map<std::string, Docx2Doc::Constants::StyleType>::const_iterator findResult = styleTypeMap.find( *oXmlStyle.Type );
			if ( findResult != styleTypeMap.end() )
				styleType = findResult->second;
			else
				styleType = Docx2Doc::Constants::styleTypeCharacter;

			unsigned short istdBase = 0x0FFF;
			unsigned short istdNext = 0x0000;
			Docx2Doc::StdfPost2000 StdfPost2000OrNone;

			if ( oXmlStyle.BasedOn.is_init() )
			{
				istdBase = m_mapStyleSheetMap[*oXmlStyle.BasedOn];
			}

			if ( oXmlStyle.Next.is_init() )
			{
				istdNext = m_mapStyleSheetMap[*oXmlStyle.Next];  
			}

			if ( ( oXmlStyle.Link.is_init() ) && ( oXmlStyle.UiPriority.is_init() ) )
			{
				//!!!TODO: Revision!!!
				StdfPost2000OrNone = Docx2Doc::StdfPost2000( (unsigned short)m_mapStyleSheetMap[*oXmlStyle.Link], false, 0, (unsigned short)(*oXmlStyle.UiPriority) );
			}

			Docx2Doc::GRFSTD grfstd( false, false, false, false, false, *oXmlStyle.SemiHidden, false, *oXmlStyle.UnhideWhenUsed, *oXmlStyle.QFormat );
			Docx2Doc::StdfBase stdfBase( sti, styleType, istdBase, istdNext, grfstd );

			std::wstring styleName( ( oXmlStyle.name->size() ), 0 );
			utf8_decode( oXmlStyle.name->begin(), oXmlStyle.name->end(), styleName.begin() );

			Docx2Doc::LPUpxPapx lPUpxPapx;
			Docx2Doc::LPUpxChpx lPUpxChpx;
			Docx2Doc::LPUpxTapx lPUpxTapx;

			CXmlPropertyReader oXmlReader;

			if (oXmlStyle.ParagraphProperty.is_init())
				lPUpxPapx	=	Docx2Doc::LPUpxPapx (Docx2Doc::UpxPapx(istd, oXmlReader.GetParagraphStyleProperties (ConvertParagraphProperties(*oXmlStyle.ParagraphProperty)) ));

			if (oXmlStyle.RunProperty.is_init())
				lPUpxChpx	=	Docx2Doc::LPUpxChpx( Docx2Doc::UpxChpx (oXmlReader.GetRunStyleProperties( ConvertRunProperties(*oXmlStyle.RunProperty)) ));

			if (oXmlStyle.tblPr.is_init())
				lPUpxTapx	=	Docx2Doc::LPUpxTapx(Docx2Doc::UpxTapx(oXmlReader.GetTableStyleProperties( ConvertTableProperties(*oXmlStyle.tblPr)) ));

			Docx2Doc::GrLPUpxSw grLPUpxSw (styleType, lPUpxPapx, lPUpxChpx, lPUpxTapx);
			Docx2Doc::LPStd lPStd (Docx2Doc::STD(Docx2Doc::Stdf(stdfBase, &StdfPost2000OrNone),
				Docx2Doc::Xstz(Docx2Doc::Xst(styleName.c_str())), grLPUpxSw));
			if (-1 != istd)
			{
				styleDefinitions[istd]	=	lPStd; 
			}
			else
			{
				styleDefinitions.push_back( lPStd );
			}
		}

		return styleDefinitions;
	}

	std::vector<Docx2Doc::LSD> CFileTransformer::ConvertLatentStyles(/*const OOX::Styles::LattentStyles &latentStyles*/)
	{
		std::vector<Docx2Doc::LSD> latentStylesDatas;

		/*bool fLocked = ( latentStyles.DefLockedState == 0 ) ? ( false ) : ( true );

		std::vector<OOX::Styles::LsdException>::const_iterator iter = (*latentStyles.LsdExceptions).begin();
		std::vector<OOX::Styles::LsdException>::const_iterator end = (*latentStyles.LsdExceptions).end();

		for (;iter != end; ++iter)	//	(*iter)
		{			

		bool fSemiHidden = false;
		bool fUnhideWhenUsed = false;
		bool fQFormat = false;
		unsigned short iPriority = 0;

		if ( (*iter).SemiHidden.is_init() )
		{
		fSemiHidden = ( (*iter).SemiHidden == 0 ) ? ( false ) : ( true );
		}

		if ( (*iter).UnhideWhenUsed.is_init() )
		{
		fUnhideWhenUsed = ( (*iter).UnhideWhenUsed == 0 ) ? ( false ) : ( true );
		}

		if ( (*iter).QFormat.is_init() )
		{
		fQFormat = ( (*iter).QFormat == 0 ) ? ( false ) : ( true );
		}

		if ( (*iter).UiPriority.is_init() )
		{
		iPriority = (unsigned short)(*iter).UiPriority;
		}

		latentStylesDatas.push_back( Docx2Doc::LSD( fLocked, fSemiHidden, fUnhideWhenUsed, fQFormat, iPriority ) );
		}*/

		for ( unsigned int i = 0; i < ( sizeof(Docx2Doc::LatentStylesTemplate) / sizeof(Docx2Doc::LatentStylesTemplate[0]) ); i++ )
		{
			latentStylesDatas.push_back( Docx2Doc::LSD( Docx2Doc::LatentStylesTemplate[i] ) );
		}

		return latentStylesDatas;
	}


	std::string CFileTransformer::GetStyleID (const OOX::Logic::Paragraph& oXmlParagraph) 
	{
		std::string strStyleID;

		if (oXmlParagraph.Property.is_init() && oXmlParagraph.Property->PStyle.is_init())
		{
			strStyleID								=	(*oXmlParagraph.Property->PStyle);
		}
		else
		{
			const OOX::Styles::Style defaultStyle	=	inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetDefaultStyle ("paragraph");
			strStyleID								=	(*defaultStyle.StyleId);

			if (0 == strStyleID.length())
			{
				const OOX::Styles::Style oStyle		=	inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetStyleWithTypeAndName ("paragraph", "Normal");
				strStyleID							=	(*oStyle.StyleId);
			}
		}

		return strStyleID;
	}
}

namespace DOCXTODOC
{
	// настройки страниц документа
	Docx2Doc::SectionProperties CFileTransformer::ConvertSectionProperties (const OOX::Logic::SectorProperty& docxSectionProperties)
	{
		PrlList docSectionProperties;

		unsigned short SXaPage = *docxSectionProperties.PageSize->Width;
		unsigned short SYaPage = *docxSectionProperties.PageSize->Height;

		docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSXaPage, (BYTE*)&SXaPage ) );
		docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSYaPage, (BYTE*)&SYaPage ) );

		if ( docxSectionProperties.Type.is_init() )
		{
			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSBkc, (BYTE*)&(sectionBreakTypeMap[*docxSectionProperties.Type]) ) );
		}

		if ( docxSectionProperties.PageSize->Orient.is_init() )
		{
			BYTE SBOrientation = (BYTE)Docx2Doc::Constants::dmOrientPortrait;

			if ( *docxSectionProperties.PageSize->Orient == std::string( "portrait" ) )
			{
				SBOrientation = (BYTE)Docx2Doc::Constants::dmOrientPortrait;
			}
			else if ( *docxSectionProperties.PageSize->Orient == std::string( "landscape" ) )
			{
				SBOrientation = (BYTE)Docx2Doc::Constants::dmOrientLandscape;
			}

			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSBOrientation, (BYTE*)&SBOrientation ) );
		}

		unsigned short SDxaLeft = Docx2Doc::XAS_nonNeg( *docxSectionProperties.PageMargin->Left );
		unsigned short SDxaRight = Docx2Doc::XAS_nonNeg( *docxSectionProperties.PageMargin->Right );
		short SDyaTop = Docx2Doc::YAS( *docxSectionProperties.PageMargin->Top );
		short SDyaBottom = Docx2Doc::YAS( *docxSectionProperties.PageMargin->Bottom );

		docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDxaLeft, (BYTE*)&SDxaLeft ) );
		docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDxaRight, (BYTE*)&SDxaRight ) );
		docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDyaTop, (BYTE*)&SDyaTop ) );
		docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDyaBottom, (BYTE*)&SDyaBottom ) );

		if ( docxSectionProperties.PageMargin->Gutter.is_init() )
		{
			unsigned short SDzaGutter = (unsigned short)(*docxSectionProperties.PageMargin->Gutter);

			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDzaGutter, (BYTE*)&SDzaGutter ) );
		}

		if ( docxSectionProperties.PageMargin->Header.is_init() )
		{ 
			unsigned short SDyaHdrTop = Docx2Doc::YAS_nonNeg(*docxSectionProperties.PageMargin->Header);

			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDyaHdrTop, (BYTE*)&SDyaHdrTop ) );
		}

		if ( docxSectionProperties.PageMargin->Footer.is_init() )
		{ 
			unsigned short SDyaHdrBottom = Docx2Doc::YAS_nonNeg(*docxSectionProperties.PageMargin->Footer);

			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDyaHdrBottom, (BYTE*)&SDyaHdrBottom ) );
		}

		if ( docxSectionProperties.Columns.is_init() )
		{
			if ( docxSectionProperties.Columns->Num.is_init() )
			{
				unsigned short SCcolumns = ( *docxSectionProperties.Columns->Num - 1 );

				docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSCcolumns, (BYTE*)&SCcolumns ) );
			}

			if ( docxSectionProperties.Columns->Space.is_init() )
			{
				unsigned short SDxaColumns = (unsigned short)Docx2Doc::XAS_nonNeg( (unsigned short)(*docxSectionProperties.Columns->Space) );

				docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDxaColumns, (BYTE*)&SDxaColumns ) );
			}

			BYTE index = 0;

			size_t count = (*docxSectionProperties.Columns->Items).size();
			const std::vector<OOX::Logic::Column>& items = (*docxSectionProperties.Columns->Items);

			for (size_t i = 0; i < count; ++i)	
			{			
				Docx2Doc::SDxaColWidthOperand SDxaColWidth(index, Docx2Doc::XAS_nonNeg( (unsigned short)(*(items[i]).Width)));

				docSectionProperties.push_back( Docx2Doc::Prl((short)DocFileFormat::sprmSDxaColWidth, (BYTE*)SDxaColWidth));

				if (items[i].Space.is_init())
				{
					//TODO: 

					Docx2Doc::SDxaColSpacingOperand SDxaColSpacing( index, Docx2Doc::XAS_nonNeg( (unsigned short)(*items[i].Space) ) );

					docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDxaColSpacing, (BYTE*)SDxaColSpacing ) );
				}

				++index;
			}
		}

		if ( docxSectionProperties.DocumentGrid.is_init() )
		{
			if ( docxSectionProperties.DocumentGrid->LinePitch.is_init() )
			{
				short SDyaLinePitch = Docx2Doc::YAS( *docxSectionProperties.DocumentGrid->LinePitch );

				docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDyaLinePitch, (BYTE*)(&SDyaLinePitch) ) );
			}

			if ( docxSectionProperties.DocumentGrid->CharSpace.is_init() )
			{
				int SDxtCharSpace = *docxSectionProperties.DocumentGrid->CharSpace;

				docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSDxtCharSpace, (BYTE*)(&SDxtCharSpace) ) );
			}

			if ( docxSectionProperties.DocumentGrid->Type.is_init() )
			{
				unsigned short SClm = (unsigned short)Docx2Doc::Constants::clmUseDefault;

				if ( *docxSectionProperties.DocumentGrid->Type == std::string( "Default" ) )
				{
					SClm = (unsigned short)Docx2Doc::Constants::clmUseDefault;
				}
				else if ( *docxSectionProperties.DocumentGrid->Type == std::string( "linesAndChars" ) )
				{
					SClm = (unsigned short)Docx2Doc::Constants::clmCharsAndLines;
				}
				else if ( *docxSectionProperties.DocumentGrid->Type == std::string( "lines" ) )
				{
					SClm = (unsigned short)Docx2Doc::Constants::clmLinesOnly;
				}
				else if ( *docxSectionProperties.DocumentGrid->Type == std::string( "snapToChars" ) )
				{
					SClm = (unsigned short)Docx2Doc::Constants::clmEnforceGrid;
				}

				docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSClm, (BYTE*)(&SClm) ) );
			}
		}

		if ( docxSectionProperties.FootNoteProperty.is_init() )
		{
			unsigned short sNfcFtnRef = (unsigned short)(this->numFmtMap[docxSectionProperties.FootNoteProperty->NumFormat->Tostd::string()]);
			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSNfcFtnRef, (BYTE*)(&sNfcFtnRef) ) );

			unsigned short sNFtn = (unsigned short)(docxSectionProperties.FootNoteProperty->NumStart);
			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSNFtn, (BYTE*)(&sNFtn) ) );
		}

		if ( docxSectionProperties.EndNoteProperty.is_init() )
		{
			unsigned short sNfcEdnRef = (unsigned short)(this->numFmtMap[docxSectionProperties.EndNoteProperty->NumFormat->Tostd::string()]);
			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSNfcEdnRef, (BYTE*)(&sNfcEdnRef) ) );

			unsigned short sNEdn = (unsigned short)(docxSectionProperties.EndNoteProperty->NumStart);
			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSNEdn, (BYTE*)(&sNEdn) ) );
		}

		AddLineNumberingSettings (docxSectionProperties, docSectionProperties);		//	<w:lnNumType>

		if (*docxSectionProperties.TitlePage)
		{
			Bool8 SFTitlePage = ( ( *docxSectionProperties.TitlePage ) ? ( 1 ) : ( 0 ) );
			docSectionProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmSFTitlePage, &SFTitlePage ) );
		}

		Docx2Doc::Sepx sepx (docSectionProperties);
		Docx2Doc::SectionProperties oSectionProperties (sepx);

		for ( std::vector<OOX::Logic::HeaderReference>::const_iterator headerReferencesIter = docxSectionProperties.Headers->begin();
			headerReferencesIter != docxSectionProperties.Headers->end();
			++headerReferencesIter )
		{
			OOX::Header* pHeader = dynamic_cast<OOX::Header*>(inputFolder.find<OOX::Document>()[headerReferencesIter->rId].get()); 

			if (pHeader)
			{
				if ( headerReferencesIter->Type == "even" )
				{
					oSectionProperties.SetEvenPageHeader (ConvertHeader(*pHeader));  
				}
				else if ( headerReferencesIter->Type == "default" )
				{
					oSectionProperties.SetOddPageHeader (ConvertHeader(*pHeader));  
				}
				else if ( headerReferencesIter->Type == "first" )
				{
					oSectionProperties.SetFirstPageHeader (ConvertHeader(*pHeader));  
				}
			}
		}

		for ( std::vector<OOX::Logic::FooterReference>::const_iterator footerReferencesIter = docxSectionProperties.Footers->begin();
			footerReferencesIter != docxSectionProperties.Footers->end(); 
			++footerReferencesIter )
		{
			OOX::Footer* pFooter = dynamic_cast<OOX::Footer*>(inputFolder.find<OOX::Document>()[footerReferencesIter->rId].get());  
			if (pFooter)
			{
				if ( footerReferencesIter->Type == "even" )
				{
					oSectionProperties.SetEvenPageFooter (ConvertFooter(*pFooter));  
				}
				else if ( footerReferencesIter->Type == "default" )
				{
					oSectionProperties.SetOddPageFooter (ConvertFooter(*pFooter));  
				}
				else if ( footerReferencesIter->Type == "first" )
				{
					oSectionProperties.SetFirstPageFooter (ConvertFooter(*pFooter));  
				}
			}
		}

		return oSectionProperties;
	}

	bool CFileTransformer::AddLineNumberingSettings (const OOX::Logic::SectorProperty& oSection, PrlList& arrSettings)
	{
		//	Line Numbering Restart Setting

		if (oSection.LnNumType->countBy.is_init())
		{
			//	Line Number Increments to Display

			short countBy			=	(unsigned short)(oSection.LnNumType->countBy);
			arrSettings.push_back (Docx2Doc::Prl ((short)DocFileFormat::sprmSNLnnMod, (BYTE*)(&countBy) ) );

			unsigned short mode		=	1;	//
			if (oSection.LnNumType->restart.is_init())
			{
				if ("newPage" == oSection.LnNumType->restart)
					mode			=	0x00;	//	DocFileFormat::lncPerPage;

				if ("newSection" == oSection.LnNumType->restart)
					mode			=	0x01;	//	DocFileFormat::lncRestart;

				if ("continuous" == oSection.LnNumType->restart)
					mode			=	0x02;	//	DocFileFormat::lncContinue;
			}

			arrSettings.push_back (Docx2Doc::Prl ((short)DocFileFormat::sprmSLnc, (BYTE*)(&mode) ) );

			//	Line Numbering Starting Value

			unsigned short start	=	0;
			if (oSection.LnNumType->start.is_init())
				start				=	(unsigned short)(oSection.LnNumType->start);

			arrSettings.push_back (Docx2Doc::Prl ((short)DocFileFormat::sprmSLnnMin, (BYTE*)(&start) ) );

			return true;
		}

		return false;
	}

	// верхний колонтитул
	Docx2Doc::Header CFileTransformer::ConvertHeader (const OOX::Header& oXmlDOCXHeader)
	{
		m_oOArtBuilder.SetLocation (HEADER_DOCUMENT);

		Docx2Doc::Header oMSDocHeader;

		for (size_t i = 0; i < oXmlDOCXHeader.Items->size(); ++i)
		{
			const OOX::Logic::TextItem& oItem					=	oXmlDOCXHeader.Items->operator [](i);

			if (oItem.is<OOX::Logic::Paragraph>())
			{
				const OOX::Logic::Paragraph& oMSDocXParagraph	=	oItem.as<OOX::Logic::Paragraph>();
				if (ValidParagraph(oMSDocXParagraph))
				{
					Docx2Doc::Paragraph oMSDocParagraph	=	ConvertParagraph<OOX::Header>(oMSDocXParagraph);
					oMSDocHeader.AddTextItem (oMSDocParagraph);
				}
			}
			else if (oItem.is<OOX::Logic::Table>())
			{
				Docx2Doc::Table oMSDocTable				=	CreateTable<OOX::Header> (oItem.as<OOX::Logic::Table>());
				oMSDocHeader.AddTextItem (oMSDocTable);
			}
			else if (oItem.is<OOX::Logic::Sdt>())
			{
				const OOX::Logic::SdtContent& oStdC				=	oItem.as<OOX::Logic::Sdt>().Content;

				for (size_t j = 0; j < oStdC.Items->size(); ++j)
				{
					const OOX::Logic::TextItem& oStdItem		=	oStdC.Items->operator [](j);

					if (oStdItem.is<OOX::Logic::Paragraph>())
					{
						const OOX::Logic::Paragraph& oMSDocXParagraph	=	oStdItem.as<OOX::Logic::Paragraph>();
						if (ValidParagraph(oMSDocXParagraph))
						{
							Docx2Doc::Paragraph oMSDocParagraph	=	ConvertParagraph<OOX::Header>(oMSDocXParagraph);
							oMSDocHeader.AddTextItem (oMSDocParagraph);
						}
					}
					else if (oStdItem.is<OOX::Logic::Table>())
					{
						Docx2Doc::Table oMSDocTable		=	CreateTable<OOX::Header> (oStdItem.as<OOX::Logic::Table>());
						oMSDocHeader.AddTextItem (oMSDocTable);
					}
				}
			}
		}

		m_oOArtBuilder.SetLocation (MAIN_DOCUMENT);

#ifdef _DEBUG		
		// DOCXDOCUTILS::DebugStrPrint (_T("Header : "), oMSDocHeader.GetAllText());
#endif
		return oMSDocHeader;
	}

	// нижний колонтитул
	Docx2Doc::Footer CFileTransformer::ConvertFooter (const OOX::Footer& oXmlDOCXFooter)
	{
		m_oOArtBuilder.SetLocation (HEADER_DOCUMENT);

		Docx2Doc::Footer oMSDocFooter;

		for (size_t i = 0; i < oXmlDOCXFooter.Items->size(); ++i)
		{
			const OOX::Logic::TextItem& oItem					=	oXmlDOCXFooter.Items->operator [](i);

			if (oItem.is<OOX::Logic::Paragraph>())
			{
				const OOX::Logic::Paragraph& oMSDocXParagraph	=	oItem.as<OOX::Logic::Paragraph>();
				if (ValidParagraph(oMSDocXParagraph))
				{
					Docx2Doc::Paragraph oMSDocParagraph	=	ConvertParagraph<OOX::Footer>(oMSDocXParagraph);
					oMSDocFooter.AddTextItem (oMSDocParagraph);
				}
			}
			else if (oItem.is<OOX::Logic::Table>())
			{
				Docx2Doc::Table oMSDocTable				=	CreateTable<OOX::Footer> (oItem.as<OOX::Logic::Table>());
				oMSDocFooter.AddTextItem (oMSDocTable);
			}
			else if (oItem.is<OOX::Logic::Sdt>())
			{
				const OOX::Logic::SdtContent& oStdC				=	oItem.as<OOX::Logic::Sdt>().Content;

				for (size_t j = 0; j < oStdC.Items->size(); ++j)
				{
					const OOX::Logic::TextItem& oStdItem		=	oStdC.Items->operator [](j);

					if (oStdItem.is<OOX::Logic::Paragraph>())
					{
						const OOX::Logic::Paragraph& oMSDocXParagraph	=	oStdItem.as<OOX::Logic::Paragraph>();
						if (ValidParagraph(oMSDocXParagraph))
						{
							Docx2Doc::Paragraph oMSDocParagraph	=	ConvertParagraph<OOX::Footer>(oMSDocXParagraph);
							oMSDocFooter.AddTextItem (oMSDocParagraph);
						}
					}
					else if (oStdItem.is<OOX::Logic::Table>())
					{
						Docx2Doc::Table oMSDocTable		=	CreateTable<OOX::Footer> (oStdItem.as<OOX::Logic::Table>());
						oMSDocFooter.AddTextItem (oMSDocTable);
					}
				}
			}
		}

		m_oOArtBuilder.SetLocation (MAIN_DOCUMENT);

#ifdef _DEBUG		
		// DOCXDOCUTILS::DebugStrPrint (_T("Footer : "), oMSDocFooter.GetAllText());
#endif

		return oMSDocFooter;
	}
}

namespace DOCXTODOC	//	TABLE
{
	template<class T> Docx2Doc::Table CFileTransformer::CreateTable (const OOX::Logic::Table& oXmlTable)
	{
		static unsigned int tableDepth = 1;

		Docx2Doc::Table table;

		OOX::Styles::Style oTableStyle;
		if (oXmlTable.tblPr->Style.is_init())
		{			
			oTableStyle	= inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetStyleById(*oXmlTable.tblPr->Style);
		}

		DOCXDOCUTILS::CTblBorders oTblBorders (oXmlTable, oTableStyle);

		int nYC		=	(int)oXmlTable.Rows->size();
		for (int nY = 0; nY < nYC; ++nY)
		{
			const OOX::Logic::TableRow& oXmlTableRow = oXmlTable.Rows->operator [](nY);

			Docx2Doc::TableRow tableRow (tableDepth);

			std::vector<Docx2Doc::XAS> xass;
			std::vector<Docx2Doc::TC80> tc80s;

			unsigned int cellIndex = 0;

			int nXC		=	(int)oXmlTableRow.Cells->size();
			for (int nX = 0; nX < nXC; ++nX)
			{
				const OOX::Logic::TableCell& oXmlCell	=	oXmlTableRow.Cells->operator[](nX);

				Docx2Doc::TableCell tableCell(tableDepth);

				Docx2Doc::Constants::VerticalMergeFlag vmf = ConvertTableVerticalMergeFlag( oXmlCell.Properties->VMerge );

				oTblBorders.Append (nX, nY, nXC, nYC, oXmlTable.tblPr->tblBorders, oXmlCell.Properties->tblBorders);

				int nCellWidth	= (int)(*oXmlCell.Properties->Width->Width);
				if (0.0 == nCellWidth)
				{
					std::vector<OOX::Logic::GridColumn> columnes = *oXmlTable.tblGrid->Columns;
					if ((int)columnes.size () > nX)
					{
						nCellWidth = static_cast<int>(*(columnes[nX].Width));
					}
				}

				Docx2Doc::TC80 tc80( Docx2Doc::TCGRF(
					Docx2Doc::Constants::horzMergeNotMerged,
					Docx2Doc::Constants::grpfTFlrtb, vmf,
					Docx2Doc::Constants::vaTop,
					Docx2Doc::Constants::ftsDxa, false, false, false ),
					nCellWidth, 
					oTblBorders.GetTopNillBorder(), oTblBorders.GetLeftNillBorder(), oTblBorders.GetBottomNillBorder(),
					oTblBorders.GetRightNillBorder()); 				

				size_t count = (*oXmlCell.Items).size();
				const std::vector<OOX::Logic::TextItem>& items = (*oXmlCell.Items);

				for (size_t i = 0; i < count; ++i)	
				{		
					if (items[i].is<OOX::Logic::Paragraph>())
					{
						const OOX::Logic::Paragraph& oDocxParagraph		=	items[i].as<OOX::Logic::Paragraph>();
						Docx2Doc::Paragraph oDocParagraph		=	ConvertParagraph<T>(oDocxParagraph);
						tableCell.AddTextItem (oDocParagraph);

						//Docx2Doc::Paragraph oDocParagraph;	//	 ONLY FOR TEST
						//tableCell.AddTextItem (oDocParagraph);		//	 ONLY FOR TEST
					}
					else if (items[i].is<OOX::Logic::Table>())
					{
						tableDepth++;
						Docx2Doc::Table docTable = CreateTable<T>(items[i].as<OOX::Logic::Table>());
						tableDepth--;
						tableCell.AddTextItem(docTable);
					}
				}				

				tc80s.push_back(tc80);

				tableRow.AddCell(tableCell);
				++cellIndex;
			}

			xass = BuildXASs( oXmlTable, *oXmlTableRow.Cells );

			Docx2Doc::TDefTableOperand tdto( oXmlTableRow.Cells->size(), xass, tc80s );

			tableRow.AddProperty( (short)DocFileFormat::sprmTDefTable, tdto );

			tableRow.AddProperties(ConvertTableProperties(*oXmlTable.tblPr, oXmlTableRow.Cells->size()));

			if (oXmlTableRow.Properties.is_init())
			{
				tableRow.AddProperties(ConvertTableRowProperties(nY,*oXmlTableRow.Properties ) );
			}

			const std::vector<Docx2Doc::TableBrcOperand>& oBrcs		=	oTblBorders.GetSpecificationBorders ();
			const std::vector<Docx2Doc::TableBrc80Operand>& oBrc80s	=	oTblBorders.GetDescriptBorders ();
			for (size_t i = 0; i < oBrc80s.size(); ++i)
			{
				tableRow.AddProperty( (short)DocFileFormat::sprmTSetBrc80, oBrc80s[i] );
				tableRow.AddProperty( (short)DocFileFormat::sprmTSetBrc, oBrcs[i] );
			}

			tableRow.AddProperties(ConvertTableRowCellsProperties(oXmlTable, nY, nYC, *oXmlTableRow.Cells,oTableStyle));

			table.AddRow(tableRow);

			oTblBorders.Clean ();
		}

		return table;
	}

	PrlList CFileTransformer::ConvertTableProperties (const OOX::Logic::TableProperty& docxTableProperties, unsigned int cellsCount) 
	{
		PrlList docTableProperties;

		DOCXDOCUTILS::CTblBorders oBorder;

		Docx2Doc::TableBordersOperand80 tableBordersOperand80;
		Docx2Doc::TableBordersOperand tableBordersOperand;

		if ( docxTableProperties.Style.is_init() )
		{
			docTableProperties = GetTablePropertiesFromStyleHierarchy( docxTableProperties.Style );

			short istd = m_mapStyleSheetMap[*docxTableProperties.Style];
			docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTIstd, (byte*)(&istd) ) );

			if ( istd < (short)m_pDOCFile->GetStyleSheet().Count() )
			{
				PrlList styleTableProperties = m_pDOCFile->GetStyleSheet()[istd].GetProperties();

				for (PrlList::const_iterator iter = styleTableProperties.begin(); iter != styleTableProperties.end(); ++iter)
				{
					docTableProperties.push_back( *iter );

					switch ( iter->GetSprmCode() )
					{
					case ( (unsigned short)DocFileFormat::sprmTTableBorders80 ):
						{
							tableBordersOperand80 = Docx2Doc::TableBordersOperand80( *iter );
						}
						break;

					case ( (unsigned short)DocFileFormat::sprmTTableBorders ):
						{
							tableBordersOperand = Docx2Doc::TableBordersOperand( *iter );
						}
						break;
					}
				}
			}
		}

		if ( docxTableProperties.Look.is_init() )
		{
			Docx2Doc::TLP tlp( Docx2Doc::Constants::itlNone, Docx2Doc::Fatl( HexString2Int( *docxTableProperties.Look ) ) );

			docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTTlp, tlp ) );
		}

		if ( docxTableProperties.Width.is_init() )
		{
			Docx2Doc::FtsWWidth_Table ftsWWidth_Table (DOCXDOCUTILS::TableWidthUnitsFromString (*docxTableProperties.Width->Type),*docxTableProperties.Width->Width );
			docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTTableWidth, ftsWWidth_Table ) );
		}

		BYTE bAutoFit = 0x01;
		if ( docxTableProperties.Layout.is_init() && docxTableProperties.Layout == "fixed")
			bAutoFit = 0x00;
		docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTFAutofit, (BYTE*)&bAutoFit ) );

		if ( docxTableProperties.Ind.is_init() )
		{
			Docx2Doc::FtsWWidth_Indent tWidthIndent (DOCXDOCUTILS::TableWidthUnitsFromString (docxTableProperties.Ind->Type), (short)docxTableProperties.Ind->Width);
			docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTWidthIndent, (BYTE*)tWidthIndent ) );
		}

		std::map<std::string, BYTE>& oBrcMap	=	oBorder.GetBrcMap ();

		if (docxTableProperties.tblBorders.is_init())
		{
			if (docxTableProperties.tblBorders->top.is_init())
			{
				Docx2Doc::Brc80MayBeNil Brc80MayBeNilTop =  Docx2Doc::Brc80MayBeNil( docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Sz.get_value_or_default(),
					oBrcMap[docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Value],
					DOCXDOCUTILS::ColorToIco (docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Color.get_value_or_default()), 
					docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand80.SetTopBorder(Brc80MayBeNilTop);

				std::string strColor	=	docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Color.get_value_or_default().Tostd::string();
				if (std::string("auto") == strColor)
					strColor			=	std::string ("000000");

				Docx2Doc::Brc brcTop = Docx2Doc::Brc(Docx2Doc::COLORREF(HexString2Int(strColor)),
					docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Sz.get_value_or_default(), 
					oBrcMap[docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Value], 
					docxTableProperties.tblBorders->top.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand.SetTopBorder(brcTop);
			}

			if ( docxTableProperties.tblBorders->bottom.is_init() )
			{
				Docx2Doc::Brc80MayBeNil Brc80MayBeNilBottom = Docx2Doc::Brc80MayBeNil( docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Sz.get_value_or_default(),
					oBrcMap[docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Color.get_value_or_default()), 
					docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand80.SetBottomBorder(Brc80MayBeNilBottom);

				std::string strColor	=	docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Color.get_value_or_default().Tostd::string();
				if (std::string("auto") == strColor)
					strColor			=	std::string ("000000");

				Docx2Doc::Brc brcBottom = Docx2Doc::Brc(Docx2Doc::COLORREF(HexString2Int(strColor)),
					docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Sz.get_value_or_default(), 
					oBrcMap[docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Value], 
					docxTableProperties.tblBorders->bottom.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand.SetBottomBorder( brcBottom );
			}

			if ( docxTableProperties.tblBorders->left.is_init() )
			{
				Docx2Doc::Brc80MayBeNil Brc80MayBeNilLeft = Docx2Doc::Brc80MayBeNil( docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Sz.get_value_or_default(),
					oBrcMap[docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Color.get_value_or_default()), 
					docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand80.SetLeftBorder( Brc80MayBeNilLeft );

				std::string strColor	=	docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Color.get_value_or_default().Tostd::string();
				if (std::string("auto") == strColor)
					strColor			=	std::string ("000000");

				Docx2Doc::Brc brcLeft = Docx2Doc::Brc( Docx2Doc::COLORREF(HexString2Int(strColor)),
					docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Sz.get_value_or_default(), 
					oBrcMap[docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Value], 
					docxTableProperties.tblBorders->left.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand.SetLeftBorder( brcLeft );
			}

			if ( docxTableProperties.tblBorders->right.is_init() )
			{
				Docx2Doc::Brc80MayBeNil Brc80MayBeNilRight = Docx2Doc::Brc80MayBeNil( docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Sz.get_value_or_default(),
					oBrcMap[docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Color.get_value_or_default()), 
					docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand80.SetRightBorder( Brc80MayBeNilRight );

				std::string strColor	=	docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Color.get_value_or_default().Tostd::string();
				if (std::string("auto") == strColor)
					strColor			=	std::string ("000000");

				Docx2Doc::Brc brcRight = Docx2Doc::Brc( Docx2Doc::COLORREF(HexString2Int(strColor)),
					docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Sz.get_value_or_default(), 
					oBrcMap[docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Value], 
					docxTableProperties.tblBorders->right.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand.SetRightBorder( brcRight );
			}

			if ( docxTableProperties.tblBorders->insideH.is_init() )
			{
				Docx2Doc::Brc80MayBeNil Brc80MayBeNilInsideH = Docx2Doc::Brc80MayBeNil( docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Sz.get_value_or_default(),
					oBrcMap[docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Color.get_value_or_default()), 
					docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand80.SetHorizontalInsideBorder( Brc80MayBeNilInsideH );

				std::string strColor	=	docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Color.get_value_or_default().Tostd::string();
				if (std::string("auto") == strColor)
					strColor			=	std::string ("000000");

				Docx2Doc::Brc brcInsideH = Docx2Doc::Brc( Docx2Doc::COLORREF(HexString2Int(strColor)),
					docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Sz.get_value_or_default(), 
					oBrcMap[docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Value], 
					docxTableProperties.tblBorders->insideH.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand.SetHorizontalInsideBorder( brcInsideH );
			}

			if ( docxTableProperties.tblBorders->insideV.is_init() )
			{
				Docx2Doc::Brc80MayBeNil Brc80MayBeNilInsideV = Docx2Doc::Brc80MayBeNil( docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Sz.get_value_or_default(),
					oBrcMap[docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Value], 
					DOCXDOCUTILS::ColorToIco (docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Color.get_value_or_default()), 
					docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand80.SetVerticalInsideBorder( Brc80MayBeNilInsideV );

				std::string strColor	=	docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Color.get_value_or_default().Tostd::string();
				if (std::string("auto") == strColor)
					strColor			=	std::string ("000000");

				Docx2Doc::Brc brcInsideV = Docx2Doc::Brc( Docx2Doc::COLORREF( HexString2Int(strColor) ),
					docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Sz.get_value_or_default(), 
					oBrcMap[docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Value], 
					docxTableProperties.tblBorders->insideV.get_value_or_default().Bdr->Space.get_value_or_default(), 
					false, 
					false );

				tableBordersOperand.SetVerticalInsideBorder( brcInsideV );
			}

			docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTTableBorders80, (BYTE*)tableBordersOperand80 ) );
			docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTTableBorders, (BYTE*)tableBordersOperand ) );
		}

		if ( docxTableProperties.CellMar.is_init() )
		{
			if ( docxTableProperties.CellMar->Top.is_init() )
			{
				Docx2Doc::CSSAOperand cssaOperandTop( Docx2Doc::CSSA( Docx2Doc::ItcFirstLim( 0, cellsCount ),
					Docx2Doc::Constants::fbrcTop,
					DOCXDOCUTILS::TableWidthUnitsFromString (docxTableProperties.CellMar->Top->Margin->Type),
					docxTableProperties.CellMar->Top->Margin->W ) );

				docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)cssaOperandTop ) );
			}

			if ( docxTableProperties.CellMar->Left.is_init() )
			{
				Docx2Doc::CSSAOperand cssaOperandLeft( Docx2Doc::CSSA( Docx2Doc::ItcFirstLim( 0, cellsCount ),
					Docx2Doc::Constants::fbrcLeft,
					DOCXDOCUTILS::TableWidthUnitsFromString (docxTableProperties.CellMar->Left->Margin->Type),
					docxTableProperties.CellMar->Left->Margin->W ) );

				docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)cssaOperandLeft ) );
			}

			if ( docxTableProperties.CellMar->Bottom.is_init() )
			{
				Docx2Doc::CSSAOperand cssaOperandBottom( Docx2Doc::CSSA( Docx2Doc::ItcFirstLim( 0, cellsCount ),
					Docx2Doc::Constants::fbrcBottom,
					DOCXDOCUTILS::TableWidthUnitsFromString (docxTableProperties.CellMar->Bottom->Margin->Type),
					docxTableProperties.CellMar->Bottom->Margin->W ) );

				docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)cssaOperandBottom ) );
			}

			if ( docxTableProperties.CellMar->Right.is_init() )
			{
				Docx2Doc::CSSAOperand cssaOperandRight( Docx2Doc::CSSA( Docx2Doc::ItcFirstLim( 0, cellsCount ),
					Docx2Doc::Constants::fbrcRight,
					DOCXDOCUTILS::TableWidthUnitsFromString (docxTableProperties.CellMar->Right->Margin->Type),
					docxTableProperties.CellMar->Right->Margin->W ) );

				docTableProperties.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTCellPadding, (BYTE*)cssaOperandRight ) );
			}
		}

		return docTableProperties;
	}

	std::vector<Docx2Doc::XAS> CFileTransformer::BuildXASs(const OOX::Logic::Table& oXmlTable, const std::vector<OOX::Logic::TableCell>& tableCells)
	{
		std::vector<Docx2Doc::XAS> resultXASs;

		resultXASs.push_back( Docx2Doc::XAS( 0 ) ); //!!!TODO!!!

		int nSpanLineOff	=	0;

		for (size_t i = 0; i < tableCells.size(); ++i)
		{
			const OOX::Logic::TableCell& oXmlTblCell	=	tableCells[i];

			//Если ширина 0, то выставляем ширину gc_nZeroWidth, как это делаем word когда к пустой таблице применяется автоподбор по содержимому
			int nCellWidth = (int)(*oXmlTblCell.Properties->Width->Width);
			if (nCellWidth <= 0)
			{
				int nColInd	=	nSpanLineOff + i;
				std::vector<OOX::Logic::GridColumn> oXmlColumnes = (*oXmlTable.tblGrid->Columns);
				if ((int)oXmlColumnes.size() > nColInd)
				{
					nCellWidth	=	static_cast<int>(*(oXmlColumnes[nColInd].Width));
				}
				else
				{
					nCellWidth	=	AVSDocFormatUtils::gc_nZeroWidth;
				}
			}

			if (oXmlTblCell.Properties->GridSpan.is_init())
			{
				std::vector<OOX::Logic::GridColumn> oXmlColumnes = (*oXmlTable.tblGrid->Columns);

				int nColsSize	=	(int)oXmlColumnes.size();
				int nXmlSpan	=	oXmlTblCell.Properties->GridSpan;
				int nToMerge	=	std::min(nXmlSpan + (int)i + nSpanLineOff,nColsSize);

				nCellWidth		=	0;

				for (int j = i + nSpanLineOff; j < nToMerge; ++j)
				{
					nCellWidth += static_cast<int>(*(oXmlColumnes[j].Width));
				}

				if (nCellWidth <= 0)
					nCellWidth	=	AVSDocFormatUtils::gc_nZeroWidth;

				//if (0 == nSpanLineOff)
				--nXmlSpan;

				nSpanLineOff	+=	nXmlSpan;
			}

			resultXASs.push_back(Docx2Doc::XAS(nCellWidth + resultXASs.back()));
		}

		return resultXASs;
	}

	//
	const PrlList CFileTransformer::ConvertTableRowProperties (int nY, const OOX::Logic::TableRowProperties& oXmlRow) 
	{
		PrlList oPrls;

		short tableRowHeight = 0;

		if ( oXmlRow.Height->Type.is_init() && ( *oXmlRow.Height->Type ==  "exact" ) )
		{
			tableRowHeight = Docx2Doc::YAS( *oXmlRow.Height->Height * ( -1 ) );
		}
		else
		{
			tableRowHeight = Docx2Doc::YAS( *oXmlRow.Height->Height );
		}

		oPrls.push_back(Docx2Doc::Prl( (short)DocFileFormat::sprmTDyaRowHeight, (BYTE*)(&tableRowHeight)));

		return oPrls;
	}

	const PrlList CFileTransformer::ConvertTableRowCellsProperties (const OOX::Logic::Table& oXmlTable, int nY, int nCY, const std::vector<OOX::Logic::TableCell>& arrXmlCells, const OOX::Styles::Style& oStyle)
	{
		PrlList arCellsPrls;

		DOCXDOCUTILS::CTblFill oTblFill (oXmlTable, oStyle);

		int nCX = arrXmlCells.size();

		for (int nX = 0; nX < nCX; ++nX)
		{
			const OOX::Logic::TableCell& oXmlCell	=	arrXmlCells[nX];

			oTblFill.AddCell (nX, nY, nCX-1, nCY-1, oXmlCell.Properties->Shading);

			Docx2Doc::TableCellWidthOperand tableCellWidthOperand( Docx2Doc::ItcFirstLim( nX, ( nX + 1 ) ), Docx2Doc::FtsWWidth_TablePart( tableCellWidthMap[*oXmlCell.Properties->Width->Type], (unsigned short)(*oXmlCell.Properties->Width->Width) ) );
			arCellsPrls.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTCellWidth, tableCellWidthOperand ) );

			if(oXmlCell.Properties->CellMar.is_init())
			{
				const OOX::Logic::TCMar& oTCMar	= oXmlCell.Properties->CellMar;
				if (oTCMar.Top.is_init())
					arCellsPrls.push_back (DOCXDOCUTILS::GetOpTop(oTCMar, nCX));

				if (oTCMar.Left.is_init())
					arCellsPrls.push_back (DOCXDOCUTILS::GetOpLeft(oTCMar, nCX));

				if (oTCMar.Right.is_init())
					arCellsPrls.push_back (DOCXDOCUTILS::GetOpRight(oTCMar, nCX));

				if (oTCMar.Bottom.is_init())
					arCellsPrls.push_back (DOCXDOCUTILS::GetOpBottom(oTCMar, nCX));
			}

			if ( oXmlCell.Properties->VAlign.is_init() )
			{
				Docx2Doc::Constants::VerticalAlign verticalAlign = Docx2Doc::Constants::vaTop;

				if ( *oXmlCell.Properties->VAlign == "top" )
				{
					verticalAlign = Docx2Doc::Constants::vaTop;
				}
				else if ( *oXmlCell.Properties->VAlign == "center" )
				{
					verticalAlign = Docx2Doc::Constants::vaCenter;
				}
				else if ( *oXmlCell.Properties->VAlign == "bottom" )
				{
					verticalAlign = Docx2Doc::Constants::vaBottom;
				}

				Docx2Doc::CellRangeVertAlign cellRangeVertAlign( Docx2Doc::ItcFirstLim( nX, ( nX + 1 ) ), verticalAlign );

				arCellsPrls.push_back( Docx2Doc::Prl( (short)DocFileFormat::sprmTVertAlign, cellRangeVertAlign ) );
			}
		}

		if (oTblFill.GetShd22().size())
		{
			Docx2Doc::DefTableShdOperand defOperand(oTblFill.GetShd22());

			arCellsPrls.push_back(Docx2Doc::Prl((short)DocFileFormat::sprmTDefTableShd,	defOperand));
			arCellsPrls.push_back(Docx2Doc::Prl((short)DocFileFormat::sprmTDefTableShdRaw, defOperand));
		}

		if (oTblFill.GetShd44().size())
		{
			Docx2Doc::DefTableShdOperand defOperand(oTblFill.GetShd44());

			arCellsPrls.push_back(Docx2Doc::Prl((short)DocFileFormat::sprmTDefTableShd,	defOperand));
			arCellsPrls.push_back(Docx2Doc::Prl((short)DocFileFormat::sprmTDefTableShdRaw, defOperand));
		}

		if (oTblFill.GetShd63().size())
		{
			Docx2Doc::DefTableShdOperand defOperand(oTblFill.GetShd63());

			arCellsPrls.push_back(Docx2Doc::Prl((short)DocFileFormat::sprmTDefTableShd,	defOperand));
			arCellsPrls.push_back(Docx2Doc::Prl((short)DocFileFormat::sprmTDefTableShdRaw, defOperand));
		}

		return arCellsPrls;
	}
}

namespace DOCXTODOC	//	FONTS
{
	void CFileTransformer::AddInternalFont (const std::wstring& strFontName)
	{	
		// шрифт может не содержаться в таблице шрифтов, а определен прямо по ходу текста

		std::map<std::wstring, short>::const_iterator findResult = m_mapFontTableMap.find(strFontName);
		if (findResult == m_mapFontTableMap.end())
		{
			m_mapFontTableMap.insert(std::pair<std::wstring, short>(strFontName, m_mapFontTableMap.size()));

			m_arrInternalFonts.push_back (strFontName);
		}
	}

	void CFileTransformer::ConvertFontTable (const OOX::FontTable& oXmlFontTable)
	{
		std::vector<Docx2Doc::FFN> ffns;

		for (size_t i = 0; i < oXmlFontTable.Fonts->size(); ++i)
		{
			const OOX::FontTable::Font& oXmlFont = oXmlFontTable.Fonts->operator [](i);

			Docx2Doc::FFID ffid (DOCXDOCUTILS::FontPitchFromString (*oXmlFont.Pitch), true,	DOCXDOCUTILS::FontFamilyFromString (*oXmlFont.Family));

			//!!!TODO!!!
			short wWeight = 400;

			FONTSIGNATURE fs;

			fs.fsCsb[0] = HexString2Int( oXmlFont.Csb0.get_value_or_default() );
			fs.fsCsb[1] = HexString2Int( oXmlFont.Csb1.get_value_or_default() );
			fs.fsUsb[0] = HexString2Int( oXmlFont.Usb0.get_value_or_default() );
			fs.fsUsb[1] = HexString2Int( oXmlFont.Usb1.get_value_or_default() );
			fs.fsUsb[2] = HexString2Int( oXmlFont.Usb2.get_value_or_default() );
			fs.fsUsb[3] = HexString2Int( oXmlFont.Usb3.get_value_or_default() );

			std::wstring strFontName;

			FormatUtils::GetSTLCollectionFromBytes<std::wstring>(&strFontName, (BYTE*)((*oXmlFont.Name).c_str()), (*oXmlFont.Name).size(), ENCODING_WINDOWS_1251);

			Docx2Doc::FFN ffn (ffid, wWeight,
				DOCXDOCUTILS::FontCharsetFromString (oXmlFont.Charset.get_value_or_default()),
				ConvertPanose(oXmlFont.Panose1.get_value_or_default()), fs, strFontName);

			ffns.push_back(ffn);
		}

		for (size_t i = 0; i < m_arrInternalFonts.size(); ++i)
		{
			Docx2Doc::FFID ffid (DOCXDOCUTILS::FontPitchFromString (std::string("")), true,	DOCXDOCUTILS::FontFamilyFromString (std::string("auto")));

			//!!!TODO!!!
			short wWeight = 400;

			FONTSIGNATURE fs;

			fs.fsCsb[0] = 0;
			fs.fsCsb[1] = 0;
			fs.fsUsb[0] = 0;
			fs.fsUsb[1] = 0;
			fs.fsUsb[2] = 0;
			fs.fsUsb[3] = 0;

			std::wstring strFontName;

			FormatUtils::GetSTLCollectionFromBytes<std::wstring>(&strFontName, (BYTE*)(m_arrInternalFonts[i].c_str()), m_arrInternalFonts[i].size(), ENCODING_WINDOWS_1251);

			Docx2Doc::FFN ffn (ffid, wWeight,
				DOCXDOCUTILS::FontCharsetFromString (std::string("")),
				ConvertPanose(std::string("")), fs, strFontName);

			ffns.push_back(ffn);
		}

		m_pDOCFile->SetFontTable(Docx2Doc::STTB<Docx2Doc::FFN>(false, &ffns));
	}

	Docx2Doc::PANOSE CFileTransformer::ConvertPanose (const std::string& strPanose)
	{
		if (20 == strPanose.size())
		{
			BYTE bFamilyType		=	HexString2Int ( std::string( ( strPanose.begin() ),			( strPanose.begin() + 2 ) ) );
			BYTE bSerifStyle		=	HexString2Int ( std::string( ( strPanose.begin() + 2 ),		( strPanose.begin() + 4 ) ) );
			BYTE bWeight			=	HexString2Int ( std::string( ( strPanose.begin() + 4 ),		( strPanose.begin() + 6 ) ) );
			BYTE bProportion		=	HexString2Int ( std::string( ( strPanose.begin() + 6 ),		( strPanose.begin() + 8 ) ) );
			BYTE bContrast			=	HexString2Int ( std::string( ( strPanose.begin() + 8 ),		( strPanose.begin() + 10 ) ) );
			BYTE bStrokeVariation	=	HexString2Int ( std::string( ( strPanose.begin() + 10 ),	( strPanose.begin() + 12 ) ) );
			BYTE bArmStyle			=	HexString2Int ( std::string( ( strPanose.begin() + 12 ),	( strPanose.begin() + 14 ) ) );
			BYTE bLetterform		=	HexString2Int ( std::string( ( strPanose.begin() + 14 ),	( strPanose.begin() + 16 ) ) );
			BYTE bMidline			=	HexString2Int ( std::string( ( strPanose.begin() + 16 ),	( strPanose.begin() + 18 ) ) );
			BYTE bHeight			=	HexString2Int ( std::string( ( strPanose.begin() + 18 ),	( strPanose.end() ) ) );

			return Docx2Doc::PANOSE (bFamilyType, bSerifStyle, bWeight, bProportion, bContrast,	bStrokeVariation, bArmStyle, bLetterform, bMidline, bHeight);
		}

		return Docx2Doc::PANOSE();
	}
}

namespace DOCXTODOC // run rule transform
{
	template<class T> Docx2Doc::Run CFileTransformer::ConvertRun (const OOX::Logic::Run& oXml, const PrlList& styleDocRunProperties, std::wstring& strRunType)
	{
		Docx2Doc::Run oBinRun;
		for (std::vector<OOX::Logic::RunItem>::const_iterator iter = oXml.Items->begin(); iter != oXml.Items->end(); ++iter)
		{
			if (iter->is<OOX::Logic::Break>())
				BreakXmlRunTransform<T>(iter->as<OOX::Logic::Break>(),oBinRun);
			else if (iter->is<OOX::Logic::Tab>())
				TabXmlRunTransform<T>(iter->as<OOX::Logic::Tab>(),oBinRun);
			else if (iter->is<OOX::Logic::FootnoteReference>())
				FootnoteReferenceXmlRunTransform<T>(iter->as<OOX::Logic::FootnoteReference>(),oBinRun);
			else if (iter->is<OOX::Logic::FootnoteRef>())
				FootnoteRefXmlRunTransform<T>(iter->as<OOX::Logic::FootnoteRef>(),oBinRun);
			else if (iter->is<OOX::Logic::EndnoteReference>())
				EndnoteReferenceXmlRunTransform<T>(iter->as<OOX::Logic::EndnoteReference>(),oBinRun);
			else if (iter->is<OOX::Logic::EndnoteRef>())
				EndnoteRefXmlRunTransform<T>(iter->as<OOX::Logic::EndnoteRef>(),oBinRun);
			else if (iter->is<OOX::Logic::Text>())
				TextXmlRunTransform<T>(iter->as<OOX::Logic::Text>(),oBinRun);
			else if (iter->is<OOX::Logic::FldChar>())
				FldCharXmlRunTransform <T>(iter->as<OOX::Logic::FldChar>(),oBinRun,strRunType);
			else if (iter->is<OOX::Logic::InstrText>())
				InstrTextXmlRunTransform <T>(iter->as<OOX::Logic::InstrText>(),oBinRun,strRunType);
			else if (iter->is<OOX::Logic::Drawing>())
				DrawingXmlRunTransform<T>(iter->as<OOX::Logic::Drawing>(),oBinRun);
			else if (iter->is<OOX::Logic::Pict>())
				PictXmlRunTransform<T>(iter->as<OOX::Logic::Pict>(),oBinRun);
			//else if (iter->is<OOX::Logic::Symbol>())
			//	SymbolXmlRunTransform<T>(iter->as<OOX::Logic::Symbol>(),oBinRun);
			else if (iter->is<OOX::Logic::DelText>())
				DelTextXmlRunTransform<T>(iter->as<OOX::Logic::DelText>(),oBinRun);
			else if (iter->is<OOX::Logic::NullRun>())
			{
				/// TODO 
			}
		}

		oBinRun.AddProperties(ConvertRunProperties(inputFolder.find<OOX::Document>().find<OOX::CStyles>().Default->RunProperty));

		if (oXml.Property.is_init())
		{
			if (oXml.Property->RStyle.is_init())
			{
				//!!!TODO!!!  
				//short istd = m_mapStyleSheetMap[*oXml.Property->RStyle];
				//oBinRun.AddProperty( Docx2Doc::Prl( (short)DocFileFormat::sprmCIstd, (byte*)&istd ) );

				PrlList styleDocRunProperties = GetRunPropertiesFromStyleHierarchy(*oXml.Property->RStyle);
				oBinRun.AddOrReplaceProperties( styleDocRunProperties );
			}
			else
			{
				const OOX::Styles::Style defaultStyle = inputFolder.find<OOX::Document>().find<OOX::CStyles>().GetDefaultStyle("character");
				oBinRun.AddOrReplaceProperties (GetRunPropertiesFromStyleHierarchy(*defaultStyle.StyleId));
			}
		}

		oBinRun.AddOrReplaceProperties(styleDocRunProperties);

		if (oXml.Property.is_init())
		{
			oBinRun.AddOrReplaceProperties(ConvertRunProperties(*oXml.Property));
		}

		return oBinRun;
	}

	//
	template<class T> int CFileTransformer::FldCharXmlRunTransform (const OOX::Logic::FldChar& oXml, Docx2Doc::Run& oBinRun, std::wstring& strRunType)
	{
		std::wstring fldCharType	=	DocFileFormat::FormatUtils::UTF8Decode (*oXml.FldCharType);
		if (fldCharType.empty())
			return FALSE;

		Docx2Doc::FldChar oFldChar(fldCharType);

		strRunType					=	fldCharType;

		if (oFldChar.CharType() == Docx2Doc::FldChar::FldCharSeparate)
		{
			oFldChar.SetFieldCharacterProperties((BYTE)Docx2Doc::grffldEnd(true, true, true, true, true, true, true, true));
			m_bHaveSeparateFldChar	=	true;
		}

		if (oFldChar.CharType() == Docx2Doc::FldChar::FldCharEnd)
		{
			oFldChar.SetFieldCharacterProperties((BYTE)Docx2Doc::grffldEnd(false, false, true, true, false, false, false, m_bHaveSeparateFldChar));
			m_bHaveSeparateFldChar	=	false;
		}

		oBinRun.AddRunItem (oFldChar);

		return TRUE;
	}

	template<class T> int CFileTransformer::TextXmlRunTransform (const OOX::Logic::Text& oXml, Docx2Doc::Run& oBinRun)
	{
		Docx2Doc::Text oText(DocFileFormat::FormatUtils::UTF8Decode(oXml.toTxt()).c_str());
		oBinRun.AddRunItem (oText);

		return TRUE;
	}

	template<class T> int CFileTransformer::InstrTextXmlRunTransform (const OOX::Logic::InstrText& oXml, Docx2Doc::Run& oBinRun, std::wstring& strRunType)
	{
		std::wstring strText	=	DocFileFormat::FormatUtils::UTF8Decode(oXml.Text.get_value_or_default());

		std::wstring Source;
		std::wstring FieldCode	=	DOCXDOCUTILS::GetInstrText_FieldCode(strText, Source);
		if (FieldCode.empty())
			return FALSE;

		strRunType				=	FieldCode;

		oBinRun.AddRunItem(Docx2Doc::Text(strText));

		return TRUE;
	}

	template<class T> int CFileTransformer::DrawingXmlRunTransform (const OOX::Logic::Drawing& oXml, Docx2Doc::Run& oBinRun)
	{
		OOX::Image* pImage				=	GetImageDOCX <T, OOX::Logic::Drawing>(&oXml);
		if (pImage)
		{
			if (oXml.haveAnchor)
			{
				return	m_oOArtBuilder.BuildImageRun (*pImage, oXml, oBinRun);
			}

			std::wstring sFileName		=	pImage->filename().wstring();
			if (sFileName.length())
			{
				Unit<int, Dx> twWidth	=	*oXml.Inline->Extent->Size->Width;
				Unit<int, Dx> twHeight	=	*oXml.Inline->Extent->Size->Height;

				Docx2Doc::Picture oPicture (sFileName, twWidth, twHeight);
				if (oPicture.IsValid())
				{
					oBinRun.AddRunItem (oPicture);
					return TRUE;
				}
			}
		}

		return FALSE;
	}

	template<class T> int CFileTransformer::PictXmlRunTransform (const OOX::Logic::Pict& oXml, Docx2Doc::Run& oBinRun)
	{		
		if (oXml.group.is_init())
			return PictGroupXmlTransform<T>(oXml, oBinRun);

		// фигура имеет заливку текстурой

		if (CreateTextureFillShape<T>(oXml, oBinRun))
			return TRUE;

		CShapeRun oShapeRun;
		if (m_oOArtBuilder.BuildShapeRun(oXml, oShapeRun))
		{	
			BuildContentTbRef (oXml);

			if (oShapeRun.IsInline())
			{
				m_oInlineShape.RemoveAllRuns();

				// TODO : сделать нормальное сорхранение Inline фигур (разобраться с недокументированым форматом сохранения объекта)

				//m_oInlineShape.SetShape (oShapeRun);
				//Docx2Doc::Picture oPicture (std::wstring(L""), 0, 0, 0, 0);		//	 fake image
				//m_oInlineShape.SetPicture (oPicture);
				//m_oInlineShape.AddRun (Docx2Doc::Run(Docx2Doc::Picture (std::wstring(L""), 0, 0, 0, 0)));//	 fake image
				//m_oInlineShape.AddRun (Docx2Doc::Run(oShapeRun));//	 fake image

				//m_oInlineShape.AddRun (Docx2Doc::Run(Docx2Doc::CInlineShape (oShapeRun) ));	//	 fake image
				//m_oInlineShape.AddRun (Docx2Doc::Run(oShapeRun));
				//m_oInlineShape.AddRun (Docx2Doc::Run(Docx2Doc::CShapeRun()));

				//m_bIsInlineShape	=	TRUE;

				// TODO : временное решение для Inline Shape - объектов (бинарный парсер доделать)

				oBinRun.AddRunItem (Docx2Doc::CInlineShape (oShapeRun) );
				m_bIsInlineShape	=	FALSE;

				return TRUE;
			}
			else
			{
				oBinRun.AddRunItem(oShapeRun);

				m_bIsInlineShape	=	FALSE;

				return TRUE;
			}
		}
		else
		{
			m_bIsInlineShape	=	FALSE;

			if (CreateImage<T>(oXml, oBinRun))
			{
				return TRUE;
			}

			return FALSE;
		}

		return TRUE;
	}
	template<class T> int CFileTransformer::DelTextXmlRunTransform (const OOX::Logic::DelText& oXml, Docx2Doc::Run& oBinRun)
	{
		Docx2Doc::Text oText( DocFileFormat::FormatUtils::UTF8Decode( oXml.toTxt() ).c_str() );
		oBinRun.AddRunItem(oText);

		return TRUE;
	}
	/*template<class T> int CFileTransformer::SymbolXmlRunTransform (const OOX::Logic::Symbol& oXml, Docx2Doc::Run& oBinRun)
	{
		if (oXml.Font.is_init() && oXml.Char.is_init())
		{
			Docx2Doc::Text oSymbol ((WCHAR)TextMark::Symbol);
			oBinRun.AddRunItem(oSymbol);

			Docx2Doc::CSymbolOperand oSymbolOp (m_mapFontTableMap[*oXml.Font], HexString2Int(*oXml.Char));
			oBinRun.AddProperty(Docx2Doc::Prl( (short)DocFileFormat::sprmCSymbol, oSymbolOp));

			return TRUE;
		}

		return FALSE;
	}*

	/*template<class T> int CFileTransformer::BreakXmlRunTransform (const OOX::Logic::Break& oXml, Docx2Doc::Run& oBinRun)
	{
		/// TODO

		Docx2Doc::Text oText;

		if ( oXml.Type.is_init() )
		{
			if ( *oXml.Type == std::string( "page" ) )
			{
				oText.SetText( &TextMark::PageBreakOrSectionMark );
			}
			else if ( *oXml.Type == std::string( "column" ) )
			{
				oText.SetText( &TextMark::ColumnBreak );
			}
			else if ( *oXml.Type == std::string( "textWrapping" ) )
			{
				oText.SetText( &TextMark::HardLineBreak );
			}
		}
		else
		{
			oText.SetText( &TextMark::HardLineBreak );
		}

		oBinRun.AddRunItem(oText);

		return TRUE;
	}*/

	template<class T> int CFileTransformer::TabXmlRunTransform (const OOX::Logic::Tab& oXml, Docx2Doc::Run& oBinRun)
	{
		/// TODO

		Docx2Doc::Text oText;
		oText.SetText(&TextMark::Tab);

		oBinRun.AddRunItem(oText);

		return TRUE;		
	}

	template<class T> int CFileTransformer::FootnoteReferenceXmlRunTransform (const OOX::Logic::CFootnoteReference& oXml, Docx2Doc::Run& oBinRun)
	{
		if (inputFolder.find<OOX::Document>().exist<OOX::FootNote>())
		{
			static short footnoteIndex = 1;

			const OOX::FootNote::Note& footNote = inputFolder.find<OOX::Document>().find<OOX::FootNote>().find(oXml);

			Docx2Doc::FootnoteReference docFootnoteReference( footnoteIndex );
			Docx2Doc::Footnote docFootnote( footnoteIndex++ );

			size_t count = (*footNote.Items).size();
			const std::vector<OOX::Logic::TextItem>& items = (*footNote.Items);

			for (size_t i = 0; i < count; ++i)	
			{			
				if (items[i].is<OOX::Logic::CParagraph>())
				{
					const OOX::Logic::CParagraph& docxParagraph	=	items[i].as<OOX::Logic::CParagraph>();

					Docx2Doc::Paragraph oParagraph		=	ConvertParagraph<OOX::FootNote>(docxParagraph);
					docFootnote.AddTextItem (oParagraph);
				}
				else if (items[i].is<OOX::Logic::CTbl>())
				{
					Docx2Doc::Table oTable				=	CreateTable<OOX::FootNote>(items[i].as<OOX::Logic::Table>());
					docFootnote.AddTextItem (oTable);
				}
			}

			oBinRun.AddRunItem (docFootnoteReference);
			m_pDOCFile->AddFootnote(docFootnote);

			return TRUE;		
		}

		return FALSE;
	}

	template<class T> int CFileTransformer::FootnoteRefXmlRunTransform (const OOX::Logic::CFootnoteRef& oXml, Docx2Doc::Run& oBinRun)
	{
		if (inputFolder.find<OOX::Document>().exist<OOX::FootNote>())
		{
			static short footnoteIndex = 1;

			oBinRun.AddRunItem(Docx2Doc::FootnoteRef(footnoteIndex++));

			return TRUE;		
		}

		return FALSE;
	}

	template<class T> int CFileTransformer::EndnoteReferenceXmlRunTransform (const OOX::Logic::CEndnoteReference& oXml, Docx2Doc::Run& oBinRun)
	{
		if (inputFolder.find<OOX::Document>().exist<OOX::EndNote>())
		{
			static short endnoteIndex = 1;

			const OOX::EndNote::Note& endNote = inputFolder.find<OOX::Document>().find<OOX::EndNote>().find(oXml);

			Docx2Doc::EndnoteReference docEndnoteReference(endnoteIndex);
			Docx2Doc::Endnote docEndnote(endnoteIndex++);

			size_t count = (*endNote.Items).size();
			const std::vector<OOX::Logic::TextItem>& items = (*endNote.Items);

			for (size_t j = 0; j < count; ++j)	
			{
				if (items[j].is<OOX::Logic::CParagraph>())
				{							
					const OOX::Logic::Paragraph& docxParagraph	=	items[j].as<OOX::Logic::CParagraph>();

					Docx2Doc::Paragraph oParagraph		=	ConvertParagraph<OOX::EndNote>(docxParagraph);
					docEndnote.AddTextItem(oParagraph);
				}
				else if (items[j].is<OOX::Logic::Table>())
				{
					Docx2Doc::Table oTable				=	CreateTable<OOX::EndNote>(items[j].as<OOX::Logic::Table>());
					docEndnote.AddTextItem(oTable);
				}
			}

			oBinRun.AddRunItem( docEndnoteReference );
			m_pDOCFile->AddEndnote( docEndnote );

			return TRUE;		
		}

		return FALSE;
	}

	template<class T> int CFileTransformer::EndnoteRefXmlRunTransform (const OOX::Logic::CEndnoteRef& oXml, Docx2Doc::Run& oBinRun)
	{
		if (inputFolder.find<OOX::Document>().exist<OOX::EndNotes>())
		{
			static short endnoteIndex = 1;

			oBinRun.AddRunItem(Docx2Doc::EndnoteRef(endnoteIndex++));

			return TRUE;		
		}

		return FALSE;
	}
	/*template<class T> int CFileTransformer::PictGroupXmlTransform (const OOX::Logic::Pict& oXml, Docx2Doc::Run& oBinRun)
	{
		Docx2Doc::COArtStorage* pStorage	=	Docx2Doc::COArtStorage::Instance();
		if (NULL == pStorage)
			return FALSE;

		Docx2Doc::COArtGroup* pShapes	=	CreateGroup<T>(oXml.group);
		if (NULL == pShapes)
			return FALSE;

		oBinRun.AddRunItem(m_oOArtBuilder.BuildGroupRun(oXml.group,pShapes));
		return TRUE;
	}*/
}

namespace DOCXTODOC
{
	/*template <class T, class TXmlImage> OOX::Image* CFileTransformer::GetImageDOCX (const TXmlImage* pXmlImage)
	{	
		if (pXmlImage)
		{
			int bFindOK	=	FALSE;
			OOX::RId nID;

			if (typeid(TXmlImage) == typeid(OOX::Logic::Drawing))
			{
				OOX::Logic::Drawing* pPicture		=	(OOX::Logic::Drawing*)(pXmlImage);
				if (pPicture)
				{
					if (pPicture->Inline->Graphic->Pic->rId.is_init())
					{
						nID			=	pPicture->Inline->Graphic->Pic->rId;
						bFindOK		=	TRUE;
					}
				}
			}

			if (typeid(TXmlImage) == typeid(OOX::Logic::Pict))
			{
				OOX::Logic::Pict* pPicture	=	(OOX::Logic::Pict*)(pXmlImage);
				if (pPicture)
				{
					if(pPicture->shape.is_init())
					{
						if (pPicture->shape->imageData.is_init())
						{
							nID				=	pPicture->shape->imageData->rId;
							bFindOK			=	TRUE;							
						}
					}
				}
			}

			if (typeid(TXmlImage) == typeid(OOX::Logic::Shape))
			{
				OOX::Logic::Shape* pShape	=	(OOX::Logic::Shape*)(pXmlImage);
				if (pShape)
				{
					if (pShape->imageData.is_init())
					{
						nID				=	pShape->imageData->rId;
						bFindOK			=	TRUE;							
					}
				}
			}

			if (bFindOK)
			{
				if (typeid(T) != typeid(OOX::Document))
				{
					if (inputFolder.find<OOX::Document>().find<T>().exist(nID))
						return dynamic_cast<OOX::Image*>(inputFolder.find<OOX::Document>().find<T>()[nID].get());
				}
				else
				{
					if (inputFolder.find<OOX::Document>().exist(nID))
						return dynamic_cast<OOX::Image*>(inputFolder.find<OOX::Document>()[nID].get());
				}
			}
		}

		return NULL;
	}*/

	/*template <class T> OOX::Image* CFileTransformer::GetImageWithId(const OOX::RId& nID)
	{
		if (typeid(T) != typeid(OOX::Document))
		{
			if (inputFolder.find<OOX::Document>().find<T>().exist(nID))
				return dynamic_cast<OOX::Image*>(inputFolder.find<OOX::Document>().find<T>()[nID].get());
		}

		if (inputFolder.find<OOX::Document>().exist(nID))
			return dynamic_cast<OOX::Image*>(inputFolder.find<OOX::Document>()[nID].get());

		return NULL;
	}*/

	/*template<class T> int CFileTransformer::CreateImage (const OOX::Logic::Pict& oXml, Docx2Doc::Run& oBinRun)
	{
		OOX::Image* pImage				=	GetImageDOCX <T, OOX::Logic::Pict>(&oXml);

		if (pImage)
		{
			std::wstring sFileName		=	pImage->filename().wstring();
			if (sFileName.length())
			{
				if (oXml.shape.is_init())
				{
					if (oXml.shape->imageData.is_init())
					{
						return m_oOArtBuilder.BuildImageRun(oXml.shape, pImage->filename().wstring(), oBinRun);
					}
				}

				Unit<int, Dx> twWidth	=	*oXml.shape->style->Size->Width;
				Unit<int, Dx> twHeight	=	*oXml.shape->style->Size->Height;

				Docx2Doc::Picture oPicture (sFileName, twWidth, twHeight);
				if (oPicture.IsValid())
				{
					oBinRun.AddRunItem (Docx2Doc::Picture());

					return TRUE;
				}
			}
		}

		return FALSE;
	}*/

	/*template<class T> Docx2Doc::COArtGroup* CFileTransformer::CreateGroup(const OOX::Logic::Group& oXmlGroup)
	{
		Docx2Doc::COArtStorage* pStorage	=	Docx2Doc::COArtStorage::Instance();
		if (NULL == pStorage)
			return FALSE;

		Docx2Doc::COArtGroup* pBinGroup		=	new Docx2Doc::COArtGroup(pStorage->GenID(m_oOArtBuilder.Location()));
		if (NULL == pBinGroup)
			return FALSE;

		pBinGroup->SetCoord(DOCX::CFPoint(oXmlGroup.coordorigin, 0.0, 0.0), DOCX::CFPoint(oXmlGroup.coordsize, 0.0, 0.0));
		pBinGroup->SetBounds(oXmlGroup.style);
		pBinGroup->SetupFromStyleXml(oXmlGroup.style);

		for (size_t i = 0; i < oXmlGroup.items->size(); ++i)
		{
			const OOX::Logic::GroupItem& oXmlItem	=	oXmlGroup.items->operator[](i);

			if (oXmlItem.is<OOX::Logic::Oval>())
			{
				const OOX::Logic::Oval& shape = oXmlItem.as<OOX::Logic::Oval>();

				if (shape.fillstyle->Id.is_init())
				{
					OOX::Image* image = GetImageWithId <T>(OOX::RId(shape.fillstyle->Id));
					if (image)
					{
						m_oOArtBuilder.SetTextureFill(image->filename().wstring());
					}
				}

				pBinGroup->Append (m_oOArtBuilder.BuildOArtGroupShape<OOX::Logic::Oval>(shape, OfficeArt::Enumerations::msosptEllipse));
			}

			if (oXmlItem.is<OOX::Logic::Roundrect>())
			{
				const OOX::Logic::Roundrect& shape = oXmlItem.as<OOX::Logic::Roundrect>();

				if (shape.fillstyle->Id.is_init())
				{
					OOX::Image* image = GetImageWithId <T>(OOX::RId(shape.fillstyle->Id));
					if (image)
					{
						m_oOArtBuilder.SetTextureFill(image->filename().wstring());
					}
				}

				pBinGroup->Append (m_oOArtBuilder.BuildOArtGroupShape<OOX::Logic::Roundrect>(oXmlItem.as<OOX::Logic::Roundrect>(), OfficeArt::Enumerations::msosptRoundRectangle));
			}

			if (oXmlItem.is<OOX::Logic::Rect>())
			{
				const OOX::Logic::Rect& shape = oXmlItem.as<OOX::Logic::Rect>();

				if (shape.fillstyle->Id.is_init())
				{
					OOX::Image* image = GetImageWithId <T>(OOX::RId(shape.fillstyle->Id));
					if (image)
					{
						m_oOArtBuilder.SetTextureFill(image->filename().wstring());
					}
				}

				pBinGroup->Append (m_oOArtBuilder.BuildOArtGroupShape<OOX::Logic::Rect>(oXmlItem.as<OOX::Logic::Rect>(), OfficeArt::Enumerations::msosptRectangle));
			}

			if (oXmlItem.is<OOX::Logic::Line>())
			{
				pBinGroup->Append (m_oOArtBuilder.BuildOArtGroupShape<OOX::Logic::Line>(oXmlItem.as<OOX::Logic::Line>(), OfficeArt::Enumerations::msosptLine));
			}

			if (oXmlItem.is<OOX::Logic::Shape>())
			{
				const OOX::Logic::Shape& shape = oXmlItem.as<OOX::Logic::Shape>();				
				if (shape.imageData.is_init())
				{
					OOX::Image* image = GetImageDOCX <T, OOX::Logic::Shape>(&shape);
					if (image)
					{
						pBinGroup->Append (m_oOArtBuilder.BuildOArtImage(shape, image->filename().wstring()));
					}
				}
				else
				{
					if (shape.fillstyle->Id.is_init())
					{
						OOX::Image* image = GetImageWithId <T>(OOX::RId(shape.fillstyle->Id));
						if (image)
						{
							m_oOArtBuilder.SetTextureFill(image->filename().wstring());
						}
					}

					pBinGroup->Append (m_oOArtBuilder.BuildOArtShape(shape, oXmlGroup));
				}
			}

			if (oXmlItem.is<OOX::Logic::Group>())
			{
				const OOX::Logic::Group& oXmlInGroup = oXmlItem.as<OOX::Logic::Group>();
				pBinGroup->Append (CreateGroup<T>(oXmlInGroup));
			}
		}

		if (pBinGroup->IsValid())
			return pBinGroup;

		RELEASEOBJECT(pBinGroup);
		return NULL;
	}*/

	/*template<class T> int CFileTransformer::CreateTextureFillShape (const OOX::Logic::Pict& oXml, Docx2Doc::Run& oBinRun)
	{
		// фигура имеет заливку текстурой

		// RECT

		if (oXml.rect.is_init())
		{
			if (oXml.rect->fillstyle->Id.is_init())
			{
				OOX::Image* pImage = GetImageWithId <T>(OOX::RId(oXml.rect->fillstyle->Id));
				if (pImage)
				{
					return m_oOArtBuilder.BuildShapeWithTextureFill<OOX::Logic::Rect>(oXml.rect, pImage->filename().wstring(), OfficeArt::Enumerations::msosptRectangle, oXml, oBinRun);
				}

				return FALSE;
			}
		}

		// OVAL

		if (oXml.oval.is_init())
		{
			if (oXml.oval->fillstyle->Id.is_init())
			{
				OOX::Image* pImage = GetImageWithId <T>(OOX::RId(oXml.oval->fillstyle->Id));
				if (pImage)
				{
					return m_oOArtBuilder.BuildShapeWithTextureFill<OOX::Logic::Oval>(oXml.oval, pImage->filename().wstring(), OfficeArt::Enumerations::msosptEllipse, oXml, oBinRun);
				}

				return FALSE;
			}
		}

		// ROUNDRECT

		if (oXml.roundrect.is_init())
		{
			if (oXml.roundrect->fillstyle->Id.is_init())
			{
				OOX::Image* pImage = GetImageWithId <T>(OOX::RId(oXml.roundrect->fillstyle->Id));
				if (pImage)
				{
					return m_oOArtBuilder.BuildShapeWithTextureFill<OOX::Logic::Roundrect>(oXml.roundrect, pImage->filename().wstring(), OfficeArt::Enumerations::msosptRoundRectangle, oXml, oBinRun);
				}

				return FALSE;
			}
		}

		// SHAPE CUSTOM

		if (oXml.shape.is_init())
		{
			if (oXml.shape->fillstyle->Id.is_init())
			{
				OOX::Image* pImage = GetImageWithId <T>(OOX::RId(oXml.shape->fillstyle->Id));
				if (pImage)
				{
					return m_oOArtBuilder.BuildShapeWithTextureFill<OOX::Logic::Shape>(oXml.shape, pImage->filename().wstring(), 0, oXml, oBinRun);
				}

				return FALSE;
			}
		}

		return FALSE;
	}*/
}

namespace DOCXTODOC
{
	/*int CFileTransformer::BuildContentTbRef (const OOX::Logic::Pict& oXml)
	{
		CTextBoxRef* pTbRef = m_oOArtBuilder.LastTbRef ();
		if (pTbRef)
		{
			std::vector<Docx2Doc::TextItem> oTextItems;

			if (oXml.rect.is_init())
			{
				if (oXml.rect->textbox.is_init())
					TransformTb(oXml.rect->textbox->content->items, oTextItems);
			}

			if (oXml.oval.is_init())
			{
				if (oXml.oval->textbox.is_init())
					TransformTb(oXml.oval->textbox->content->items, oTextItems);
			}

			if (oXml.roundrect.is_init())
			{
				if (oXml.roundrect->textbox.is_init())
					TransformTb(oXml.roundrect->textbox->content->items, oTextItems);
			}

			if (oXml.line.is_init())
			{
				if (oXml.line->textbox.is_init())
					TransformTb(oXml.line->textbox->content->items, oTextItems);
			}

			if (oXml.shape.is_init())
			{
				if (oXml.shape->textbox.is_init())
					TransformTb(oXml.shape->textbox->content->items, oTextItems);
			}

			if (oTextItems.size())
			{
				pTbRef->AppendTbItems(oTextItems);
				return TRUE;
			}
		}

		return FALSE;
	}*/

	int CFileTransformer::TransformTb (const std::vector<OOX::Logic::TextItem>& oXmlItems, std::vector<Docx2Doc::TextItem>& oTextItems)
	{
		for (size_t i = 0; i < oXmlItems.size(); ++i)
		{
			const OOX::Logic::TextItem& oXmlItem	=	oXmlItems[i];

			if (oXmlItem.is<OOX::Logic::CParagraph>())
			{
				Docx2Doc::Paragraph oBinPr	=	ConvertParagraph<OOX::Document>(oXmlItem.as<OOX::Logic::CParagraph>());
				oTextItems.push_back(TextItem(oBinPr));
			}

			if (oXmlItem.is<OOX::Logic::CTbl>())
			{
				Docx2Doc::Table oBinTable	=	CreateTable<OOX::Document>(oXmlItem.as<OOX::Logic::CTbl>());
				oTextItems.push_back(TextItem(oBinTable));
			}

			if (oXmlItem.is<OOX::Logic::CSdt>())
			{
				//const OOX::Logic::SdtContent& content = oXmlItem.as<OOX::Logic::Sdt>().Content;
				//TransformTb(*content.Items, oTextItems);  
			}
		}

		return TRUE;
	}
}
