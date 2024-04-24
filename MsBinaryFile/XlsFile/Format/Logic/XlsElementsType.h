﻿/*
 * (c) Copyright Ascensio System SIA 2010-2024
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

namespace XLS
{

enum ElementType
{
    typeNone = 0,

	typeBiffRecord,
	typeBiffRecordContinued,
	typeBiffRecordSplit,

	typeCompositeObject,

//BiffRecord
	typeAnyObject = 1000,
	typeAreaFormat,
	typeAlRuns,
	typeArea,
	typeArray,
	typeAttachedLabel,
	typeAutoFilter,
	typeAutoFilter12,
	typeAutoFilterInfo,
	typeAxcExt,
	typeAxesUsed,
	typeAxis,
	typeAxisLine,
	typeAxisParent,
	typeBackup,
	typeBar,
	typeBegin,
	typeBigName,
	typeBkHim,
	typeBlank,
	typeBOF,
	typeBoolErr,
	typeBookBool,
	typeBookExt,
	typeBopPop,
	typeBopPopCustom,
	typeBottomMargin,
	typeBoundSheet8,
	typeBRAI,
	typeBuiltInFnGroupCount,
	typeCalcCount,
	typeCalcDelta,
	typeCalcIter,
	typeCalcMode,
	typeCalcPrecision,
	typeCalcRefMode,
	typeCalcSaveRecalc,
	typeCatLab,
	typeCatSerRange,
	typeCellWatch,
	typeCF,
	typeCF12,
	typeCFEx,
	typeChart,
	typeChart3d,
	typeChart3DBarShape,
	typeChartFormat,
	typeChartFrtInfo,
	typeCodeName,
	typeCodePage,
	typeColInfo,
	typeCompat12,
	typeCompressPictures,
	typeCondFmt,
	typeCondFmt12,
	typeContinue,
	typeContinueBigName,
	typeContinueFrt,
	typeContinueFrt11,
	typeContinueFrt12,
	typeCountry,
	typeConnGrbitDbtOledb,
	typeConnGrbitDbtAdo,
	typeConnGrbitDbtWeb,
	typeCrErr,
	typeCRN,
	typeCrtLayout12,
	typeCrtLayout12A,
	typeCrtLine,
	typeCrtLink,
	typeCrtMlFrt,
	typeCrtMlFrtContinue,
	typeDat,
	typeDataFormat,
	typeDataLabExt,
	typeDataLabExtContents,
	typeDate1904,
	typeDBCell,
	typeDbOrParamQry,
	typeDBQueryExt,
	typeDCon,
	typeDConBin,
	typeDConName,
	typeDConRef,
	typeDConn,
	typeDConnConnectionOleDb,
	typeDConnConnectionWeb,
	typeDConnId,
	typeDConnParameter,
	typeDConnParamBindingValType,
	typeDConnParamBindingValByte,
	typeDConnParamBindingValInt,
	typeDConnStringSequence,
	typeDefaultRowHeight,
	typeDefaultText,
	typeDefColWidth,
	typeDimensions,
	typeDocRoute,
	typeDropBar,
	typeDropDownObjIds,
	typeDSF,
	typeDv,
	typeDVal,
	typeDXF,
	typeDxGCol,
	typeEnd,
	typeEndObject,
	typeEntExU2,
	typeEOF_T,
	typeExcel9File,
	typeExternName,
	typeExternSheet,
	typeExtSST,
	typeExtString,
	typeFbi,
	typeFbi2,
	typeFeat,
	typeFeatHdr,
	typeFeatHdr11,
	typeFeature11,
	typeFeature12,
	typeFilePass,
	typeFileSharing,
	typeFilterMode,
	typeFnGroupName,
	typeFnGrp12,
	typeFont,
	typeFontInfo,
	typeFontX,
	typeFooter,
	typeForceFullCalculation,
	typeFormat,
	typeFormula,
	typeFrame,
	typeFrtFontList,
	typeFrtWrapper,
	typeGelFrame,
	typeGridSet,
	typeGUIDTypeLib,
	typeGuts,
	typeHCenter,
	typeHeader,
	typeHeaderFooter,
	typeHFPicture,
	typeHideObj,
	typeHLink,
	typeIHLink,
	typeHLinkTooltip,
	typeHorizontalPageBreaks,
	typeIFmtRecord,
	typeIMDATA,
	typeIndex,
	typeInterfaceEnd,
	typeInterfaceHdr,
	typeIntl,
	typeLabel,
	typeLabelSst,
	typeLbl,
	typeLeftMargin,
	typeLegend,
	typeLegendException,
	typeLel,
	typeLine,
	typeLineFormat,
	typeList12,
	typeLPr,
	typeLRng,
	typeMarkerFormat,
	typeMDB,
	typeMDTInfo,
	typeMDXKPI,
	typeMDXProp,
	typeMDXSet,
	typeMDXStr,
	typeMDXTuple,
	typeMergeCells,
	typeMms,
	typeMsoDrawing,
	typeMsoDrawingGroup,
	typeMsoDrawingSelection,
	typeMTRSettings,
	typeMulBlank,
	typeMulRk,
	typeNameCmt,
	typeNameFnGrp12,
	typeNamePublish,
	typeNote,
	typeNumber,
	typeObj,
	typeObjectLink,
	typeObjProtect,
	typeObNoMacros,
	typeObProj,
	typeOleDbConn,
	typeOleObjectSize,
	typePalette,
	typePane,
	typePassword,
	typePBT,
	typePhoneticInfo,
	typePicF,
	typePie,
	typePieFormat,
	typePivotChartBits,
	typePlotArea,
	typePlotGrowth,
	typePls,
	typePLV,
	typePos,
	typePrintGrid,
	typePrintRowCol,
	typePrintSize,
	typeProt4Rev,
	typeProt4RevPass,
	typeProtect,
	typeQsi,
	typeQsif,
	typeQsir,
	typeQsiSXTag,
	typeRadar,
	typeRadarArea,
	typeRealTimeData,
	typeRecalcId,
	typeRecipName,
	typeRefreshAll,
	typeRichTextStream,
	typeRightMargin,
	typeRGISeriesListSpecial,
	typeRK,
	typeRow,
	typeRRSort,
	typeRRTabId,
	typeSBaseRef,
	typeScatter,
	typeSCENARIO,
	typeScenarioProtect,
	typeScenMan,
	typeScl,
	typeSelection,
	typeSerAuxErrBar,
	typeSerAuxTrend,
	typeSerFmt,
	typeSeries,
	typeSeriesList,
	typeSeriesText,
	typeSerParent,
	typeSerToCrt,
	typeSetup,
	typeShapePropsStream,
	typeSheetExt,
	typeShrFmla,
	typeShtProps,
	typeSIIndex,
	typeSort,
	typeSortData,
	typeSST,
	typeStartObject,
	typeString,
	typeStyle,
	typeStyleExt,
	typeSupBook,
	typeSurf,
	typeStringSegmented,
	typeStringSegmentedSXADDL,
	typeSXAddl,
	typeSxaddlSxString,
	typeSXDI,
	typeSxDXF,
	typeSXEx,
	typeSxFilt,
	typeSxFormat,
	typeSxItm,
	typeSxIvd,
	typeSXLI,
	typeSXPI,
	typeSXPIEx,
	typeSxRule,
	typeSxSelect,
	typeSXStreamID,
	typeSXString,
	typeSXTbl,
	typeSxTbpg,
	typeSXTBRGIITM,
	typeSXTH,
	typeSxvd,
	typeSXVDEx,
	typeSXVDTEx,
	typeSXVI,
	typeSXVIFlags,
	typeSxView,
	typeSXAxis,
	typeSXViewEx,
	typeSXViewEx9,
	typeSXViewLink,
	typeSXVS,
	typeSync,
	typeTable,
	typeTableStyle,
	typeTableStyleElement,
	typeTableStyles,
	typeTemplate,
	typeText,
	typeTextPropsStream,
	typeTheme,
	typeTick,
	typeTopMargin,
	typeTxO,
	typeTxtQry,
	typeTxtWf,
	typeUncalced,
	typeUnits,
	typeUserBView,
	typeUserSViewBegin,
	typeUserSViewEnd,
	typeUsesELFs,
	typeValueRange,
	typeVCenter,
	typeVerticalPageBreaks,
	typeWebPub,
	typeWindow1,
	typeWindow2,
	typeWinProtect,
	typeWOpt,
	typeWriteAccess,
	typeWriteProtect,
	typeWsBool,
	typeXCT,
	typeXF,
	typeXFCRC,
	typeXFExt,
	typeYMult,

	typeClrtClient,

//CompositeObject
	typeAI,
	typeATTACHEDLABEL,
	typeAUTOFILTER,
	typeAXES,
	typeAXISPARENT,
	typeAXM,
	typeAXS,
	typeBACKGROUND,
	typeBIGNAME,
	typeBUNDLESHEET,
	typeCELL,
	typeCELL_GROUP,
	typeCELLTABLE,
	typeCHART,
	typeCHARTFOMATS,
	typeCOLUMNS,
	typeCONDFMT,
	typeCONDFMT12,
	typeCONDFMTS,
	typeCRT,
	typeCRTMLFRT,
	typeCUSTOMVIEW,
	typeDAT,
	typeDBQUERY,
	typeDBQUERYEXT,
	typeDCON,
	typeDFTTEXT,
	typeDOCROUTE,
	typeDREF,
	typeDROPBAR,
	typeDVAL,
	typeDVAXIS,
	typeFEAT,
	typeFEAT11,
	typeFNGROUPS,
	typeFONTLIST,
	typeFORMATTING,
	typeFORMULA,
	typeFRAME,
	typeGELFRAME,
	typeGLOBALS,
	typeHLINK,
	typeINTERFACE_T,
	typeIMDATAOBJECT,
	typeIVAXIS,
	typeLBL,
	typeLD,
	typeMACROSORTANDFILTER,
	typeMDBLOCK,
	typeMDTINFO,
	typeMDXSTR,
	typeMDXTUPLESET,
	typeMETADATA,
	typeMSODRAWINGGROUP,
	typeOBJ,
	typeOBJECTS,
	typePAGESETUP,
	typePHONETICINFO,
	typePICF,
	typePIVOTADDL,
	typePIVOTCACHE,
	typePIVOTCACHEDEFINITION,
	typePIVOTCORE,
	typePIVOTEX,
	typePIVOTFORMAT,
	typePIVOTFRT,
	typePIVOTFRT9,
	typePIVOTIVD,
	typePIVOTLI,
	typePIVOTPI,
	typePIVOTRULE,
	typePIVOTSELECT,
	typePIVOTTH,
	typePIVOTVD,
	typePIVOTVDTEX,
	typePIVOTVIEW,
	typePIVOTVIEWEX,
	typePRFILTER,
	typePROTECTION,
	typePROTECTION_COMMON,
	typeQSIR,
	typeQUERYTABLE,
	typeRECORD12,
	typeRTD,
	typeSCENARIOS,
	typeSERIESAXIS,
	typeSERIESDATA,
	typeSERIESFORMAT,
	typeSHAPEPROPS,
	typeSHAREDSTRINGS,
	typeSHFMLA_SET,
	typeSORT,
	typeSORTANDFILTER,
	typeSORTDATA12,
	typeSS,
	typeSTYLES,
	typeSUB,
	typeSUPBOOK,
	typeSXADDLAUTOSORT,
	typeSXADDLCACHE,
	typeSXADDLCACHE12,
	typeSXADDLCACHEFIELD,
	typeSXADDLCACHEITEM,
	typeSXADDLCALCMEMBER,
	typeSXADDLCONDFMT,
	typeSXADDLCONDFMTS,
	typeSXADDLDBQUERY,
	typeSXADDLFIELD,
	typeSXADDLFIELD12,
	typeSXADDLGROUP,
	typeSXADDLGRPLEVEL,
	typeSXADDLHIERARCHY,
	typeSXADDLQSI,
	typeSXADDLSXDH,
	typeSXADDLSXFILT,
	typeSXADDLSXFILTER12,
	typeSXADDLSXFILTERS12,
	typeSXADDLSXMG,
	typeSXADDLSXMGS,
	typeSXADDLSXRULE,
	typeSXDB,
	typeSXDBEx,
	typeSxBool,
	typeSxErr,
	typeSxNil,
	typeSxIsxoper,
	typeSXFDBType,
	typeSXRng,
	typeSxName,
	typeSXDtr,
	typeSXInt,
	typeSXNum,
	typeSXPair,
	typeSXFormula,
	typeSxFmla,
	typeSXFDB,
	typeSXFORMULA,
	typeSXFMLA,
	typeSXDBB,
	typeSXOPER,
	typeSXRANGE,
	typeFDB,
	typeDBB,
	//typeGRPSXOPER,
	//typeSRCSXOPER,
	typeSXSRC,
	typeSXTBL,
	typeTABLESTYLES,
	typeTEXTOBJECT,
	typeTEXTPROPS,
	typeTHEME,
	typeUNKNOWNFRT,
	typeWINDOW,
	typeXFS,
	typeAnySubstream,
	typeChartSheetSubstream,
	typeABNFParenthesis,
	typeGlobalsSubstream,
	typeMacroSheetSubstream,
	typeWorkbookStreamObject,
	typeWorksheetSubstream,

	typeBiffStructure = 2000,
	typeBopPopCustomPiesIndices,
	typeIXFCellMulBlankSpecial,
	typeAddinUdf,
	typeAF12CellIcon,
	typeAF12Criteria,
	typeAFDOper,
	typeAFDOperRk,
	typeAFDOperBoolErr,
	typeAFDOperXNum,
	typeAFDOperStr,
	typeBes,
	typeBiffString,
	typeBiffAttribute,
	typeFixedPoint,
	typeFormulaValue,
	typeChartNumNillable,
	typeBookExt_Conditional11,
	typeBookExt_Conditional12,
	typeBuiltInStyle,
	typeCachedDiskHeader,
	typeCell,
	typeCellOffsetResender,
	typeCellRangeRef,
	typeCellRef,
	typeCellXF,
	typeCFColor,
	typeCFExNonCF12,
	typeCFExTemplateParams,
	typeCFMStateItem,
	typeCFMultistate,
	typeCFDatabar,
	typeCFGradient,
	typeCFVO,
	typeCondFmtStructure,
	typeControlInfo,
	typeDropDownObjId,
	typeDXFALC,
	typeDXFBdr,
	typeDXFFntD,
	typeDXFId,
	typeDXFN,
	typeDXFN12,
	typeDXFN12List,
	typeDXFNum,
	typeDXFNumUsr,
	typeDXFPat,
	typeDXFProt,
	typeEnhancedProtection,
	typeExternDdeLinkNoOper,
	typeExternDocName,
	typeExternOleDdeLink,
	typeExtProp,
	typeExtRst,
	typeFactoidData,
	typeFeat11FdaAutoFilter,
	typeFeat11FieldDataItem,
	typeFeat11RgSharepointIdDel,
	typeFeat11RgSharepointIdChange,
	typeFeat11RgInvalidCells,
	typeFeat11XMapEntry2,
	typeFeat11XMapEntry,
	typeFeat11XMap,
	typeFeat11Fmla,
	typeFeat11WSSListInfo,
	typeFeatFormulaErr2,
	typeFeatProtection,
	typeFeatSmartTag,
	typeFileOffset,
	typeFilePointer,
	typeFormatRun,
	typeFrtHeader,
	typeFrtHeaderOld,
	typeFrtRefHeader,
	typeFrtRefHeaderNoGrbit,
	typeFrtRefHeaderU,
	typeFtCblsData,
	typeFtCf,
	typeFtCmo,
	typeFtEdoData,
	typeFtGboData,
	typeFtLbsData,
	typeFtMacro,
	typeFtNts,
	typeFtPictFmla,
	typeFtPioGrbit,
	typeFtRboData,
	typeFtSbs,
	typeFullColorExt,
	typeGradStop,
	typeHiddenMemberSet,
	typeHorzBrk,
	typeISSTInf,
	typeLbsDropData,
	typeList12BlockLevel,
	typeList12DisplayName,
	typeList12TableStyleClientInfo,
	typeLongRGBA,
	typeMDir,
	typeMDXStrIndex,
	typeMOper,
	typeNoteRR,
	typeNoteSh,
	typeObjFmla,
	typeObjLinkFmla,
	typeParsedFormula,
	typePhRuns,
	typePhs,
	typePictFmlaEmbedInfo,
	typePictFmlaKey,
	typePtg,
	typeRevItab,
	typeRevLblName,
	typeRevNamePly,
	typeRgbExtra,
	typeRgce,
	typeRkRec,
	typeRPHSSub,
	typeRRD,
	typeRun,
	typeSDContainer,
	typeSecurityDescriptor,
	typeSerAr,
	typeSheetExtOptional,
	typeSheetId,
	typeSortCond12,
	typeSqRef,
	typeSqRefU,
	typeStxp,
	typeStyleXF,
	typeTableFeatureType,
	typeTxOLastRun,
	typeTxORuns,
	typeVertBrk,
	typeXFExtGradient,
	typeXFExtNoFRT,
	typeXFProp,
	typeXFPropBorder,
	typeXFPropColor,
	typeXFPropGradient,
	typeXFPropGradientStop,
	typeXFProps,
	typeXLUnicodeRichExtendedString,
	typeXORObfuscation,
	typeXTI,
	typeXnum,
	
	typeIMsoArray,
	typeMSOCR,
	typeMSOSHADECOLOR,
	typeAntiMoniker,
	typeVersion,
	typeCompositeMoniker,
	typeEncryptionHeader,
	typeEncryptionHeaderFlags,
	typeEncryptionVerifier,
	typeFactoidType,
	typeFileMoniker,
	typeHyperlinkMoniker,
	typeHyperlinkObject,
	typeItemMoniker,
	typeProperty,
	typePropertyBag,
	typePropertyBagStore,
	typeRC4CryptoAPIEncryptionHeader,
	typeRC4EncryptionHeader,
	typeURICreateFlags,
	typeURLMoniker,
	typeXlsFilter_Top10,
	typeXlsFilter_Criteria,
	typeSXEZDoper,

	typeOfficeArtRecord = 3000,
	typeOfficeArtBStoreContainerFileBlock,
	typeOfficeArtDgContainer,
	typeOfficeArtDggContainer,
	typeOfficeArtCOLORREF,
	typeOfficeArtFOPTE,
	typeOfficeArtFRIT,
	typeOfficeArtIDCL,
	typeOfficeArtMetafileHeader,
	typeOfficeArtRecordHeader,
	typeOfficeArtRGFOPTE,
	typeOfficeArtBlip,
	typeOfficeArtSpContainer,
	typeOfficeArtSpgrContainer,
	typeOfficeArtBStoreContainer,
	typeOfficeArtClientAnchorChart,
	typeOfficeArtClientAnchorHF,
	typeOfficeArtClientAnchorSheet,
	typeOfficeArtChildAnchor,
	typeOfficeArtColorMRUContainer,
	typeOfficeArtContainer,
	typeOfficeArtFDG,
	typeOfficeArtFDGGBlock,
	typeOfficeArtFOPT,
	typeOfficeArtFRITContainer,
	typeOfficeArtFSP,
	typeOfficeArtFSPGR,
	typeOfficeArtSplitMenuColorContainer,
	typeOfficeArtTertiaryFOPT,
	typeOfficeArtClientData,
    typeOfficeArtClientTextbox,

    //xlsb static const XLS::ElementType	type = XLS::typeSLICERCACHEOLAPIMPL;
    typeCONDITIONALFORMATTING = 4000,
    typeCONDITIONALFORMATTING14,
    typeBeginConditionalFormatting,
    typeBeginConditionalFormatting14,
    typeCFRULE,
    typeCFRULE14,
    typeBeginCFRule,
    typeBeginCFRule14,
    typeuCFVO,
    typeuCFVO14,
    typeCFVO14,
    typeCOLORSCALE,
    typeCOLORSCALE14,
    typeDATABAR,
    typeBeginDatabar,
    typeDATABAR14,
    typeBeginDatabar14,
    typeICONSET,
    typeBeginIconSet,
    typeICONSET14,
    typeBeginIconSet14,
    typeACFMT,
    typeFmt,
    typeFRTDXF,
    typeFRTWORKSHEET,
    typeFRTSTYLESHEET,
    typeuDXF,
    typeDXF14,
    typeCUSTOMRICHFILTERS,
    typeRICHFILTERS,
    typeDynamicRichFilter,
    typeTop10RichFilter,
    typeRICHFILTERCONTENT,
    typeACICONFILTER,
    typeACFILTERS,
    typeACCUSTOMFILTER,
    typeCUSTOMFILTERS,
    typeFILTERS,
    typeACFILTERCONTENT,
    typeDynamicFilter,
    typeTop10Filter,
    typeColorFilter,
    typeIconFilter,
    typeFRTTABLE,
    typeSUPSAME,
    typeSUPADDIN,
    typeSupBookSrc,
	typeSupSelf,
    typeDVALS,
    typeDVALS14,
    typeDVal14,
    typeBeginDVals,
    typeBeginDVals14,
    typeFRTQSI,
    typeFRTEXTCONNECTIONS,
    typeEXTCONNECTION,
    typeEXTCONN14,
    typeEXTCONN15,
    typeBeginExtConnection,
    typeBeginExtConn14,
    typeBeginExtConn15,
    typeRangePr15,
    typeSLICERCACHEOLAPIMPL,
    typeSLICERCACHENATIVEITEMS,
    typeFRTSLICERCACHE,
    typeSLICERSEX,
    typeTABLESLICERSEX,
    typeSLICEREX,
    typeTABLESLICEREX,
    typeFRTWORKBOOK,
    typeRWBRK,
    typeCOLBRK,
    typeBeginRwBrk,
    typeBeginColBrk,
    typeRangeProtection,
    typeRangeProtectionIso,
    typeCsProtection,
    typeCsProtectionIso,
    typeSheetProtection,
    typeSheetProtectionIso,
    typeCSVIEWS,
    typeCSVIEW,
    typeBeginCsView,
    typeWSVIEWS2,
    typeWSVIEW2,
    typeBeginWsView,
    typeCsPageSetup,
    typePageSetup,
    typeCsProp,
    typeWsProp,
    typePCRRecord,
    typePIVOTCACHERECORDDT,
    typePCDIMissing,
    typePCDINumber,
    typePCDIBoolean,
    typePCDIError,
    typePCDIString,
    typePCDIDatetime,
    typePCDIIndex,
    typePCDIAMissing,
    typePCDIANumber,
    typePCDIABoolean,
    typePCDIAError,
    typePCDIAString,
    typePCDIADatetime,
    typePIVOTFILTERS,
    typeBeginSXView,
    typeEndSXView,
    typeBeginSXView14,
    typeEndSXView14,
    typeSXCONDFMTS,
    typeBeginSXCondFmts,
    typeEndSXCondFmts,
    typeSXCONDFMTS14,
    typeBeginSXCondFmts14,
    typeEndSXCondFmts14,
    typeSXCONDFMT,
    typeBeginSXCondFmt,
    typeEndSXCondFmt,
    typeSXCONDFMT14,
    typeBeginSXCondFmt14,
    typeEndSXCondFmt14,
    typeBeginSXRules,
    typeEndSXRules,
    typeBeginSXRules14,
    typeEndSXRules14,
    typeBeginPRule,
    typeEndPRule,
    typeBeginPRule14,
    typeEndPRule14,
    typeBeginPRFilters,
    typeEndPRFilters,
    typeBeginPRFilters14,
    typeEndPRFilters14,
    typeBeginPRFilter,
    typeEndPRFilter,
    typeBeginPRFilter14,
    typeEndPRFilter14,
    typeBeginPRFItem,
    typeEndPRFItem,
    typeBeginPRFItem14,
    typeEndPRFItem14,
    typeSxvcellNum,
    typeSxvcellStr,
    typeSxvcellErr,
    typeSxvcellBool,
    typeSxvcellDate,
    typeSxvcellNil,
    typeBeginSXView16,
    typeEndSXView16,
    typePIVOTRULES,
    typePIVOTRULES14,
    typePIVOTRULE14,
    typePRFILTERS,
    typePRFILTERS14,
    typePRFILTER14,
    typePRFITEM,
    typePRFITEM14,
    typeBeginPivotCacheDef,
    typePCDIRUN,
    typePCDI,
    typePCDIA,
    typeISXVDRWS,
    typeBeginISXVDRws,
    typeISXVDCOLS,
    typeBeginISXVDCols,
    typeSXLIRWS,
    typeSXLICOLS,
    typePCDIDT,
    typeFRTPIVOTCACHEDEF,
    typePCD14,
    typeTABLECELL,
    typeDATACELL,
    typeFMLACELL,
    typeSHRFMLACELL,
	typeBookProtection,
	typeBookProtectionIso,
	typeBeginSortCond,
	typeBeginSortCond14,
	typeSLICERCACHEIDS,
	typeTABLESLICERCACHEIDS,
	typeSLICERCACHEID,
	typeTABLESLICERCACHEID,
};



}
