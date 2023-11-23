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

#include <map>
#include <string>
#include <algorithm>
#include <math.h>

#include "Constants.h"
#include "../../../DesktopEditor/common/Types.h"
#include "../../DocxFormat/Logic/Paragraph.h"

/*#include "Logic\Color.h"
#include "Logic\ColorsTable.h"*/

#include "OfficeArt/Common.h"
#include "OfficeArt/Enumerations.h"

#define DPI_DEFAULT		72.0

namespace DOCX
{
	class CPointF
	{
	public:

		CPointF () : m_X (0), m_Y (0), m_TX (0), m_TY (0), m_fCorrection (65536.0)
		{

		}

		CPointF (unsigned int dX, unsigned int dY) : m_X (dX), m_Y (dY), m_TX (0), m_TY (0), m_fCorrection (65536.0)
		{

		}

		CPointF (const std::string& value) : m_X (0), m_Y (0), m_TX (0), m_TY (0), m_fCorrection (65536.0)
		{
			if (0 == value.length())
				return;

			std::string strText	=	value;

			strText.erase(std::remove(strText.begin(), strText.end(), L' '), strText.end());

			double fT			=	1.0;		//	

			//	MM

			size_t from			=	strText.find("mm");
			if (std::string::npos != from)
			{
				strText.erase(std::remove(strText.begin(), strText.end(), L'm'), strText.end());

				m_fCorrection	=	36000;
				fT				=	(DPI_DEFAULT * 20.0) / 25.399931;
			}

			// PT

			from				=	strText.find("pt");
			if (std::string::npos != from)
			{
				strText.erase(std::remove(strText.begin(), strText.end(), L'p'), strText.end());
				strText.erase(std::remove(strText.begin(), strText.end(), L't'), strText.end());

				m_fCorrection	=	12700.0;
				fT				=	20.0;
			}

			// DEF

			from				=	strText.find(',');
			if (std::string::npos != from)
			{
				if (0 == from)
				{
					if (1 == (int)strText.length())
						return;			

					double dX	=	atof (strText.c_str());

					strText		=	strText.substr(from + 1, ((int)strText.length() - 1) - from);
					m_Y			=	(unsigned int)(dX * m_fCorrection);

					m_TX		=	(int)(dX * fT);

					return;
				}

				double dX		=	atof (strText.substr(0, from).c_str());

				m_X				=	FormatNum (dX, m_fCorrection);
				m_TX			=	(int)(dX * fT);

				strText			=	strText.substr(from + 1, ((int)strText.length() - 1) - from);
				if (0 == (int)strText.length())
					return;

				double dY		=	atof (strText.c_str());
				m_Y				=	FormatNum (strText, m_fCorrection);
				m_TY			=	(int)(dY * fT);

				return;
			}

			if (strText.length())
			{
				double dX		=	atof (strText.c_str());
				m_X				=	(unsigned int)(dX * m_fCorrection);
				m_TX			=	(int)(dX * fT);
			}
		}

		inline unsigned int X () const 
		{
			return m_X;
		}

		inline unsigned int Y () const 
		{
			return m_Y;
		}

		inline int GetTX() const
		{
			return	m_TX;
		}

		inline int GetTY() const
		{
			return	m_TY;
		}

	private:

		inline unsigned int ToFixed(double dNumber) const
		{
			if (dNumber < 0.0)
			{		
				return (unsigned int)(((long)dNumber - dNumber) * 65536.0) | (0xffff << 16);
			}	

			if (dNumber > 0.0)
			{
				return (unsigned int)((dNumber - (long)dNumber) * 65536.0);
			}

			return 0;
		}

		inline unsigned int FormatNum (const std::string& strVal, double dMul) const
		{
			return FormatNum (atof (strVal.c_str()), dMul);
		}

		inline unsigned int FormatNum (double dVal, double dMul) const
		{
			dVal	=	dVal * dMul;
			if (dVal > 0.0)
				dVal	+=	0.5;
			if (dVal < 0.0)
				dVal	-=	0.5;

			return (unsigned int)dVal;
		}

	private:

		unsigned int	m_X;
		unsigned int	m_Y;

		double			m_fCorrection;

		int				m_TX;
		int				m_TY;
	};

	class CFPoint
	{
	public:

		CFPoint () : m_dX(0.0), m_dY(0.0)
		{

		}

		CFPoint (const std::string& value, double dX, double dY) : m_dX(dX), m_dY(dY)
		{
			if (value.length())
			{
				std::string strText	= value;
				strText.erase(std::remove(strText.begin(), strText.end(), L' '), strText.end());
				if (strText.length())
				{
					size_t find = strText.find(',');
					if (std::string::npos != find)
					{
						m_dX = atof ((strText.substr(0, find)).c_str());

						strText	= strText.substr(find + 1, ((int)strText.length() - 1) - find);

						if (strText.length())
							m_dY = atof (strText.c_str());
					}
					else
					{
						m_dX = atof (strText.c_str());
					}
				}
			}
		}

		inline double X()
		{
			return m_dX;
		}

		inline double Y()
		{
			return m_dY;
		}

	private:

		double m_dX;
		double m_dY;
	};

	class CMatrixF
	{
	public:

		CMatrixF () : m_XToX (0), m_XToY(0), m_YToX(0), m_YToY(0), m_PX(0), m_PY(0)
		{		  

		}	

