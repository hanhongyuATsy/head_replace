#ifndef _COMMON_TOOLS_TEST_H
#define _COMMON_TOOLS_TEST_H

#include "gtest/gtest.h"
#include "filenamereader.h"
#include "filetxtreader.h"
#include "common_tools.h"

//#define _DEBUG

#include "def_log.h"

using namespace std;

struct dir_info {
    string name;
    int file_cnt;
    int cpp_file_cnt;
    int head_file_cnt;
};

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
    void get_cpp_file_count_Test();
    void get_head_file_count_Test();

private:
    void parseOperatorParam(const string& fileName, struct dir_info & dir);
    // 读取测试数据文件名
    FileNameReader _fileNameReader;
    // 解析测试数据
    FileTxtReader _fileTxtReader;

    vector<string> _vecOperatorFileName;

};

#endif
