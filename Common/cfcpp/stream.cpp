/*
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
#include "stream.h"
#include "../../DesktopEditor/common/File.h"
#include <algorithm>


std::streamsize CFCPP::Length(const CFCPP::Stream& st)
{
    if (st.get() == nullptr)
        return 0;

    auto curPos = st->tell();
    st->seek(0, std::ios_base::end);
    auto ssize = st->tell();
    st->seek(curPos);

    return ssize;
}

CFCPP::Stream CFCPP::OpenFileStream(std::wstring filename, bool bRewrite, bool trunc)
{
    BYTE* pUtf8 = nullptr;
    LONG lLen = 0;
    NSFile::CUtf8Converter::GetUtf8StringFromUnicode(filename.c_str(), filename.length(), pUtf8, lLen, false);
    std::string utf8filename(pUtf8, pUtf8 + lLen);
    delete [] pUtf8;

    return OpenFileStream(utf8filename, bRewrite, trunc);
}

CFCPP::Stream CFCPP::OpenFileStream(std::string filename, bool bRewrite, bool trunc)
{
    CFCPP::Stream st;

    // it's not good, but otherwise file doesn't create or if use ios::app, then the seek for writing will be blocked
    if (bRewrite)
        std::fstream create(filename, std::ios::app | std::ios::out);

    if (trunc && bRewrite)
        st.reset(new FStreamWrapper(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc));
    else if (bRewrite)
        st.reset(new FStreamWrapper(filename, std::ios::binary | std::ios::in | std::ios::out));
    else
        st.reset(new FStreamWrapper(filename, std::ios::binary | std::ios::in));

    return st;
}

bool CFCPP::IsOpen(const Stream &st)
{
    if (std::dynamic_pointer_cast<FStreamWrapper>(st))
        return std::static_pointer_cast<FStreamWrapper>(st)->is_open();

    return false;
}

std::string CFCPP::CorrectUnixPath(const std::string original)
{
    #if !defined(_WIN32) && !defined (_WIN64)
    return original;
    #else
        auto str = original;
        std::replace(str.begin(), str.end(), '/', '\\');
        return str;
    #endif
}

int CFCPP::FileLenght(std::wstring filename)
{
    auto stream = OpenFileStream(filename);
    auto lenght = Length(stream);
    stream->close();

    return lenght;
}

ULONG64 CFCPP::FileFNVHash(std::wstring filename, int len, int offset)
{

    auto stream = OpenFileStream(filename);
    if (!IsOpen(stream))
        return 0;

    if (len < 0)
        len = Length(stream);

    stream->seek(offset);

    ULONG64 h = 2166136261;
    constexpr int bufLen = 0x2000;
    char buffer[bufLen];
    while (len > 0)
    {
        memset(buffer, 0, bufLen);
        int readLen = std::min(bufLen, len);
        stream->read(buffer, readLen);
        int i;

        for (i = 0; i < readLen; i++)
            h = (h * 16777619) ^ buffer[i];

        len -= readLen;
    }

    return h;
}