		CMatrixF (const std::string& str) : m_XToX (0), m_XToY(0), m_YToX(0), m_YToY(0), m_PX(0), m_PY(0)
		{		  
			if (0 == str.length())
				return;

			std::string strText		=	str;
			strText.erase(std::remove(strText.begin(), strText.end(), L' '), strText.end());

			//

			size_t from				=	strText.find(',');
			if (std::string::npos == from)
				return;

			if (0 != from)
			{
				std::string number	=	strText.substr(0, from);

				if (std::string::npos != number.find('f'))
					m_XToX			=	atoi (number.substr(0,number.length()-1).c_str());
				else
					m_XToX			=	ToFixed (atof (number.c_str()) );

				if (std::string::npos == from)
					return;
			}

			strText					=	strText.substr(from + 1, strText.length() - 1 - from);

			//

			from					=	strText.find(',');
			if (0 != from)
			{
				std::string number	=	strText.substr(0, from);

				if (std::string::npos != number.find('f'))
					m_YToX			=	atoi (number.substr(0,number.length()-1).c_str());
				else
					m_YToX			=	ToFixed (atof (number.c_str()) );

				if (std::string::npos == from)
					return;
			}

			strText					=	strText.substr(from + 1, strText.length() - 1 - from);

			//

			from					=	strText.find(',');
			if (0 != from)
			{
				std::string number	=	strText.substr(0, from);

				if (std::string::npos != number.find('f'))
					m_XToY			=	atoi (number.substr(0,number.length()-1).c_str());
				else
					m_XToY			=	ToFixed (atof (number.c_str()));

				if (std::string::npos == from)
					return;
			}

			strText					=	strText.substr(from + 1, strText.length() - 1 - from);

			//

			from					=	strText.find(',');
			if (0 != from)
			{
				std::string number	=	strText.substr(0, from);

				if (std::string::npos != number.find('f'))
					m_YToY			=	atoi (number.substr(0,number.length()-1).c_str());
				else
					m_YToY			=	ToFixed (atof (number.c_str()));

				if (std::string::npos == from)
					return;
			}

			strText					=	strText.substr(from + 1, strText.length() - 1 - from);

			//

			from					=	strText.find(',');
			if (0 != from)
			{
				std::string number	=	strText.substr(0, from);

				if (std::string::npos != number.find('f'))
					m_PX			=	atoi (number.substr(0,number.length()-1).c_str());
				else
					m_PX			=	ToPerspective (atof (number.c_str()));

				if (std::string::npos == from)
					return;
			}

			strText					=	strText.substr(from + 1, strText.length() - 1 - from);

			//

			from					=	strText.find(',');
			if (0 != from)
			{
				std::string number	=	strText.substr(0, from);

				double df			=	atof (number.c_str());

				if (std::string::npos != number.find('f'))
					m_PY			=	atoi (number.substr(0,number.length()-1).c_str());
				else
					m_PY			=	ToPerspective (atof (number.c_str()));
			}
		}

		inline unsigned int XToX () 
		{
			return m_XToX;
		}

		inline unsigned int XToY () 
		{
			return m_XToY;
		}

		inline unsigned int YToX () 
		{
			return m_YToX;
		}

		inline unsigned int YToY () 
		{
			return m_YToY;
		}

		inline unsigned int PX () 
		{
			return m_PX;
		}

		inline unsigned int PY () 
		{
			return m_PY;
		}

	private:

		unsigned int ToFixed(double dNumber)
		{
			if (dNumber < 0.0)
			{		
				return (unsigned int)(((long)dNumber - dNumber) * 65536.0) | (0xffff << 16);
			}	

			if (dNumber > 0.0)
			{
				//return (unsigned int)((dNumber - (long)dNumber) * 65536.0);
				return (unsigned int)(dNumber  * 65536.0);
			}

			return 0;
		}

		unsigned int ToPerspective(double dNumber)
		{
			static const double WEIGHT	=	256.0;		//	если сохраням матрицу как это делает Office 2010 (через свойства Shadow), то вес по умолчанию 0x00000100

			if (dNumber < 0.0)
			{		
				return 0xffffffff - (unsigned int)((-1.0 * dNumber * WEIGHT * 65536.0));
			}	

			if (dNumber > 0.0)
			{
				return (unsigned int)(dNumber * WEIGHT * 65536.0);
			}

			return 0;
		}

	private:		 

		unsigned m_XToX;
		unsigned m_XToY;
		unsigned m_YToX;
		unsigned m_YToY;
		unsigned m_PX;
		unsigned m_PY;
	};

	class CEmu
	{
	public:
		CEmu() : m_nVal(0)
		{

		}

		CEmu(const std::string& str) : m_nVal(0)
		{
			if (0 == str.length())
				return;

			std::string strText	=	str;

			int nCorrection	=	1;

			strText.erase(std::remove(strText.begin(), strText.end(), L' '), strText.end());

			size_t from			=	strText.find("mm");
			if (std::string::npos != from)
			{
				strText.erase(std::remove(strText.begin(), strText.end(), L'm'), strText.end());
				nCorrection		=	36000;
			}

			from				=	strText.find("pt");
			if (std::string::npos != from)
			{
				strText.erase(std::remove(strText.begin(), strText.end(), L'p'), strText.end());
				strText.erase(std::remove(strText.begin(), strText.end(), L't'), strText.end());

				nCorrection		=	12700;
			}

			m_nVal				=	atoi(str.c_str()) * nCorrection;
		}

		inline int Get()
		{
			return m_nVal;
		}

	private:

		int	m_nVal;
	};
}

namespace DOCXDOCUTILS
{
	/*inline unsigned char ColorToIco (const OOX::Logic::CColor& oColor)
	{
		OOX::Logic::ColorsTable colorsTable;

		std::string colorName	=	colorsTable.fromColor(oColor);
		if (std::string("auto" == colorName)
			colorName			=	std::string ("000000";

		std::map<std::string, BYTE> colorsMap;
		colorsMap.insert( std::std::pair<std::string, BYTE>( "auto", 0x00 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "black", 0x01 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "blue", 0x02 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "cyan", 0x03 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "green", 0x04 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "magenta", 0x05 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "red", 0x06 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "yellow", 0x07 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "white", 0x08 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "darkBlue", 0x09 ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "darkCyan", 0x0A ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "darkGreen", 0x0B ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "darkMagenta", 0x0C ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "darkRed", 0x0D ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "darkYellow", 0x0E ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "darkGray", 0x0F ) );
		colorsMap.insert( std::pair<std::string, BYTE>( "lightGray", 0x10 ) );

		return colorsMap[colorName];
	}*/

	inline unsigned char AlignFromString (const std::string& align)
	{
		//!!!TODO!!!
		if (align == std::string("left"))
			return 0;
		else if (align == std::string("center"))
			return 1;
		else if (align == std::string("right"))
			return 2;
		else if (align == std::string("both"))
			return 3;

		return 0;
	}

