#pragma once

#include "DocFile.h"

#include "../../DocxFormat/Docx.h"
#include "../../DocxFormat/Logic/Pict.h"
#include "../../DocxFormat/Logic/Hyperlink.h"
#include "../../DocxFormat/Logic/Table.h"
#include "../../DocxFormat/Logic/TableProperty.h"
#include "../../DocxFormat/Logic/Paragraph.h"
#include "../../DocxFormat/Logic/ParagraphProperty.h"
#include "../../DocxFormat/Logic/SectionProperty.h"
#include "../../DocxFormat/Logic/Run.h"
#include "../../DocxFormat/Logic/RunProperty.h"
#include "../../DocxFormat/Logic/RunContent.h"
#include "../../DocxFormat/Logic/FldChar.h"
#include "../../DocxFormat/Logic/FldSimple.h"
#include "../../DocxFormat/Logic/Annotations.h"
#include "../../DocxFormat/Logic/Sdt.h"
#include "../../DocxFormat/Styles.h"
#include "../../DocxFormat/Endnote.h"
#include "../../DocxFormat/Font.h"
#include "../../DocxFormat/FontTable.h"
#include "../../DocxFormat/HeaderFooter.h"
#include "../../DocxFormat/Numbering.h"


//#include "Parse.h"
#include "../../Base/Unit.h"

#include "Prl.h"
#include "InternalElements.h"
//#include "TableUtils.h"

namespace Docx2Doc
{
	class CPrCopier
	{
	public:
		CPrCopier(PrlList* dest, PrlList* source): m_dest(dest), m_source(source)
		{
			if ((NULL != m_dest) && (NULL != m_source))
			{
				AddOrReplaceProperties();
			}
		}

	private:
		inline void AddOrReplaceProperties()
		{
			for (std::vector<Docx2Doc::Prl>::const_iterator iter = m_source->begin(); iter != m_source->end(); ++iter)
			{
				RemovePropertyByCode(iter->GetSprmCode());
				m_dest->push_back(*iter);
			}    
		}

		inline void RemovePropertyByCode(unsigned short sprm)
		{
			for (std::vector<Docx2Doc::Prl>::iterator iter = m_dest->begin(); iter != m_dest->end(); ++iter)
			{
				if (iter->GetSprmCode() == sprm)
				{
					m_dest->erase(iter);

					RemovePropertyByCode(sprm);

					break;
				}
			}
		}

	private:

		PrlList* m_dest;
		PrlList* m_source;
	};

	class CFileTransformer
	{
	public:

		CFileTransformer ();
		~CFileTransformer();

		long Convert(const WCHAR* ooxFolder, const WCHAR* docFile);

	private:
		void ConvertDocument (const OOX::CDocument& oXmlDoc);
		void ConvertContent  (const std::vector<OOX::WritingElement*>& oXmlItems);		// OOX::Logic::TextItem - похоже это просто WritingElement
		template<class T> Docx2Doc::Paragraph ConvertParagraph (const OOX::Logic::CParagraph& oXmlParagraph);

		// Document
		std::wstring GetFontNameByThemeName(const std::wstring& themeName);
		std::vector<Docx2Doc::XAS> BuildXASs(const OOX::Logic::CTbl& docxTable, const std::vector<OOX::Logic::CTableCellProperties>& tableCells);

		int ValidParagraph (const OOX::Logic::CParagraph& oXmlParagraph);
		template<class T> Docx2Doc::Hyperlink ConvertHyperlink( const OOX::Logic::CHyperlink& docxHyperlink, const PrlList& styleDocRunProperties);
		template<class T> void UpdateItemByCondition( T* docItem, const std::wstring& condition);

		const PrlList ConvertRunProperties (const OOX::Logic::CRunProperty& docxRunProperties);
		const PrlList ConvertParagraphProperties( const OOX::Logic::CParagraphProperty& docxParagraphProperties);
		PrlList ConvertTableProperties( const OOX::Logic::CTableProperty& docxTableProperties, unsigned int cellsCount = 0);

		Docx2Doc::Constants::VerticalMergeFlag ConvertTableVerticalMergeFlag( const nullable<ComplexTypes::Word::CVMerge>& vMerge);

