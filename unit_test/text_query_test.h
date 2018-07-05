#ifndef _TEXT_QUERY_TEST_H
#define _TEXT_QUERY_TEST_H

#include "gtest/gtest.h"
#include "filenamereader.h"
#include "filetxtreader.h"
#include "text_query.h"
#include "def_log.h"


using namespace std;

struct file_info {
    string name;
    int lines;
};

class TextQueryTest: public testing::Test
{

protected:
    void SetUp();
    void TearDown();

public:

    void read_file_Test();
//    void query_str_location_Test();
//    void get_file_lines_Test();
//    void get_coding_format_Test();



private:
    void parseOperatorParam(const string& fileName, struct file_info &file);
    // 读取测试数据文件名
    FileNameReader _fileNameReader;
    // 解析测试数据
    FileTxtReader _fileTxtReader;

    vector<string> _vecOperatorFileName;

    TextQuery file;    

};

#endif