	inline short StiToIstd (short nDef)
	{
		if (nDef >= 0 && nDef <= 9)
			return nDef;

		if (65 == nDef)
			return 10;
		if (105 == nDef)
			return 11;
		if (107 == nDef)
			return 12;

		return -1;
	}
	inline static std::vector<int> GetValues(const std::string& strValues)
	{
		std::vector<int> values;
		if (strValues.empty())
			return values;

		int number = 0;
		std::string str = strValues;
		while(str.length())
		{
			size_t separator = str.find (',');
			if (std::string::npos != separator)
			{			
				std::string snumber = str.substr(0, separator);
				if (std::string::npos != snumber.find('f'))
					number = (int) (21600.0 * (atof (snumber.substr(0,snumber.length()-1).c_str()) / 65536.0));		//	????
				else
					number = atoi (snumber.c_str());

				values.push_back (number);
				str	= str.substr(separator + 1, str.length() - separator - 1);
			}
			else
			{
				if (std::string::npos != str.find('f'))
					number = atoi (str.substr(0,str.length()-1).c_str());
				else
					number = atoi (str.c_str());

				values.push_back (number);

				break;
			}
		}

		return values;
	}
}

namespace DOCXDOCUTILS
{
	inline unsigned int HexChar2Int (const char value)
	{
		if (value >= '0' && value <= '9')
			return value - '0';
		if (value >= 'a' && value <= 'f')
			return 10 + value - 'a';
		if (value >= 'A' && value <= 'F')
			return 10 + value - 'A';
		return 0;
	}

	inline unsigned int HexString2UInt (const std::wstring& value)
	{
		unsigned int summa = 0;
		for (int i = 0; i != value.size(); ++i)
			summa += HexChar2Int(value[i]) << (4 * (value.size() - i - 1));
		return summa;
	}

	inline unsigned int HexString2UInt2X (const std::string& value)
	{
		unsigned int summa = 0;
		for (int i = 0; i != value.size(); ++i)
		{
			summa += HexChar2Int(value[i]) << (4 * (value.size() - i - 1));
		}

		return summa;
	}

	inline unsigned int RGBToBGR (const unsigned int& nColor)
	{
		return ((nColor>>16) & 0xFF) | (0xFF00 & nColor) | (0xFF0000 & (nColor<<16));
	}

	inline int GetFillColor(const std::wstring& value, unsigned int& nColor)
	{
		nColor	=	0;

		if (value.length() >= 6)
		{
			int from = value.find(' ');
			if (-1 == from)
			{
				if ('#' == value[0])
				{
					nColor = RGBToBGR(HexString2UInt(value.substr(1,value.length()-1)));
					return TRUE;
				}

				nColor = RGBToBGR(HexString2UInt(value));
				return TRUE;
			}
			else
			{
				if ('#' == value[0])
				{
					nColor = RGBToBGR(HexString2UInt(value.substr(1,from-1)));
					return TRUE;
				}

				nColor = RGBToBGR(HexString2UInt(value));
				return TRUE;
			}
		}
		else
		{
			if ('#' == value[0] && 4 == value.length())		//	#cfc -> CCFFCC
			{
				nColor	=	0;

				nColor	+=	HexChar2Int(value[1]);
				nColor	+=	HexChar2Int(value[1]) << 4;

				nColor	+=	HexChar2Int(value[2]) << 8;
				nColor	+=	HexChar2Int(value[2]) << 12;

				nColor	+=	HexChar2Int(value[3]) << 16;
				nColor	+=	HexChar2Int(value[3]) << 20;

				return TRUE;
			}
		}

		return FALSE;
	}
	inline unsigned int GetFixePointValue (const std::string& value)
	{
		if (value.length() > 1)
		{
			std::string strText = value;

			if ('f' == strText[strText.length()-1] )
			{
				std::string number	=	strText.substr(0,strText.length()-1);
				if (number.length ())
					return atoi (number.c_str());
			}
			else
			{			
				return (unsigned int)(atof (strText.c_str()) * 65536.0);
			}
		}

		return 0;
	}

	inline static int GetArcValue(const std::string& strValue)
	{
		if (0==strValue.length())
			return 0;

		if (std::string::npos != strValue.find('f'))
		{
			return (int) (21600.0 * (atof (strValue.substr(0,strValue.length()-1).c_str()) / 65536.0));		//	????
		}
		else
		{
			return (int)(21600.0 * atof (strValue.c_str()));
		}

		return 0;
	}
	inline static unsigned int ToFixed2(double dNumber)
	{
		if (dNumber < 0.0)
		{		
			return (unsigned int)(((long)dNumber - dNumber) * 65536.0) | (0xffff << 16);
		}	

		if (dNumber > 0.0)
		{
			return (unsigned int)((dNumber - (long)dNumber) * 65536.0);
		}

		return 0;
	}

	inline static double GetAngleValue (const std::string& strValue)
	{
		size_t from		=	strValue.find("fd");
		if (std::string::npos != from)
		{
			std::string strText		=	strValue;

			strText.erase(std::remove(strText.begin(), strText.end(), L'f'), strText.end());
			strText.erase(std::remove(strText.begin(), strText.end(), L'd'), strText.end());

			return atof(strText.c_str()) / 65536.0;
		}

		return atof(strValue.c_str());
	}
}

namespace DOCXDOCUTILS	//	fonts
{	
	inline Docx2Doc::Constants::FontFamilyType FontFamilyFromString (const std::string& sFontFamily)
	{
		if (sFontFamily == std::string("auto"))
		{
			return Docx2Doc::Constants::fontFamilyTypeUnspecified;
		}
		else if (sFontFamily == std::string("roman"))
		{
			return Docx2Doc::Constants::fontFamilyTypeRomanSerif;
		}
		else if (sFontFamily == std::string("swiss"))
		{
			return Docx2Doc::Constants::fontFamilyTypeSwissSansSerif;
		}
		else if (sFontFamily == std::string("modern"))
		{
			return Docx2Doc::Constants::fontFamilyTypeModernMonospace;
		}
		else if (sFontFamily == std::string("script"))
		{
			return Docx2Doc::Constants::fontFamilyTypeScriptCursive;
		}
		else if (sFontFamily == std::string("decorative"))
		{
			return Docx2Doc::Constants::fontFamilyTypeDecorativeFantasy;
		}

		return Docx2Doc::Constants::fontFamilyTypeUnspecified;
	}