		template<class T> void ConvertFldSimple( const OOX::Logic::CFldSimple& fldSimpleDocx, const PrlList& styleDocRunProperties, Docx2Doc::Paragraph& docParagraph, std::wstring& runType);

		// настройки страниц документа

		Docx2Doc::SectionProperties ConvertSectionProperties (const OOX::Logic::CSectionProperty& oSection);
		bool AddLineNumberingSettings (const OOX::Logic::CSectionProperty& oSection, PrlList& arrSettings);

		// верхний колонтитул
		Docx2Doc::Header	ConvertHeader (const OOX::CHdrFtr& oXmlDOCXHeader);
		// нижний колонтитул
		Docx2Doc::Footer	ConvertFooter (const OOX::CHdrFtr& oXmlDOCXFooter);

		// Table

		template<class T> Docx2Doc::Table CreateTable (const OOX::Logic::CTbl& oXmlTable);
		const PrlList ConvertTableRowCellsProperties(const OOX::Logic::CTbl& oXmlTable, int nY, int nCY, const std::vector<OOX::Logic::TableCell>& docxTableCells, const OOX::CStyle& oStyle);
		const PrlList ConvertTableRowProperties(int nY, const OOX::Logic::CTableRowProperties& oXmlRow);

		// Fonts

		void AddInternalFont (const std::wstring& strFontName);
		void ConvertFontTable (const OOX::CFontTable& oXmlFontTable);
		Docx2Doc::PANOSE ConvertPanose (const std::string& strPanose);

		// Styles

		PrlList GetParagraphPropertiesFromStyleHierarchy (const std::wstring& styleID, PrlList* styleDocRunLinkProperties);
		PrlList GetRunPropertiesFromStyleHierarchy (const std::wstring& styleID);
		PrlList GetTablePropertiesFromStyleHierarchy (const std::wstring& styleID);

		void ConvertStyleSheet (const OOX::CStyles& oStyleSheet);
		std::vector<Docx2Doc::LSD> ConvertLatentStyles (/*const OOX::Styles::LattentStyles& latentStyles*/);
		std::vector<Docx2Doc::LPStd> ConvertStyleDefinitions (const std::vector<OOX::CStyle*>& arrStyles);


		std::wstring GetStyleID (const OOX::Logic::CParagraph& oXmlParagraph);

		// Numbering

		const std::vector<Docx2Doc::LSTF> ConvertAbstractNums (const std::vector<OOX::Numbering::CAbstractNum>& arrNums);
		const std::vector<Docx2Doc::LVL> ConvertLVLs (const OOX::CNumbering& oXmlNumbering, const std::vector<OOX::Numbering::CAbstractNum>& _abstractNums);
		const Docx2Doc::LVL ConvertLVL (const OOX::Numbering::CNumLvl& _level);
		const Docx2Doc::Xst ConvertLvlText (const std::string& _lvlText, Docx2Doc::Constants::MSONFC _nfc);
		void ConvertNumbering (const OOX::CNumbering& _numbering);
		const Docx2Doc::PlfLfo ConvertNums (const std::vector<OOX::Numbering::CNum>& _nums);
		int FindAbstractNumIdWithStyleRef (const OOX::CNumbering& oXmlNumbering, const std::string& refLink);

