﻿/*
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

#define AVS_OFFICESTUDIO_FILE_UNKNOWN					0x0000

#define AVS_OFFICESTUDIO_FILE_DOCUMENT					0x0040
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOCX				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0001
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOC				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0002
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_ODT				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0003
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_RTF				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0004
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_TXT				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0005
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_HTML				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0006
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_MHT				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0007
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_EPUB				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0008
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_FB2				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0009
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_MOBI				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x000a
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOCM				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x000b
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOTX				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x000c
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOTM				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x000d
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_ODT_FLAT			AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x000e
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_OTT				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x000f
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOC_FLAT			AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0010
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOCX_FLAT		AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0011
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_HTML_IN_CONTAINER AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0012
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOCX_PACKAGE		AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0014
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_OFORM			AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0015
#define AVS_OFFICESTUDIO_FILE_DOCUMENT_DOCXF			AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0016

#define AVS_OFFICESTUDIO_FILE_DOCUMENT_XML				AVS_OFFICESTUDIO_FILE_DOCUMENT + 0x0030

#define AVS_OFFICESTUDIO_FILE_PRESENTATION				0x0080
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_PPTX			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0001
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_PPT			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0002
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_ODP			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0003
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_PPSX			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0004
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_PPTM			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0005
#define	AVS_OFFICESTUDIO_FILE_PRESENTATION_PPSM			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0006
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_POTX			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0007
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_POTM			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0008
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_ODP_FLAT		AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x0009
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_OTP			AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x000a
#define AVS_OFFICESTUDIO_FILE_PRESENTATION_PPTX_PACKAGE	AVS_OFFICESTUDIO_FILE_PRESENTATION + 0x000b

#define AVS_OFFICESTUDIO_FILE_SPREADSHEET				0x0100
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLSX			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0001
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLS			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0002
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_ODS			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0003
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_CSV			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0004
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLSM			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0005
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLTX			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0006
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLTM			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0007

#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLSB			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0008
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_ODS_FLAT		AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x0009
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_OTS			AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x000a
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLSX_FLAT		AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x000b
#define AVS_OFFICESTUDIO_FILE_SPREADSHEET_XLSX_PACKAGE	AVS_OFFICESTUDIO_FILE_SPREADSHEET + 0x000c

#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM				0x0200
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_PDF			AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0001
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_SWF			AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0002
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_DJVU		AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0003
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_XPS			AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0004
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_SVG			AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0005
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_HTMLR		AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0006
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_HTMLRMenu	AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0007
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_HTMLRCanvas	AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0008
#define AVS_OFFICESTUDIO_FILE_CROSSPLATFORM_PDFA		AVS_OFFICESTUDIO_FILE_CROSSPLATFORM + 0x0009

#define AVS_OFFICESTUDIO_FILE_IMAGE						0x0400
#define AVS_OFFICESTUDIO_FILE_IMAGE_JPG					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0001
#define AVS_OFFICESTUDIO_FILE_IMAGE_TIFF				AVS_OFFICESTUDIO_FILE_IMAGE + 0x0002
#define AVS_OFFICESTUDIO_FILE_IMAGE_TGA					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0003
#define AVS_OFFICESTUDIO_FILE_IMAGE_GIF					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0004
#define AVS_OFFICESTUDIO_FILE_IMAGE_PNG					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0005
#define AVS_OFFICESTUDIO_FILE_IMAGE_EMF					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0006
#define AVS_OFFICESTUDIO_FILE_IMAGE_WMF					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0007
#define AVS_OFFICESTUDIO_FILE_IMAGE_BMP					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0008
#define AVS_OFFICESTUDIO_FILE_IMAGE_CR2					AVS_OFFICESTUDIO_FILE_IMAGE + 0x0009
#define AVS_OFFICESTUDIO_FILE_IMAGE_PCX					AVS_OFFICESTUDIO_FILE_IMAGE + 0x000a
#define AVS_OFFICESTUDIO_FILE_IMAGE_RAS					AVS_OFFICESTUDIO_FILE_IMAGE + 0x000b
#define AVS_OFFICESTUDIO_FILE_IMAGE_PSD					AVS_OFFICESTUDIO_FILE_IMAGE + 0x000c
#define AVS_OFFICESTUDIO_FILE_IMAGE_ICO					AVS_OFFICESTUDIO_FILE_IMAGE + 0x000d

#define AVS_OFFICESTUDIO_FILE_OTHER						0x0800
#define AVS_OFFICESTUDIO_FILE_OTHER_EXTRACT_IMAGE		AVS_OFFICESTUDIO_FILE_OTHER + 0x0001
#define AVS_OFFICESTUDIO_FILE_OTHER_MS_OFFCRYPTO		AVS_OFFICESTUDIO_FILE_OTHER + 0x0002
#define AVS_OFFICESTUDIO_FILE_OTHER_HTMLZIP				AVS_OFFICESTUDIO_FILE_OTHER + 0x0003
#define AVS_OFFICESTUDIO_FILE_OTHER_OLD_DOCUMENT		AVS_OFFICESTUDIO_FILE_OTHER + 0x0004
#define AVS_OFFICESTUDIO_FILE_OTHER_OLD_PRESENTATION	AVS_OFFICESTUDIO_FILE_OTHER + 0x0005
#define AVS_OFFICESTUDIO_FILE_OTHER_OLD_DRAWING			AVS_OFFICESTUDIO_FILE_OTHER + 0x0006
#define AVS_OFFICESTUDIO_FILE_OTHER_TEAMLAB_INNER		AVS_OFFICESTUDIO_FILE_OTHER + 0x0007
#define AVS_OFFICESTUDIO_FILE_OTHER_JSON				AVS_OFFICESTUDIO_FILE_OTHER + 0x0008               // Для mail-merge
#define AVS_OFFICESTUDIO_FILE_OTHER_ZIP					AVS_OFFICESTUDIO_FILE_OTHER + 0x0009
#define AVS_OFFICESTUDIO_FILE_OTHER_ODF					AVS_OFFICESTUDIO_FILE_OTHER + 0x000a
#define AVS_OFFICESTUDIO_FILE_OTHER_MS_MITCRYPTO		AVS_OFFICESTUDIO_FILE_OTHER + 0x000b
#define AVS_OFFICESTUDIO_FILE_OTHER_MS_VBAPROJECT		AVS_OFFICESTUDIO_FILE_OTHER + 0x000c
#define AVS_OFFICESTUDIO_FILE_OTHER_COMPOUND			AVS_OFFICESTUDIO_FILE_OTHER + 0x000d

#define AVS_OFFICESTUDIO_FILE_TEAMLAB					0x1000
#define AVS_OFFICESTUDIO_FILE_TEAMLAB_DOCY				AVS_OFFICESTUDIO_FILE_TEAMLAB + 0x0001
#define AVS_OFFICESTUDIO_FILE_TEAMLAB_XLSY				AVS_OFFICESTUDIO_FILE_TEAMLAB + 0x0002
#define AVS_OFFICESTUDIO_FILE_TEAMLAB_PPTY				AVS_OFFICESTUDIO_FILE_TEAMLAB + 0x0003

#define AVS_OFFICESTUDIO_FILE_CANVAS					0x2000
#define AVS_OFFICESTUDIO_FILE_CANVAS_WORD				AVS_OFFICESTUDIO_FILE_CANVAS + 0x0001
#define AVS_OFFICESTUDIO_FILE_CANVAS_SPREADSHEET		AVS_OFFICESTUDIO_FILE_CANVAS + 0x0002
#define AVS_OFFICESTUDIO_FILE_CANVAS_PRESENTATION		AVS_OFFICESTUDIO_FILE_CANVAS + 0x0003
#define AVS_OFFICESTUDIO_FILE_CANVAS_PDF				AVS_OFFICESTUDIO_FILE_CANVAS + 0x0004