	inline Docx2Doc::Constants::CharacterPitch FontPitchFromString (const std::string& sPitch)
	{
		if (sPitch == std::string("variable"))
			return Docx2Doc::Constants::characterPitchVariable;
		else if (sPitch == std::string("fixed"))
			return Docx2Doc::Constants::characterPitchFixed;

		return Docx2Doc::Constants::characterPitchDefault;
	}

	inline unsigned char FontCharsetFromString (const std::string& Charset)
	{
		if (Charset == std::string("CC"))
			return RUSSIAN_CHARSET;
		else if (Charset == std::string("00"))
			return ANSI_CHARSET;
		else if (Charset == std::string("02"))
			return SYMBOL_CHARSET;
		else if (Charset == std::string("80"))
			return SHIFTJIS_CHARSET;
		else if (Charset == std::string("86"))
			return GB2312_CHARSET;

		return DEFAULT_CHARSET;  
	}
}

namespace DOCXDOCUTILS
{
	inline unsigned short GetStyleWrapType (const std::string& type) 
	{
		if (type == std::string("none"))
			return 3;
		if (type == std::string("topAndBottom"))
			return 1;
		if (type == std::string("square"))
			return 2;
		if (type == std::string("tight"))
			return 4;
		if (type == std::string("through"))
			return 5;

		return 0;
	}

}

namespace DOCXDOCUTILS
{
	inline bool GetFlipH (const std::string& strFlip)
	{
		if (strFlip.length())
		{
			if ((std::string::npos != strFlip.find('x')) || (std::string::npos != strFlip.find('1')))
				return true;
		}

		return false;
	}

	inline bool GetFlipV (const std::string& strFlip)
	{
		if (strFlip.length())
		{
			if ((std::string::npos != strFlip.find('y')) || (std::string::npos != strFlip.find('1')))
				return true;
		}

		return false;
	}
}

namespace DOCXDOCUTILS
{
	inline std::wstring GetInstrText_FieldCode(std::wstring InstrText, std::wstring& Source)
	{
		if (0 == InstrText.length())
			return std::wstring(L"");

		std::wstring instrText = InstrText;

		instrText.erase(std::remove(instrText.begin(), instrText.end(), L' '), instrText.end());

		if (L'H' == instrText[0])
		{
			std::wstring::size_type pos	= InstrText.find(L"HYPERLINK");

			if (std::wstring::npos != pos)
			{
				Source	=	InstrText.substr (pos + std::wstring(L"HYPERLINK").length(),InstrText.length() - pos + std::wstring(L"HYPERLINK").length() - 1);
				return std::wstring(L"HYPERLINK");
			}
		}

		if (L'P' == instrText[0])
		{
			if (std::wstring::npos != instrText.find(L"PAGEREF"))
				return std::wstring(L"PAGEREF");

			if (std::wstring::npos != instrText.find(L"PAGE"))
				return std::wstring(L"PAGE");
		}

		if (L'T' == instrText[0])
		{
			if (std::wstring::npos != instrText.find(L"TOC"))
				return std::wstring(L"TOC");
		}

		if (L'A' == instrText[0])
		{
			if (std::wstring::npos != instrText.find(L"ADDRESSBLOCK"))
				return std::wstring(L"ADDRESSBLOCK");
		}

		if (L'G' == instrText[0])
		{
			if (std::wstring::npos != instrText.find(L"GREETINGLINE"))
				return std::wstring(L"GREETINGLINE");
		}

		if (L'M' == instrText[0])
		{
			if (std::wstring::npos != instrText.find(L"MERGEFIELD"))
				return std::wstring(L"MERGEFIELD");
		}

		return std::wstring(L"");
	}	
}

namespace DOCX
{
	class CSColor
	{
	public:

		CSColor () :  m_nColor (0)
		{

		}

