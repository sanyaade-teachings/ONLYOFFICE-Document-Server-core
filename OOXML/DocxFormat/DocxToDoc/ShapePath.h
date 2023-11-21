#pragma once

//#include <XmlUtils.h>
#include <math.h>

#include "OfficeArt/Common.h"
#include "OfficeArt/MSOArray.h"
#include "OfficeArt/Enumerations.h"

#include "../../../DesktopEditor/common/Types.h"

#define M_PI				3.14159265358979323846

const double ShapeSize		=	43200.0;
const LONG ShapeSizeVML		=	21600;
const double RadKoef		=	M_PI/10800000.0;

#define	pow2_16	65536

namespace Docx2Doc
{
	enum FormulaType
	{
		// VML
		ftSum			= 0,	// a + b - c  
		ftProduct		= 1,	// a * b / c  
		ftMid			= 2,	// (a + b) / 2  
		ftAbsolute		= 3,	// abs(a)  
		ftMin			= 4,	// min(a,b)  
		ftMax			= 5,	// max(a,b)  
		ftIf			= 6,	// if  a > 0 ? b : c  
		ftMod			= 7,	// sqrt(a)  
		ftAtan2			= 8,	// atan2(b,a)  
		ftSin			= 9,	// a * sin(b)  
		ftCos			= 10,	// a * cos(b)  
		ftCosatan2		= 11,	// a * cos(atan2(c,b))
		ftSinatan2		= 12,	// a * sin(atan2(c,b))  
		ftSqrt			= 13,	// sqrt(a*a + b*b + c*c)
		ftSumangle		= 14,	// a + b° - c°
		ftEllipse		= 15,	// c * sqrt(1-(a/b)2)  
		ftTan			= 16,	// a * tan(b)  
		ftVal			= 17	// a
	};	

	enum ParamType
	{
		ptFormula			= 0,
		ptAdjust			= 1,
		ptValue				= 2
	};

	static bool IsDigit(const WCHAR& c)
	{
		return (((c >= '0') && (c <= '9')) || (c == '-'));
	}
	static bool IsAlpha(const WCHAR& c)
	{
		return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
	}
	static bool IsNumber(std::wstring str)
	{
		for (int nIndex = 0; nIndex < str.GetLength(); ++nIndex)
		{
			if (!IsDigit(str[nIndex]))
			{
				return false;
			}
		}
		return true;
	}

	static std::wstring ToString(LONG val)
	{
		std::wstring str = L"";
		str.format(L"%d""", val);
		return str;
	}

	static void ParseString(std::wstring strDelimeters, std::wstring strSource, CAtlArray<std::wstring>* pArrayResults, bool bIsCleared = true)
	{
		if (NULL == pArrayResults)
			return;

		if (bIsCleared)
			pArrayResults->RemoveAll();

		std::wstring resToken;
		int curPos= 0;

		resToken = strSource.Tokenize(strDelimeters, curPos);
		while (resToken != _T(""))
		{
			pArrayResults->Add(resToken);
			resToken = strSource.Tokenize(strDelimeters, curPos);
		};
	}
	static void ParseString(std::wstring strDelimeters, std::wstring strSource, CSimpleArray<std::wstring>* pArrayResults, bool bIsCleared = true)
	{
		if (NULL == pArrayResults)
			return;

		if (bIsCleared)
			pArrayResults->RemoveAll();

		std::wstring resToken;
		int curPos= 0;

		resToken = strSource.Tokenize(strDelimeters, curPos);
		while (resToken != _T(""))
		{
			pArrayResults->Add(resToken);
			resToken = strSource.Tokenize(strDelimeters, curPos);
		};

	}
	static void ParseString(CSimpleArray<char>* pArrayDelimeters, std::wstring strSource, CSimpleArray<std::wstring>* pArrayResults, bool bIsCleared = true)
	{
		if (NULL == pArrayDelimeters)
			return;

		std::wstring strDelimeters = _T("");
		for (int nIndex = 0; nIndex < pArrayDelimeters->GetSize(); ++nIndex)
			strDelimeters += (*pArrayDelimeters)[nIndex];

		return ParseString(strDelimeters, strSource, pArrayResults, bIsCleared);
	}

