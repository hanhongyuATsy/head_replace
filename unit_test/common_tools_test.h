#ifndef _COMMON_TOOLS_TEST_H
#define _COMMON_TOOLS_TEST_H

#include "gtest/gtest.h"
#include "filenamereader.h"
#include "filetxtreader.h"
#include "../common_tools.h"

//#define _DEBUG

#include "../def_log.h"

using namespace std;

class ListFileValidationTest: public testing::Test
{

protected:
    void SetUp();
    void TearDown();

public:
    /**
     * @brief     测试ListFile::get_all_file_count()
     * @param[in]
     * @param[out]
     * @return
     */
    void get_all_file_count_Test();

private:
    void parseOperatorParam(const string& fileName,string &file_cnt,string &dir_name);
    // 读取测试数据文件名
    FileNameReader _fileNameReader;
    // 解析测试数据
    FileTxtReader _fileTxtReader;

    vector<string> _vecOperatorFileName;

};

#endif
