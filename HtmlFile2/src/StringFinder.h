#ifndef STRINGFINDER_H
#define STRINGFINDER_H

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <vector>

namespace NSStringFinder 
{
	template <typename StringType>
	StringType FindPropety(const StringType& sString, const StringType& sProperty, const StringType& sDelimiter, const StringType& sEnding)
	{
		size_t unEndPosition = 0;
		return FindPropety(sString, sProperty, sDelimiter, sEnding, 0, unEndPosition);
	}
	
	template <typename StringType>
	StringType FindPropety(const StringType& sString, const StringType& sProperty, const StringType& sDelimiter, const StringType& sEnding, const size_t& unStarting, size_t& unEndPosition)
	{
		if (sString.length() < unStarting)
			return StringType();

		typedef const boost::iterator_range<typename StringType::const_iterator> StringRange;

		StringRange itFound = boost::algorithm::ifind_first(StringRange(sString.begin() + unStarting, sString.end()), sProperty);

		if (itFound.empty())
			return StringType();

		StringRange itFoundBegin = boost::algorithm::ifind_first(StringRange(itFound.end(), sString.end()), sDelimiter);

		if (itFoundBegin.empty())
			return StringType();

		StringRange itFoundEnd = boost::algorithm::ifind_first(StringRange(itFoundBegin.end(), sString.end()), sEnding);

		if (itFoundEnd.empty())
			return StringType();

		unEndPosition += (itFoundEnd.end() - sString.begin());

		StringType sValue{itFoundBegin.end(), itFoundEnd.begin()};
		boost::algorithm::trim(sValue);
		return sValue;
	}

	template <typename StringType>
	StringType FindPropety(const StringType& sString, const StringType& sProperty, const std::vector<StringType>& arDelimiters, const std::vector<StringType>& arEndings, const size_t& unStarting, size_t& unEndPosition)
	{
		if (sString.length() < unStarting)
			return StringType();

		std::string sRegexValue = "(?i)" + std::string(sProperty.begin(), sProperty.end());

		if (!arDelimiters.empty())
		{
			sRegexValue += "\\s*[";
			for (const StringType& sDelimiter : arDelimiters)
				sRegexValue +=  std::string(sDelimiter.begin(), sDelimiter.end()) + "|";
			sRegexValue.pop_back();
			sRegexValue += "]{1}";
		}

		if (!arEndings.empty())
		{
			std::string sEndingValue;

			for (const StringType& sEnding : arEndings)
				sEndingValue +=  std::string(sEnding.begin(), sEnding.end()) + "|";

			sEndingValue.pop_back();

			sRegexValue += "\\s*(.[^" + sEndingValue + "]*)\\s*[" + sEndingValue + "]?";
		}
		else
			sRegexValue += "\\s*(.*)[\\n|\\r]?";

		boost::regex oRegex(sRegexValue);
		boost::match_results<typename StringType::const_iterator> oResult;

		if (!boost::regex_search(sString.begin() + unStarting, sString.end(), oResult, oRegex))
			return StringType();

		unEndPosition = unStarting + oResult.position() + oResult.length();

		StringType sValue(oResult[1]);
		boost::algorithm::trim(sValue);

		return sValue;
	}

	template <typename StringType>
	StringType FindPropety(const StringType& sString, const StringType& sProperty, const std::vector<StringType>& arDelimiters, const std::vector<StringType>& arEndings, const size_t& unStarting = 0)
	{
		size_t unTempEnding = 0;
		return FindPropety(sString, sProperty, arDelimiters, arEndings, unStarting, unTempEnding);
	}

	template <typename StringType, typename StringEndgeType>
	void CutInside(StringType& sString, const StringEndgeType& sLeftEdge, const StringEndgeType& sRightEdge)
	{
		typedef const boost::iterator_range<typename StringType::const_iterator> StringRange;

		StringRange itFoundBegin = boost::algorithm::ifind_first(StringRange(sString.begin(), sString.end()), sLeftEdge);

		if (itFoundBegin.empty())
			return;

		StringRange itFoundEnd = boost::algorithm::ifind_first(StringRange(itFoundBegin.end(), sString.cend()), sRightEdge);

		if (itFoundEnd.empty())
		{
			sString = StringType{itFoundBegin.end(), sString.cend()};
			return;
		}

		sString = StringType{itFoundBegin.end(), itFoundEnd.begin()};
	}

	template <typename StringType, typename StringEdgeType>
	void CutInside(StringType& sString, const StringEdgeType& sEdge)
	{
		CutInside(sString, sEdge, sEdge);
	}

	template <typename StringFirstType, typename StringSecondType>
	bool Equals(const StringFirstType& sFirstString, const StringSecondType& sSecondString)
	{
		return boost::iequals(sFirstString, sSecondString);
	}

	template <typename StringFirstType, typename StringSecondType>
	bool EqualOf(const StringFirstType& sFirstString, const std::vector<StringSecondType>& arStrings)
	{
		for (const StringFirstType& sString : arStrings)
			if (boost::iequals(sFirstString, sString))
				return true;

		return false;
	}

	template <typename StringFirstType, typename StringSecondType>
	bool EqualOf(const StringFirstType& sFirstString, const std::initializer_list<StringSecondType>& arStrings)
	{
		for (const StringFirstType& sString : arStrings)
			if (boost::iequals(sFirstString, sString))
				return true;

		return false;
	}

	template <typename StringType, typename StringValueType>
	bool Find(const StringType& sString, const StringValueType& sValue)
	{
		return !boost::algorithm::ifind_first(sString, sValue).empty();
	}

	int ToInt(const std::wstring& oValue, int nMinValue = 0)
	{
		boost::wregex oRegex(LR"((-?\.\d+|-?\d+(\.\d+)?))");

		boost::match_results<typename std::wstring::const_iterator> oResult;

		if (!boost::regex_search(oValue.begin(), oValue.end(), oResult, oRegex))
			return nMinValue;

		const int nValue = std::stoi(*oResult.begin());

		return (nValue >= nMinValue) ? nValue : nMinValue;
	}
	
	int ToDouble(const std::wstring& oValue, double dMinValue = 0.)
	{
		boost::wregex oRegex(LR"((-?\.\d+|-?\d+(\.\d+)?))");

		boost::match_results<typename std::wstring::const_iterator> oResult;

		if (!boost::regex_search(oValue.begin(), oValue.end(), oResult, oRegex))
			return dMinValue;

		const double dValue = std::stod(*oResult.begin());

		return (dValue >= dMinValue) ? dValue : dMinValue;
	}
}

#endif // STRINGFINDER_H