	inline static void ParsePath(std::wstring strSource, CSimpleArray<std::wstring>* pArrayResults, bool bIsCleared = true)
	{
		if (NULL == pArrayResults)
			return;

		std::wstring strPath = strSource;
		//strPath.Replace(_T(" "), _T(","));
		for (int nIndex = 0; nIndex < strPath.GetLength(); ++nIndex)
		{
			if (nIndex == (strPath.GetLength() - 1))
				continue;

			if (IsAlpha(strPath[nIndex]) && (',' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
				strPath.Insert(nIndex + 1, '0');
				++nIndex;
			}
			else if ((',' == strPath[nIndex]) && (',' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, '0');
				++nIndex;
			}
			else if ((',' == strPath[nIndex]) && IsAlpha(strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, '0');
				++nIndex;
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsAlpha(strPath[nIndex]) && IsDigit(strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsDigit(strPath[nIndex]) && IsAlpha(strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsDigit(strPath[nIndex]) && ('@' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsDigit(strPath[nIndex]) && ('#' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsAlpha(strPath[nIndex]) && ('@' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsAlpha(strPath[nIndex]) && ('#' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsDigit(strPath[nIndex]) && ('$' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsDigit(strPath[nIndex]) && ('?' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsAlpha(strPath[nIndex]) && ('$' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if (IsAlpha(strPath[nIndex]) && ('?' == strPath[nIndex + 1]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
			else if ((IsAlpha(strPath[nIndex]) && IsAlpha(strPath[nIndex + 1])) && ('x' == strPath[nIndex]))
			{
				strPath.Insert(nIndex + 1, ',');
				++nIndex;
			}
		}

		ParseString(_T(","), strPath, pArrayResults, bIsCleared);
		return;
	}

	static LONG GetValue(std::wstring strParam, ParamType& ptType, bool& bRes,
		long lShapeWidth = ShapeSizeVML, long lShapeHeight = ShapeSizeVML)
	{
		ptType = ptValue;
		bRes = true;
		if ('#' == strParam[0])
		{
			ptType = ptAdjust;
			return (LONG)XmlUtils::GetInteger(strParam.Mid(1));
		}
		else if ('@' == strParam[0])
		{
			ptType = ptFormula;
			return (LONG)XmlUtils::GetInteger(strParam.Mid(1));
		}
		else if (!IsNumber(strParam))
		{
			if (_T("width") == strParam)
			{
				return lShapeWidth;
			}
			else if (_T("height") == strParam)
			{
				return lShapeHeight;
			}
			else if (_T("pixelWidth") == strParam)
			{
				return lShapeWidth;
			}
			else if (_T("pixelHeight") == strParam)
			{
				return lShapeHeight;
			}
			else if (_T("pixelLineWidth") == strParam || _T("lineDrawn") == strParam)
			{
				return 1;
			}
			else
			{
				bRes = false;
				return 0;
			}
		}	
		else
		{
			ptType = ptValue;
			return (LONG)XmlUtils::GetInteger(strParam);
		}
	}

	static FormulaType GetFormula(std::wstring strName, bool& bRes)
	{
		bRes = true;
		if		(_T("sum") == strName)									return ftSum;
		else if ((_T("prod") == strName) || (_T("product") == strName)) return ftProduct;
		else if (_T("mid") == strName)									return ftMid;
		else if ((_T("absolute") == strName) || (_T("abs") == strName)) return ftAbsolute;
		else if (_T("min") == strName)									return ftMin;
		else if (_T("max") == strName)									return ftMax;
		else if (_T("if") == strName)									return ftIf;
		else if (_T("sqrt") == strName)									return ftSqrt;
		else if (_T("mod") == strName)									return ftMod;
		else if (_T("sin") == strName)									return ftSin;
		else if (_T("cos") == strName)									return ftCos;
		else if (_T("tan") == strName)									return ftTan;
		else if (_T("atan2") == strName)								return ftAtan2;
		else if (_T("sinatan2") == strName)								return ftSinatan2;
		else if (_T("cosatan2") == strName)								return ftCosatan2;
		else if (_T("sumangle") == strName)								return ftSumangle;
		else if (_T("ellipse") == strName)								return ftEllipse;
		else if (_T("val") == strName)									return ftVal;
		else bRes = false;

		return ftVal;
	}
}

namespace AVSDocFileFormat
{
	class CFormulasManager;
	class CFormula
	{
	public:
		FormulaType m_eFormulaType;
		int m_lIndex;

		LONG m_lParam1;
		ParamType m_eType1;

		LONG m_lParam2;
		ParamType m_eType2;

		LONG m_lParam3;
		ParamType m_eType3;

	private:
		long m_lCountRecurs;

	public:
		CFormula()
		{
			m_eFormulaType = ftSum;
			m_lIndex = 0;
			m_lParam1 = 0;	m_eType1 = ptValue;
			m_lParam2 = 0;	m_eType2 = ptValue;
			m_lParam3 = 0;	m_eType3 = ptValue;

			m_lCountRecurs = 0;
		}

		CFormula(int nIndex)
		{
			m_eFormulaType = ftSum;
			m_lIndex = nIndex;
			m_lParam1 = 0;	m_eType1 = ptValue;
			m_lParam2 = 0;	m_eType2 = ptValue;
			m_lParam3 = 0;	m_eType3 = ptValue;

			m_lCountRecurs = 0;
		}

		CFormula& operator =(const CFormula& oSrc)
		{
			m_eFormulaType	= oSrc.m_eFormulaType;
			m_lIndex		= oSrc.m_lIndex;

			m_lParam1		= oSrc.m_lParam1;
			m_eType1		= oSrc.m_eType1;

			m_lParam2		= oSrc.m_lParam2;
			m_eType2		= oSrc.m_eType2;

			m_lParam3		= oSrc.m_lParam3;
			m_eType3		= oSrc.m_eType3;

			m_lCountRecurs = 0;
			return (*this);
		}

		void FromString(std::wstring strFormula, long lShapeWidth = ShapeSizeVML, long lShapeHeight = ShapeSizeVML)
		{
			CSimpleArray<std::wstring> oArrayParams;
			ParseString(_T(" "), strFormula, &oArrayParams);
			int nCount = oArrayParams.GetSize();
			if (0 >= nCount)
				return;

			bool bRes = true;
			m_eFormulaType = GetFormula(oArrayParams[0], bRes);

			ParamType ptType = ptValue;
			if (1 < nCount)
			{
				m_lParam1 = GetValue(oArrayParams[1], ptType, bRes, lShapeWidth, lShapeHeight);
				m_eType1 = ptType;		
			}
			if (2 < nCount)
			{
				m_lParam2 = GetValue(oArrayParams[2], ptType, bRes, lShapeWidth, lShapeHeight);
				m_eType2 = ptType;		
			}
			if (3 < nCount)
			{
				m_lParam3 = GetValue(oArrayParams[3], ptType, bRes, lShapeWidth, lShapeHeight);
				m_eType3 = ptType;		
			}
		}
		LONG Calculate(CFormulasManager* pManager);
	};

	class CFormulasManager
	{
	public:
		CSimpleArray<LONG>* m_pAdjustments;
		CSimpleArray<LONG> m_arResults;

		CSimpleArray<CFormula> m_arFormulas;

		long m_lShapeWidth;
		long m_lShapeHeight;

	public:
		CFormulasManager() : m_arFormulas(), m_arResults()
		{
			m_pAdjustments	= NULL;
			m_lShapeWidth	= ShapeSizeVML;
			m_lShapeHeight	= ShapeSizeVML;
		}
		CFormulasManager& operator =(const CFormulasManager& oSrc)
		{
			m_pAdjustments	= oSrc.m_pAdjustments;
			m_lShapeWidth	= oSrc.m_lShapeWidth;
			m_lShapeHeight	= oSrc.m_lShapeHeight;

			m_arResults.RemoveAll();
			for (int nIndex = 0; nIndex < oSrc.m_arResults.GetSize(); ++nIndex)
			{
				m_arResults.Add(oSrc.m_arResults[nIndex]);
			}
			m_arFormulas.RemoveAll();
			for (int nIndex = 0; nIndex < oSrc.m_arFormulas.GetSize(); ++nIndex)
			{
				m_arFormulas.Add(oSrc.m_arFormulas[nIndex]);
			}

			return (*this);
		}

		void RemoveAll()
		{
			m_pAdjustments	= NULL;
			m_lShapeWidth	= ShapeSizeVML;
			m_lShapeHeight	= ShapeSizeVML;

			m_arFormulas.RemoveAll();
			m_arResults.RemoveAll();
		}

		void Clear(CSimpleArray<LONG>* pAdjusts)
		{
			m_pAdjustments = pAdjusts;

			//m_arFormulas.RemoveAll();
			//m_arResults.RemoveAll();
			for (int nIndex = 0; nIndex < m_arResults.GetSize(); ++nIndex)
			{
				m_arResults[nIndex] = 0xFFFFFFFF;
			}
		}
		void AddFormula(std::wstring strFormula)
		{
			CFormula oFormula(m_arFormulas.GetSize());
			oFormula.FromString(strFormula, m_lShapeWidth, m_lShapeHeight);
			m_arFormulas.Add(oFormula);
			m_arResults.Add(0xFFFFFFFF);
		}
		void AddFormula(CFormula oFormula)
		{
			oFormula.m_lIndex = m_arFormulas.GetSize();
			m_arFormulas.Add(oFormula);
			m_arResults.Add(0xFFFFFFFF);
		}
		void CalculateResults()
		{
			for (int index = 0; index < m_arFormulas.GetSize(); ++index)
			{
				LONG lResult = m_arFormulas[index].Calculate(this);
			}

			//m_pAdjustments = NULL;
			//m_arFormulas.RemoveAll();
		}
	};
}

namespace AVSDocFileFormat
{
	// TODO : add escape segments

	class CPathSegment
	{
	public:
		enum MSOPATHTYPE
		{
			msopathLineTo,
			msopathCurveTo,
			msopathMoveTo,
			msopathClose,
			msopathEnd,
			msopathEscape,
			msopathClientEscape,
			msopathInvalid
		};

		enum MSOPATHESCAPE
		{
			msopathEscapeExtension 				=	0x00000000,	
			msopathEscapeAngleEllipseTo  		=	0x00000001,
			msopathEscapeAngleEllipse 	 		=	0x00000002,
			msopathEscapeArcTo  				=	0x00000003,
			msopathEscapeArc  					=	0x00000004,
			msopathEscapeClockwiseArcTo  		=	0x00000005,
			msopathEscapeClockwiseArc 	 		=	0x00000006,
			msopathEscapeEllipticalQuadrantX  	=	0x00000007,
			msopathEscapeEllipticalQuadrantY 	=	0x00000008,
			msopathEscapeQuadraticBezier 	 	=	0x00000009,
			msopathEscapeNoFill  				=	0x0000000A,
			msopathEscapeNoLine  				=	0x0000000B,
			msopathEscapeAutoLine  				=	0x0000000C,
			msopathEscapeAutoCurve  			=	0x0000000D,
			msopathEscapeCornerLine  			=	0x0000000E,
			msopathEscapeCornerCurve 			=	0x0000000F,
			msopathEscapeSmoothLine  			=	0x00000010,
			msopathEscapeSmoothCurve  			=	0x00000011,
			msopathEscapeSymmetricLine 			=	0x00000012,
			msopathEscapeSymmetricCurve 		=	0x00000013,
			msopathEscapeFreeform 				=	0x00000014,
			msopathEscapeFillColor 				=	0x00000015,
			msopathEscapeLineColor 				=	0x00000016
		};

	public:

		CPathSegment () : m_oBits(2)
		{

		}

		CPathSegment (std::wstring Command, int Segments) : m_oBits(2)
		{
			m_oBits.SetBits<int>(Segments, 0, 13);

			if (std::wstring("m") == Command)
				m_oBits.SetBits<unsigned short>(msopathMoveTo,  13, 3);

			if (std::wstring("l") == Command)
				m_oBits.SetBits<unsigned short>(msopathLineTo,  13, 3);

			if (std::wstring("c") == Command)
				m_oBits.SetBits<unsigned short>(msopathCurveTo,	13, 3);

			if (std::wstring("e") == Command)
				m_oBits.SetBits<unsigned short>(msopathEnd,		13, 3);

			if (std::wstring("x") == Command)
				m_oBits.SetBits<unsigned short>(msopathClose,	13, 3);
		}

		CPathSegment (std::wstring Command, int Escape, int Segments) : m_oBits(2)
		{
			m_oBits.SetBits<int>(Segments, 0, 13);
			
			if (std::wstring("nf") == Command)
				m_oBits.SetBits<MSOPATHESCAPE>(msopathEscapeNoFill, 13, 3);

			if (std::wstring("ns") == Command)
				m_oBits.SetBits<MSOPATHESCAPE>(msopathEscapeNoLine, 13, 3);

			//m_oBits.SetBits<int>(Escape, 3, 5);		
			//m_oBits.SetBits<int>(Segments, 8, 8);			
		}

		inline unsigned short Get()
		{
			return FormatUtils::BytesToUInt16 (m_oBits.GetBytes(), 0, sizeof(unsigned short));
		}

	private:

		AVSDocFormatUtils::BitSet m_oBits;
	};

	class CShapePath
	{
	public:

		CShapePath () : m_bIsSimple (TRUE)
		{
			m_nType	=	-1;
		}

		inline BOOL IsValid ()
		{
			return (m_nType >= 0) && (m_oPoints.GetSize() > 0) && (m_oSegments.GetSize() > 0);
		}

		inline BOOL IsSimple ()
		{
			return m_bIsSimple;
		}

		inline BOOL Build (const std::string& strPath, const std::string& strAdj, const std::string& strFormulas)
		{
			m_oManager.RemoveAll();

			m_oPoints.Clear ();
			m_oSegments.Clear ();

			if (0==strPath.length())
				return FALSE;

			CSimpleArray<std::wstring> oArray;
			ParsePath(std::wstring(strPath.c_str()), &oArray);

			if (oArray.GetSize())
			{
				m_nType	=	1;

				ParamType eParamType = ptValue;
				LONG lValue;
				bool bRes = true;
				std::wstring strCommand;
				OfficeArt::CPoint32 point;
				OfficeArt::CPoint32 movePt;

				LoadAdjustValuesList (std::wstring(strAdj.c_str()));
				m_oManager.m_pAdjustments	=	&m_arAdjustments;

				LoadGuidesList (std::wstring(strFormulas.c_str()));
				if (m_arAdjustments.GetSize())
					m_oManager.CalculateResults();

				std::wstring oldCommand = L"";

				for (int nIndex = 0; nIndex < oArray.GetSize(); ++nIndex)
				{
					lValue	=	GetFormatedValue (nIndex, oArray);

					if (IsCommand(oArray[nIndex]))
					{
						//ATLTRACE (L"COMMAND : %s\n",oArray[nIndex]);

						strCommand = oArray[nIndex];

						if (std::wstring("x") == strCommand)
						{
							m_oSegments.Add(CPathSegment(strCommand,1).Get());
						}
						else if (std::wstring("e") == strCommand)
						{
							m_oSegments.Add(CPathSegment(strCommand,0).Get());
						}
						else if (std::wstring("n") == oldCommand)
						{
							if (std::wstring("s") == strCommand)
							{
								//m_oSegments.Add(CPathSegment(L"ns", 1, 0).Get());
							}
							else if (std::wstring("f") == strCommand)
							{
								//m_oSegments.Add(CPathSegment(L"nf", 1, 0).Get());
							}
						}

						oldCommand	=	strCommand;
					}
					else
					{
						if (std::wstring("m") == strCommand || std::wstring("l") == strCommand || std::wstring("r") == strCommand || std::wstring("c") == strCommand || std::wstring("v") == strCommand)
						{
							LONG nValue0	=	GetFormatedValue (nIndex, oArray);
							LONG nValue1	=	GetFormatedValue (nIndex + 1, oArray);

							OfficeArt::CPoint32 curPoint = OfficeArt::CPoint32(nValue0,nValue1);

							if (std::wstring("m") == strCommand)
							{
								movePt		=	curPoint;

								m_oSegments.Add(CPathSegment(std::wstring("m"),0).Get());
								m_oPoints.Add(curPoint);

								++nIndex;
							}
							else if(std::wstring("r") == strCommand)
							{
								curPoint.X	+=	point.X;
								curPoint.Y	+=	point.Y;

								m_oPoints.Add(curPoint);
								m_oSegments.Add(CPathSegment(std::wstring("l"),1).Get());

								++nIndex;
							}
							else if(std::wstring("c") == strCommand)
							{
								m_bHaveCurves	=	TRUE;

								LONG nValue2	=	GetFormatedValue (nIndex + 2, oArray);
								LONG nValue3	=	GetFormatedValue (nIndex + 3, oArray);
								LONG nValue4	=	GetFormatedValue (nIndex + 4, oArray);
								LONG nValue5	=	GetFormatedValue (nIndex + 5, oArray);

								OfficeArt::CPoint32 curPoint2 = OfficeArt::CPoint32(nValue2, nValue3);
								OfficeArt::CPoint32 curPoint3 = OfficeArt::CPoint32(nValue4, nValue5);

								m_oPoints.Add(curPoint);
								m_oPoints.Add(curPoint2);
								m_oPoints.Add(curPoint3);

								m_oSegments.Add(CPathSegment(std::wstring("c"),1).Get());

								nIndex += 5;

								point = curPoint3;
								continue;
							}
							else if(std::wstring("v") == strCommand)
							{
								m_bHaveCurves	=	TRUE;

								LONG nValue2	=	GetFormatedValue (nIndex + 2, oArray);
								LONG nValue3	=	GetFormatedValue (nIndex + 3, oArray);
								LONG nValue4	=	GetFormatedValue (nIndex + 4, oArray);
								LONG nValue5	=	GetFormatedValue (nIndex + 5, oArray);

								OfficeArt::CPoint32 curPoint2 = OfficeArt::CPoint32(nValue2, nValue3);
								OfficeArt::CPoint32 curPoint3 = OfficeArt::CPoint32(nValue4,nValue5);

								curPoint.X	+=	point.X;
								curPoint.Y	+=	point.Y;

								curPoint2.X	+=	point.X;
								curPoint2.Y	+=	point.Y;

								curPoint3.X	+=	point.X;
								curPoint3.Y	+=	point.Y;

								m_oPoints.Add(curPoint);
								m_oPoints.Add(curPoint2);
								m_oPoints.Add(curPoint3);

								m_oSegments.Add(CPathSegment(std::wstring("c"),1).Get());

								nIndex += 5;

								point = curPoint3;
								continue;
							}
							else
							{
								m_oPoints.Add(curPoint);
								m_oSegments.Add(CPathSegment(strCommand,1).Get());

								++nIndex;
							}

							point	=	curPoint;
						}
						else
						{
							m_bIsSimple	=	FALSE;
						}
					}
				}

				return TRUE;
			}

			return FALSE;
		}

		inline int GetType () const
		{
			if (m_bHaveCurves)
				return 3;

			return m_nType;
		}

		inline OfficeArt::CMSOArray<OfficeArt::CPoint32>& GetPoints()
		{
			return m_oPoints;
		}

		inline OfficeArt::CMSOArray<unsigned short>& GetSegments()
		{
			return m_oSegments;
		}

		// FORMULA
		inline bool LoadAdjustValuesList(const std::wstring& xml)
		{
			m_arAdjustments.RemoveAll ();

			CSimpleArray<std::wstring> arAdj;
			ParseString(_T(","), xml, &arAdj);

			m_arAdjustments.RemoveAll();
			for (int nIndex = 0; nIndex < arAdj.GetSize(); ++nIndex)
				m_arAdjustments.Add((LONG)XmlUtils::GetInteger(arAdj[nIndex]));

			return true;
		}

		inline bool LoadGuidesList(const std::wstring& strXml)
		{
			XmlUtils::CXmlNode oNodeGuides;
			if (oNodeGuides.FromXmlString(strXml))
			{
				XmlUtils::CXmlNodes oList;
				if (oNodeGuides.GetNodes(_T("f"), oList))
				{
					int lCount = oList.GetCount();
					for (int nIndex = 0; nIndex < lCount; ++nIndex)
					{
						XmlUtils::CXmlNode oNodeFormula;
						oList.GetAt(nIndex, oNodeFormula);

						m_oManager.AddFormula(oNodeFormula.GetAttributeOrValue(_T("eqn")));
					}
				}

				return true;
			}

			return false;
		}

	private:

		inline LONG GetFormatedValue(LONG nIndex, const CSimpleArray<std::wstring>& oArray)
		{
			ParamType eParamType	=	ptValue;
			bool bRes				=	true;
			LONG lValue				=	GetValue (oArray[nIndex], eParamType, bRes);

			switch (eParamType)
			{
			case ptFormula:
				{ 
					lValue			=	m_oManager.m_arResults[lValue]; 
					break; 
				}
			case ptAdjust: 
				{ 
					lValue = (*(m_oManager.m_pAdjustments))[lValue];
					break;
				}
			default:
				break;
			};

			return lValue;
		}

		inline static void ParsePath (const std::wstring& strSource, CSimpleArray<std::wstring>* pArrayResults, bool bIsCleared = true)
		{
			if (NULL == pArrayResults)
				return;

			std::wstring strPath =	strSource;
			int nIndexOld	=	0;

			int nLength		=	strPath.GetLength();
			for (int nIndex = 0; nIndex < nLength; ++nIndex)
			{
				if (nIndex == (nLength - 1))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld));
				}

				WCHAR strChar	= strPath[nIndex];
				WCHAR strChar2	= strPath[nIndex + 1];
				
				if (' ' == strChar)
					strChar = ',';
				
				if (' ' == strChar2)
					strChar2 = ',';

				if (IsAlpha(strChar) && (',' == strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
					pArrayResults->Add(_T("0"));											//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
				}
				else if (IsDigit(strChar) && (',' == strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
				}
				else if ((',' == strChar) && (',' == strChar2))
				{
					pArrayResults->Add(_T("0"));
				}
				else if ((',' == strChar) && IsAlpha(strChar2))
				{
					pArrayResults->Add(_T("0"));
					nIndexOld = nIndex + 1;
				}
				else if ((',' == strChar) && IsDigit(strChar2))
				{
					nIndexOld = nIndex + 1;
				}
				else if (IsAlpha(strChar) && IsDigit(strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
					nIndexOld = nIndex + 1;
				}
				else if (IsDigit(strChar) && IsAlpha(strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
					nIndexOld = nIndex + 1;
				}
				else if (IsDigit(strChar) && ('@' == strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );

					++nIndex;
					nIndexOld = nIndex;
				}
				else if (IsDigit(strChar) && ('#' == strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );

					++nIndex;
					nIndexOld = nIndex;
				}
				else if (IsAlpha(strChar) && ('@' == strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );

					++nIndex;
					nIndexOld = nIndex;
				}
				else if (IsAlpha(strChar) && ('#' == strChar2))
				{
					pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );

					++nIndex;
					nIndexOld = nIndex;
				}
				else if (('x' == strChar) && IsAlpha(strChar2))
				{
					pArrayResults->Add(_T("x"));											//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
					nIndexOld = nIndex + 1;
				}
				else if (IsAlpha(strChar) && IsAlpha(strChar2))
				{
					//if ((('n'==strChar) && ('f'==strChar2)) || (('n'==strChar) && ('s'==strChar2)))
					//{
					//	pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 2));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
					//	++nIndex;
					//	nIndexOld = nIndex + 1;
					//}
					//else
					{
						pArrayResults->Add(strPath.Mid(nIndexOld, nIndex - nIndexOld + 1));		//ATLTRACE (L"COMMAND : %s\n",pArrayResults->operator[](pArrayResults->GetSize()-1) );
						nIndexOld = nIndex + 1;
					}
				}
			}

			return;
		}

		inline static bool IsDigit (const WCHAR& c)
		{
			return (((c >= '0') && (c <= '9')) || (c == '-'));
		}
		inline static bool IsAlpha (const WCHAR& c)
		{
			return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
		}

		inline static bool IsNumber (const std::wstring& str)
		{
			for (int nIndex = 0; nIndex < str.GetLength(); ++nIndex)
			{
				if (!IsDigit(str[nIndex]))
				{
					return false;
				}
			}
			return true;
		}

		inline static bool IsCommand (const std::wstring& str)
		{
			if (str == std::wstring(_T("m")) || str == std::wstring(_T("l")) || str == std::wstring(_T("x")) ||
				str == std::wstring(_T("e")) || str == std::wstring(_T("r")) || str == std::wstring(_T("c")) || str == std::wstring(_T("v")) ||
				str == std::wstring(_T("nf")) || str == std::wstring(_T("ns")) || str == std::wstring(_T("n")) || str == std::wstring(_T("s")) || str == std::wstring(_T("f")) )
				return true;

			return false;
		}

		inline static LONG GetValue (const std::wstring& strParam, ParamType& ptType, bool& bRes, long lShapeWidth = ShapeSizeVML, long lShapeHeight = ShapeSizeVML)
		{
			ptType = ptValue;
			bRes = true;
			if ('#' == strParam[0])
			{
				ptType = ptAdjust;
				return (LONG)XmlUtils::GetInteger(strParam.Mid(1));
			}
			else if ('@' == strParam[0])
			{
				ptType = ptFormula;
				return (LONG)XmlUtils::GetInteger(strParam.Mid(1));
			}
			else if (!IsNumber(strParam))
			{
				if (_T("width") == strParam)
				{
					return lShapeWidth;
				}
				else if (_T("height") == strParam)
				{
					return lShapeHeight;
				}
				else
				{
					bRes = false;
					return 0;
				}
			}	
			else
			{
				ptType = ptValue;
				return (LONG)XmlUtils::GetInteger(strParam);
			}
		}

	public:

		int		m_nType;
		BOOL	m_bIsSimple;

		BOOL	m_bHaveCurves;		

		OfficeArt::CMSOArray<OfficeArt::CPoint32>	m_oPoints;
		OfficeArt::CMSOArray<unsigned short>		m_oSegments;

		CFormulasManager		m_oManager;
		CSimpleArray<long>		m_arAdjustments;
		CSimpleArray<double>	Guides;

	};
}