		inline int Init (const std::wstring& Color)
		{
			if (Color.length() <= 0)
				return FALSE;

			std::wstring color	=	std::wstring(Color.c_str());
			wchar_t wChar	=	color.at(0);
			switch (wChar)
			{
			case L'a':
				if      ( color.find( L"aliceBlue"			) >= 0) { m_nColor = RGB2(240,248,255);	return TRUE; }
				else if ( color.find( L"antiqueWhite"		) >= 0) { m_nColor = RGB2(250,235,215);	return TRUE; }
				else if ( color.find( L"aqua"				) >= 0) { m_nColor = RGB2(0,255,255);	return TRUE; }
				else if ( color.find( L"aquamarine"			) >= 0) { m_nColor = RGB2(127,255,212);	return TRUE; }
				else if ( color.find( L"azure"				) >= 0) { m_nColor = RGB2(240,255,255);	return TRUE; }
				break;
			case L'b':
				if      ( color.find( L"beige"				) >= 0) { m_nColor = RGB2(245,245,220);	return TRUE; }
				else if ( color.find( L"bisque"				) >= 0) { m_nColor = RGB2(255,228,196);	return TRUE; }
				else if ( color.find( L"black"				) >= 0) { m_nColor = RGB2(0,0,0);		return TRUE; }
				else if ( color.find( L"blanchedAlmond"		) >= 0) { m_nColor = RGB2(255,235,205);	return TRUE; }
				else if ( color.find( L"blue"				) >= 0) { m_nColor = RGB2(0,0,255);		return TRUE; }
				else if ( color.find( L"blueViolet"			) >= 0) { m_nColor = RGB2(138,43,226);	return TRUE; }
				else if ( color.find( L"brown"				) >= 0) { m_nColor = RGB2(165,42,42);	return TRUE; }
				else if ( color.find( L"burlyWood"			) >= 0) { m_nColor = RGB2(222,184,135);	return TRUE; }
				break;
			case L'c':
				if      ( color.find( L"cadetBlue"			) >= 0) { m_nColor = RGB2(95,158,160);	return TRUE; }
				else if ( color.find( L"chartreuse"			) >= 0) { m_nColor = RGB2(127,255,0);	return TRUE; }
				else if ( color.find( L"chocolate"			) >= 0) { m_nColor = RGB2(210,105,30);	return TRUE; }
				else if ( color.find( L"coral"				) >= 0) { m_nColor = RGB2(255,127,80);	return TRUE; }
				else if ( color.find( L"cornflowerBlue"		) >= 0) { m_nColor = RGB2(100,149,237);	return TRUE; }
				else if ( color.find( L"cornsilk"			) >= 0) { m_nColor = RGB2(255,248,220);	return TRUE; }
				else if ( color.find( L"crimson"				) >= 0) { m_nColor = RGB2(220,20,60);	return TRUE; }
				else if ( color.find( L"cyan"				) >= 0) { m_nColor = RGB2(0,255,255);	return TRUE; }
				break;
			case L'd':
				if      ( color.find( L"darkBlue"			) >= 0) { m_nColor = RGB2(0,0,139);		return TRUE; }
				else if ( color.find( L"darkCyan"			) >= 0) { m_nColor = RGB2(0,139,139);	return TRUE; }
				else if ( color.find( L"darkGoldenrod"		) >= 0) { m_nColor = RGB2(184,134,11);	return TRUE; }
				else if ( color.find( L"darkGray"			) >= 0) { m_nColor = RGB2(169,169,169);	return TRUE; }
				else if ( color.find( L"darkGreen"			) >= 0) { m_nColor = RGB2(0,100,0);		return TRUE; }
				else if ( color.find( L"darkGrey"			) >= 0) { m_nColor = RGB2(169,169,169);	return TRUE; }
				else if ( color.find( L"darkKhaki"			) >= 0) { m_nColor = RGB2(189,183,107);	return TRUE; }
				else if ( color.find( L"darkMagenta"			) >= 0) { m_nColor = RGB2(139,0,139);	return TRUE; }
				else if ( color.find( L"darkOliveGreen"		) >= 0) { m_nColor = RGB2(85,107,47);	return TRUE; }
				else if ( color.find( L"darkOrange"			) >= 0) { m_nColor = RGB2(255,140,0);	return TRUE; }
				else if ( color.find( L"darkOrchid"			) >= 0) { m_nColor = RGB2(153,50,204);	return TRUE; }
				else if ( color.find( L"darkRed"				) >= 0) { m_nColor = RGB2(139,0,0);		return TRUE; }
				else if ( color.find( L"darkSalmon"			) >= 0) { m_nColor = RGB2(233,150,122);	return TRUE; }
				else if ( color.find( L"darkSeaGreen"		) >= 0) { m_nColor = RGB2(143,188,143);	return TRUE; }
				else if ( color.find( L"darkSlateBlue"		) >= 0) { m_nColor = RGB2(72,61,139);	return TRUE; }
				else if ( color.find( L"darkSlateGray"		) >= 0) { m_nColor = RGB2(47,79,79);	return TRUE; }
				else if ( color.find( L"darkSlateGrey"		) >= 0) { m_nColor = RGB2(47,79,79);	return TRUE; }
				else if ( color.find( L"darkTurquoise"		) >= 0) { m_nColor = RGB2(0,206,209);	return TRUE; }
				else if ( color.find( L"darkViolet"			) >= 0) { m_nColor = RGB2(148,0,211);	return TRUE; }
				else if ( color.find( L"deepPink"			) >= 0) { m_nColor = RGB2(255,20,147);	return TRUE; }
				else if ( color.find( L"deepSkyBlue"			) >= 0) { m_nColor = RGB2(0,191,255);	return TRUE; }
				else if ( color.find( L"dimGray"				) >= 0) { m_nColor = RGB2(105,105,105);	return TRUE; }
				else if ( color.find( L"dimGrey"				) >= 0) { m_nColor = RGB2(105,105,105);	return TRUE; }
				else if ( color.find( L"dkBlue"				) >= 0) { m_nColor = RGB2(0,0,139);		return TRUE; }
				else if ( color.find( L"dkCyan"				) >= 0) { m_nColor = RGB2(0,139,139);	return TRUE; }
				else if ( color.find( L"dkGoldenrod"			) >= 0) { m_nColor = RGB2(184,134,11);	return TRUE; }
				else if ( color.find( L"dkGray"				) >= 0) { m_nColor = RGB2(169,169,169);	return TRUE; }
				else if ( color.find( L"dkGreen"				) >= 0) { m_nColor = RGB2(0,100,0);		return TRUE; }
				else if ( color.find( L"dkGrey"				) >= 0) { m_nColor = RGB2(169,169,169);	return TRUE; }
				else if ( color.find( L"dkKhaki"				) >= 0) { m_nColor = RGB2(189,183,107);	return TRUE; }
				else if ( color.find( L"dkMagenta"			) >= 0) { m_nColor = RGB2(139,0,139);	return TRUE; }
				else if ( color.find( L"dkOliveGreen"		) >= 0) { m_nColor = RGB2(85,107,47);	return TRUE; }
				else if ( color.find( L"dkOrange"			) >= 0) { m_nColor = RGB2(255,140,0);	return TRUE; }
				else if ( color.find( L"dkOrchid"			) >= 0) { m_nColor = RGB2(153,50,204);	return TRUE; }
				else if ( color.find( L"dkRed"				) >= 0) { m_nColor = RGB2(139,0,0);		return TRUE; }
				else if ( color.find( L"dkSalmon"			) >= 0) { m_nColor = RGB2(233,150,122);	return TRUE; }
				else if ( color.find( L"dkSeaGreen"			) >= 0) { m_nColor = RGB2(143,188,139);	return TRUE; }
				else if ( color.find( L"dkSlateBlue"			) >= 0) { m_nColor = RGB2(72,61,139);	return TRUE; }
				else if ( color.find( L"dkSlateGray"			) >= 0) { m_nColor = RGB2(47,79,79);	return TRUE; }
				else if ( color.find( L"dkSlateGrey"			) >= 0) { m_nColor = RGB2(47,79,79);	return TRUE; }
				else if ( color.find( L"dkTurquoise"			) >= 0) { m_nColor = RGB2(0,206,209);	return TRUE; }
				else if ( color.find( L"dkViolet"			) >= 0) { m_nColor = RGB2(148,0,211);	return TRUE; }
				else if ( color.find( L"dodgerBlue"			) >= 0) { m_nColor = RGB2(30,144,255);	return TRUE; }
				break;
			case L'f':
				if      ( color.find( L"firebrick"			) >= 0) { m_nColor = RGB2(178,34,34);	return TRUE; }
				else if ( color.find( L"floralWhite"			) >= 0) { m_nColor = RGB2(255,250,240);	return TRUE; }
				else if ( color.find( L"forestGreen"			) >= 0) { m_nColor = RGB2(34,139,34);	return TRUE; }
				else if ( color.find( L"fuchsia"				) >= 0) { m_nColor = RGB2(255,0,255);	return TRUE; }
				break;	   
			case L'g':
				if      ( color.find( L"gainsboro"			) >= 0) { m_nColor = RGB2(220,220,220);	return TRUE; }
				else if ( color.find( L"ghostWhite"			) >= 0) { m_nColor = RGB2(248,248,255);	return TRUE; }
				else if ( color.find( L"gold"				) >= 0) { m_nColor = RGB2(255,215,0);	return TRUE; }
				else if ( color.find( L"goldenrod"			) >= 0) { m_nColor = RGB2(218,165,32);	return TRUE; }
				else if ( color.find( L"gray"				) >= 0) { m_nColor = RGB2(128,128,128);	return TRUE; }
				else if ( color.find( L"green"				) >= 0) { m_nColor = RGB2(0,128,0);		return TRUE; }
				else if ( color.find( L"greenYellow"			) >= 0) { m_nColor = RGB2(173,255,47);	return TRUE; }
				else if ( color.find( L"grey"				) >= 0) { m_nColor = RGB2(128,128,128);	return TRUE; }
				break;	   
			case L'h':	   
				if      ( color.find( L"honeydew"			) >= 0) { m_nColor = RGB2(240,255,240);	return TRUE; }
				else if ( color.find( L"hotPink"				) >= 0) { m_nColor = RGB2(255,105,180);	return TRUE; }
				break;
			case L'i':
				if      ( color.find( L"indianRed"			) >= 0) { m_nColor = RGB2(205,92,92);	return TRUE; }
				else if ( color.find( L"indigo"				) >= 0) { m_nColor = RGB2(75,0,130);	return TRUE; }
				else if ( color.find( L"ivory"				) >= 0) { m_nColor = RGB2(255,255,240);	return TRUE; }
				break;
			case L'k':
				if      ( color.find( L"khaki"				) >= 0) { m_nColor = RGB2(240,230,140);	return TRUE; }
				break;
			case L'l':
				if      ( color.find( L"lavender"			) >= 0) { m_nColor = RGB2(230,230,250);	return TRUE; }
				else if ( color.find( L"lavenderBlush"		) >= 0) { m_nColor = RGB2(255,240,245);	return TRUE; }
				else if ( color.find( L"lawnGreen"			) >= 0) { m_nColor = RGB2(124,252,0);	return TRUE; }
				else if ( color.find( L"lemonChiffon"		) >= 0) { m_nColor = RGB2(255,250,205);	return TRUE; }
				else if ( color.find( L"lightBlue"			) >= 0) { m_nColor = RGB2(173,216,230);	return TRUE; }
				else if ( color.find( L"lightCoral"			) >= 0) { m_nColor = RGB2(240,128,128);	return TRUE; }
				else if ( color.find( L"lightCyan"			) >= 0) { m_nColor = RGB2(224,255,255);	return TRUE; }
				else if ( color.find( L"lightGoldenrodYellow") >= 0) { m_nColor = RGB2(250,250,210);	return TRUE; }
				else if ( color.find( L"lightGray"			) >= 0) { m_nColor = RGB2(211,211,211);	return TRUE; }
				else if ( color.find( L"lightGreen"			) >= 0) { m_nColor = RGB2(144,238,144);	return TRUE; }
				else if ( color.find( L"lightGrey"			) >= 0) { m_nColor = RGB2(211,211,211);	return TRUE; }
				else if ( color.find( L"lightPink"			) >= 0) { m_nColor = RGB2(255,182,193);	return TRUE; }
				else if ( color.find( L"lightSalmon"			) >= 0) { m_nColor = RGB2(255,160,122);	return TRUE; }
				else if ( color.find( L"lightSeaGreen"		) >= 0) { m_nColor = RGB2(32,178,170);	return TRUE; }
				else if ( color.find( L"lightSkyBlue"		) >= 0) { m_nColor = RGB2(135,206,250);	return TRUE; }
				else if ( color.find( L"lightSlateGray"		) >= 0) { m_nColor = RGB2(119,136,153);	return TRUE; }
				else if ( color.find( L"lightSlateGrey"		) >= 0) { m_nColor = RGB2(119,136,153);	return TRUE; }
				else if ( color.find( L"lightSteelBlue"		) >= 0) { m_nColor = RGB2(176,196,222);	return TRUE; }
				else if ( color.find( L"lightYellow"			) >= 0) { m_nColor = RGB2(255,255,224);	return TRUE; }
				else if ( color.find( L"lime"				) >= 0) { m_nColor = RGB2(0,255,0);		return TRUE; }
				else if ( color.find( L"limeGreen"			) >= 0) { m_nColor = RGB2(50,205,50);	return TRUE; }
				else if ( color.find( L"linen"				) >= 0) { m_nColor = RGB2(250,240,230);	return TRUE; }
				else if ( color.find( L"ltBlue"				) >= 0) { m_nColor = RGB2(173,216,230);	return TRUE; }
				else if ( color.find( L"ltCoral"				) >= 0) { m_nColor = RGB2(240,128,128);	return TRUE; }
				else if ( color.find( L"ltCyan"				) >= 0) { m_nColor = RGB2(224,255,255);	return TRUE; }
				else if ( color.find( L"ltGoldenrodYellow"	) >= 0) { m_nColor = RGB2(250,250,120);	return TRUE; }
				else if ( color.find( L"ltGray"				) >= 0) { m_nColor = RGB2(211,211,211);	return TRUE; }
				else if ( color.find( L"ltGreen"				) >= 0) { m_nColor = RGB2(144,238,144);	return TRUE; }
				else if ( color.find( L"ltGrey"				) >= 0) { m_nColor = RGB2(211,211,211);	return TRUE; }
				else if ( color.find( L"ltPink"				) >= 0) { m_nColor = RGB2(255,182,193);	return TRUE; }
				else if ( color.find( L"ltSalmon"			) >= 0) { m_nColor = RGB2(255,160,122);	return TRUE; }
				else if ( color.find( L"ltSeaGreen"			) >= 0) { m_nColor = RGB2(32,178,170);	return TRUE; }
				else if ( color.find( L"ltSkyBlue"			) >= 0) { m_nColor = RGB2(135,206,250);	return TRUE; }
				else if ( color.find( L"ltSlateGray"			) >= 0) { m_nColor = RGB2(119,136,153);	return TRUE; }
				else if ( color.find( L"ltSlateGrey"			) >= 0) { m_nColor = RGB2(119,136,153);	return TRUE; }
				else if ( color.find( L"ltSteelBlue"			) >= 0) { m_nColor = RGB2(176,196,222);	return TRUE; }
				else if ( color.find( L"ltYellow"			) >= 0) { m_nColor = RGB2(255,255,224);	return TRUE; }
				break;
			case L'm':
				if      ( color.find( L"magenta"				) >= 0) { m_nColor = RGB2(255,0,255);	return TRUE; }
				else if ( color.find( L"maroon"				) >= 0) { m_nColor = RGB2(128,0,0);		return TRUE; }
				else if ( color.find( L"medAquamarine"		) >= 0) { m_nColor = RGB2(102,205,170);	return TRUE; }
				else if ( color.find( L"medBlue"				) >= 0) { m_nColor = RGB2(0,0,205);		return TRUE; }
				else if ( color.find( L"mediumAquamarine"	) >= 0) { m_nColor = RGB2(102,205,170);	return TRUE; }
				else if ( color.find( L"mediumBlue"			) >= 0) { m_nColor = RGB2(0,0,205);		return TRUE; }
				else if ( color.find( L"mediumOrchid"		) >= 0) { m_nColor = RGB2(186,85,211);	return TRUE; }
				else if ( color.find( L"mediumPurple"		) >= 0) { m_nColor = RGB2(147,112,219);	return TRUE; }
				else if ( color.find( L"mediumSeaGreen"		) >= 0) { m_nColor = RGB2(60,179,113);	return TRUE; }
				else if ( color.find( L"mediumSlateBlue"		) >= 0) { m_nColor = RGB2(123,104,238);	return TRUE; }
				else if ( color.find( L"mediumSpringGreen"	) >= 0) { m_nColor = RGB2(0,250,154);	return TRUE; }
				else if ( color.find( L"mediumTurquoise"		) >= 0) { m_nColor = RGB2(72,209,204);	return TRUE; }
				else if ( color.find( L"mediumVioletRed"		) >= 0) { m_nColor = RGB2(199,21,133);	return TRUE; }
				else if ( color.find( L"medOrchid"			) >= 0) { m_nColor = RGB2(186,85,211);	return TRUE; }
				else if ( color.find( L"medPurple"			) >= 0) { m_nColor = RGB2(147,112,219);	return TRUE; }
				else if ( color.find( L"medSeaGreen"			) >= 0) { m_nColor = RGB2(60,179,113);	return TRUE; }
				else if ( color.find( L"medSlateBlue"		) >= 0) { m_nColor = RGB2(123,104,238);	return TRUE; }
				else if ( color.find( L"medSpringGreen"		) >= 0) { m_nColor = RGB2(0,250,154);	return TRUE; }
				else if ( color.find( L"medTurquoise"		) >= 0) { m_nColor = RGB2(72,209,204);	return TRUE; }
				else if ( color.find( L"medVioletRed"		) >= 0) { m_nColor = RGB2(199,21,133);	return TRUE; }
				else if ( color.find( L"midnightBlue"		) >= 0) { m_nColor = RGB2(25,25,112);	return TRUE; }
				else if ( color.find( L"mintCream"			) >= 0) { m_nColor = RGB2(245,255,250);	return TRUE; }
				else if ( color.find( L"mistyRose"			) >= 0) { m_nColor = RGB2(255,228,225);	return TRUE; }
				else if ( color.find( L"moccasin"			) >= 0) { m_nColor = RGB2(255,228,181);	return TRUE; }
				break;	  
			case L'n':
				if      ( color.find( L"navajoWhite"			) >= 0) { m_nColor = RGB2(255,222,173);	return TRUE; }
				else if ( color.find( L"navy"				) >= 0) { m_nColor = RGB2(0,0,128);		return TRUE; }
				break;
			case L'o':
				if      ( color.find( L"oldLace"				) >= 0) { m_nColor = RGB2(253,245,230);	return TRUE; }
				else if ( color.find( L"olive"				) >= 0) { m_nColor = RGB2(128,128,0);	return TRUE; }
				else if ( color.find( L"oliveDrab"			) >= 0) { m_nColor = RGB2(107,142,35);	return TRUE; }
				else if ( color.find( L"orange"				) >= 0) { m_nColor = RGB2(255,165,0);	return TRUE; }
				else if ( color.find( L"orangeRed"			) >= 0) { m_nColor = RGB2(255,69,0);	return TRUE; }
				else if ( color.find( L"orchid"				) >= 0) { m_nColor = RGB2(218,112,214);	return TRUE; }
				break;	 
			case L'p':	  
				if      ( color.find( L"paleGoldenrod"		) >= 0) { m_nColor = RGB2(238,232,170);	return TRUE; }
				else if ( color.find( L"paleGreen"			) >= 0) { m_nColor = RGB2(152,251,152);	return TRUE; }
				else if ( color.find( L"paleTurquoise"		) >= 0) { m_nColor = RGB2(175,238,238);	return TRUE; }
				else if ( color.find( L"paleVioletRed"		) >= 0) { m_nColor = RGB2(219,112,147);	return TRUE; }
				else if ( color.find( L"papayaWhip"			) >= 0) { m_nColor = RGB2(255,239,213);	return TRUE; }
				else if ( color.find( L"peachPuff"			) >= 0) { m_nColor = RGB2(255,218,185);	return TRUE; }
				else if ( color.find( L"peru"				) >= 0) { m_nColor = RGB2(205,133,63);	return TRUE; }
				else if ( color.find( L"pink"				) >= 0) { m_nColor = RGB2(255,192,203);	return TRUE; }
				else if ( color.find( L"plum"				) >= 0) { m_nColor = RGB2(221,160,221);	return TRUE; }
				else if ( color.find( L"powderBlue"			) >= 0) { m_nColor = RGB2(176,224,230);	return TRUE; }
				else if ( color.find( L"purple"				) >= 0) { m_nColor = RGB2(128,0,128);	return TRUE; }
				break;	   
			case L'r':
				if      ( color.find( L"red"					) >= 0) { m_nColor = RGB2(255,0,0);		return TRUE; }
				else if ( color.find( L"rosyBrown"			) >= 0) { m_nColor = RGB2(188,143,143);	return TRUE; }
				else if ( color.find( L"royalBlue"			) >= 0) { m_nColor = RGB2(65,105,225);	return TRUE; }
				break;	   
			case L's':	  
				if      ( color.find( L"saddleBrown"			) >= 0) { m_nColor = RGB2(139,69,19);	return TRUE; }
				else if ( color.find( L"salmon"				) >= 0) { m_nColor = RGB2(250,128,114);	return TRUE; }
				else if ( color.find( L"sandyBrown"			) >= 0) { m_nColor = RGB2(244,164,96);	return TRUE; }
				else if ( color.find( L"seaGreen"			) >= 0) { m_nColor = RGB2(46,139,87);	return TRUE; }
				else if ( color.find( L"seaShell"			) >= 0) { m_nColor = RGB2(255,245,238);	return TRUE; }
				else if ( color.find( L"sienna"				) >= 0) { m_nColor = RGB2(160,82,45);	return TRUE; }
				else if ( color.find( L"silver"				) >= 0) { m_nColor = RGB2(192,192,192);	return TRUE; }
				else if ( color.find( L"skyBlue"				) >= 0) { m_nColor = RGB2(135,206,235);	return TRUE; }
				else if ( color.find( L"slateBlue"			) >= 0) { m_nColor = RGB2(106,90,205);	return TRUE; }
				else if ( color.find( L"slateGray"			) >= 0) { m_nColor = RGB2(112,128,144);	return TRUE; }
				else if ( color.find( L"slateGrey"			) >= 0) { m_nColor = RGB2(112,128,144);	return TRUE; }
				else if ( color.find( L"snow"				) >= 0) { m_nColor = RGB2(255,250,250);	return TRUE; }
				else if ( color.find( L"springGreen"			) >= 0) { m_nColor = RGB2(0,255,127);	return TRUE; }
				else if ( color.find( L"steelBlue"			) >= 0) { m_nColor = RGB2(70,130,180);	return TRUE; }
				break;	  
			case L't':
				if      ( color.find( L"tan"					) >= 0) { m_nColor = RGB2(210,180,140);	return TRUE; }
				else if ( color.find( L"teal"				) >= 0) { m_nColor = RGB2(0,128,128);	return TRUE; }
				else if ( color.find( L"thistle"				) >= 0) { m_nColor = RGB2(216,191,216);	return TRUE; }
				else if ( color.find( L"tomato"				) >= 0) { m_nColor = RGB2(255,99,71);	return TRUE; }
				else if ( color.find( L"turquoise"			) >= 0) { m_nColor = RGB2(64,224,208);	return TRUE; }
				break;
			case L'v':
				if      ( color.find( L"violet"				) >= 0) { m_nColor = RGB2(238,130,238);	return TRUE; }
				break;
			case L'w':
				if      ( color.find( L"wheat"				) >= 0)	{ m_nColor = RGB2(245,222,179);	return TRUE; }
				else if ( color.find( L"white"				) >= 0)	{ m_nColor = RGB2(255,255,255);	return TRUE; }
				else if ( color.find( L"whiteSmoke"			) >= 0)	{ m_nColor = RGB2(245,245,245);	return TRUE; }
				break;	  
			case L'y':	  
				if      ( color.find( L"yellow"				) >= 0)	{ m_nColor = RGB2(255,255,0);	return TRUE; }
				else if ( color.find( L"yellowGreen"			) >= 0)	{ m_nColor = RGB2(154,205,50);	return TRUE; }
				break;
			}

			if (DOCXDOCUTILS::GetFillColor (Color, m_nColor))
				return TRUE;

			return FALSE;
		}

		inline int Color() 
		{
			return m_nColor;
		}

	private:

		inline unsigned int RGB2 (unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xF)	// TODO
		{
			return ( (b<<16) | (g<<8) | (r) );
		}

	private:

		unsigned int m_nColor;
	};
}

#ifdef _DEBUG		

/*namespace DOCXDOCUTILS
{
	inline void DebugStrPrint (std::wstring strMessage, const std::string& strSource)
	{
		OutputDebugStringW(strMessage.c_str());
		OutputDebugStringA(strSource.c_str());
		OutputDebugStringW(L"\n");
	}

	inline void DebugStrPrint (std::wstring strMessage, const std::wstring& strSource)
	{
		OutputDebugStringW(strMessage.c_str());
		OutputDebugStringW(strSource.c_str());
		OutputDebugStringW(L"\n");
	}
}*/

#endif