		// run rule transform
		template<class T> Docx2Doc::Run ConvertRun(const OOX::Logic::CRun& oXml, const PrlList& styleDocRunProperties, std::wstring& strRunType);
		template<class T> int TextXmlRunTransform (const OOX::Logic::CText& oXml, Docx2Doc::Run& oBinRun);
		template<class T> int FldCharXmlRunTransform (const OOX::Logic::CFldChar& oXml, Docx2Doc::Run& oBinRun, std::wstring& strRunType);
		template<class T> int InstrTextXmlRunTransform (const OOX::Logic::CInstrText& oXml, Docx2Doc::Run& oBinRun, std::wstring& strRunType);
		template<class T> int DrawingXmlRunTransform (const OOX::Logic::CDrawing& oDrawing, Docx2Doc::Run& oBinRun);
		template<class T> int PictXmlRunTransform (const OOX::Logic::CPicture& oXml, Docx2Doc::Run& oBinRun);
		template<class T> int DelTextXmlRunTransform (const OOX::Logic::CDelText& oXml, Docx2Doc::Run& oBinRun);
		//template<class T> int SymbolXmlRunTransform (const OOX::Logic::Symbol& oXml, Docx2Doc::Run& oBinRun);
		//template<class T> int BreakXmlRunTransform (const OOX::Logic::Break& oXml, Docx2Doc::Run& oBinRun);
		template<class T> int TabXmlRunTransform (const OOX::Logic::CTab& oXml, Docx2Doc::Run& oBinRun);
		template<class T> int FootnoteReferenceXmlRunTransform (const OOX::Logic::CFootnoteReference& oXml, Docx2Doc::Run& oBinRun);
		template<class T> int FootnoteRefXmlRunTransform (const OOX::Logic::CFootnoteRef& oXml, Docx2Doc::Run& oBinRun);
		template<class T> int EndnoteReferenceXmlRunTransform (const OOX::Logic::CEndnoteReference& oXml, Docx2Doc::Run& oBinRun);
		template<class T> int EndnoteRefXmlRunTransform (const OOX::Logic::CEndnoteRef& oXml, Docx2Doc::Run& oBinRun);

		// Images

		template <class T, class TXmlImage> OOX::Image* GetImageDOCX (const TXmlImage* pXmlImage);
		template <class T> int CreateImage (const OOX::Logic::CPicture& oPicture, Docx2Doc::Run& oBinRun);
		template <class T> OOX::Image* GetImageWithId(const OOX::RId& nID);
		template<class T> int CreateTextureFillShape (const OOX::Logic::CPicture& oXml, Docx2Doc::Run& oBinRun);

		// Group

		//template<class T> Docx2Doc::COArtGroup* CreateGroup(const OOX::Logic::Group& oXmlGroup);
		template<class T> int PictGroupXmlTransform (const OOX::Logic::CPicture& oXml, Docx2Doc::Run& oBinRun);


		// TextBox

		int BuildContentTbRef (const OOX::Logic::CPicture& oXml);
		int TransformTb (const std::vector<OOX::WritingElement*>& oXmlItems, std::vector<Docx2Doc::TextItem>& oTextItems);

	private:

		std::map<std::wstring, short>	m_mapFontTableMap;
		std::vector<std::wstring>		m_arrInternalFonts;

		std::map<std::wstring, Docx2Doc::LID>		m_lidMap;
		std::map<std::wstring, Docx2Doc::StyleID>	m_predefinedStyleIDMap;
		std::map<std::wstring, short>				m_mapStyleSheetMap;

		std::map<std::wstring, Docx2Doc::Constants::StyleType>	m_styleTypeMap;
		std::map<std::wstring, Docx2Doc::Constants::MSONFC>		m_numFmtMap;
		std::map<int, int> m_idLsidMap;
		std::map<int, short> m_idIndexMap;
		std::map<std::wstring, BYTE> m_kulMap;
		std::map<std::wstring, Docx2Doc::Constants::SBkcOperand> m_sectionBreakTypeMap;
		std::map<std::wstring, BYTE> m_verticalPositionCodeMap;
		std::map<std::wstring, BYTE> m_horizontalPositionCodeMap;
		std::map<std::wstring, BYTE> m_textFrameWrappingMap;
		std::map<std::wstring, Docx2Doc::Constants::Fts> m_tableCellWidthMap;
		std::map<std::wstring, Docx2Doc::Constants::TabJC> m_customTabStopAlignment;
		std::map<std::wstring, Docx2Doc::Constants::TabLC> m_customTabStopLeader;

		OOX::CDocx				m_oDocx;
		Docx2Doc::CDocFile*		m_pDocFile;

		bool					m_bHaveSeparateFldChar;
		int						m_bIsInlineShape;

		//Docx2Doc::COArtBuilder	m_oOArtBuilder;	// Office Drawing Binary File Format - Builder
		//Docx2Doc::InlineShape		m_oInlineShape;

		int	m_bIsHaveRunPr;
	};
}
