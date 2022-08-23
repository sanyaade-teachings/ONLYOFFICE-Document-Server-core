#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "streamrw.h"
#include "../../DesktopEditor/common/File.h"

using namespace testing;
using namespace std;
using namespace CFCPP;

struct StreamRWTest : testing::Test
{
    string filename;
    Stream stream;
    shared_ptr<StreamRW> rw;
    const char symbol = 'a';
    const int integer = 13;

    StreamRWTest() :
        filename("../../../data/types.bin"),
        stream(OpenFileStream(filename, true)),
        rw(new StreamRW(stream))
    {
    }

    ~StreamRWTest()
    {
    }
};


TEST_F(StreamRWTest, test_stream_open)
{
    EXPECT_TRUE(IsOpen(stream));
}

TEST_F(StreamRWTest, test_stream_write)
{
    rw->Seek(0);
    rw->Write(symbol);
    rw->Write(integer);
    stream->flush();
    EXPECT_EQ((int)Length(stream), 5);
}


TEST_F(StreamRWTest, test_stream_read)
{
    EXPECT_EQ(rw->Seek(0), 0);
    EXPECT_EQ(rw->Read<char>(), symbol);
    EXPECT_EQ(rw->Read<int>(), integer);
    remove(filename.c_str());
}

TEST_F(StreamRWTest, test_stream_rw_array)
{
    int sarr[3] = {99, 0, -3};
    int darr[3] = {-1,-1,-1};
    rw->WriteArray(reinterpret_cast<char*>(sarr), sizeof (sarr));
    rw->Seek(0);
    rw->ReadArray(reinterpret_cast<char*>(darr), sizeof (darr));
    EXPECT_EQ(sarr[2], darr[2]);

    remove(filename.c_str());
}
