
//using ::testing::Return; 
//using ::testing::_;
//using ::testing::DoAll;
//
#include    "common_tools_test.h"

TEST_F(ListFileValidationTest,get_all_file_count_Test)
{
    get_all_file_count_Test();
}

void ListFileValidationTest::SetUp()
{
    LOGFUNC("setup\n");
    // 存放测试数据目录,直接赋值,没有采用xml文件管理是为了方便配置
    string dirName;

    // 数单元测试数据存放目录
    dirName = "./unit_test/data/common_tools";
    _fileNameReader.readFileName(dirName, _vecOperatorFileName);    // 获取目录下所有.xml文件

    // 排序,为了方便排查
    stable_sort(_vecOperatorFileName.begin(), _vecOperatorFileName.end());
}

void ListFileValidationTest::TearDown()
{
    LOGFUNC("TearDown\n");
}

void ListFileValidationTest::get_all_file_count_Test()
{
    struct dir_info dir;

    for(unsigned int i = 0; i < _vecOperatorFileName.size(); i++)
    {
        parseOperatorParam(_vecOperatorFileName[i], dir);

        ListFile   proj_dir(dir.name.c_str());    
        EXPECT_EQ(dir.file_cnt, proj_dir.get_all_file_count());
        EXPECT_EQ(dir.cpp_file_cnt, proj_dir.get_cpp_file_count());
        EXPECT_EQ(dir.head_file_cnt, proj_dir.get_head_file_count());
    }
}

void ListFileValidationTest::parseOperatorParam(const string& fileName, struct dir_info &dir)
{

    LOGFUNC("fileName = %s\n", fileName.c_str());
    string fileTxt = _fileTxtReader.getFileTxt(fileName);
    // rapidxml 解析xml字符串
    rapidxml::xml_document<> doc;
    char* pFileTxt =  const_cast<char*>(fileTxt.c_str());
    try
    {
        doc.parse<0>(pFileTxt);
    }
    catch(const rapidxml::parse_error& ex)
    {
        // TODO: 记录日志,出错位置和出错信息
    }

    // 获取根节点
    rapidxml::xml_node<>* rootNode = doc.first_node("root");

    rapidxml::xml_node<>* inputNode = rootNode->first_node("input");
    if(NULL != inputNode)
    {
        rapidxml::xml_node<>* isDateDirNode= inputNode->first_node("dealDir");
        if(NULL != isDateDirNode)
        {
            dir.name = isDateDirNode->value();
            LOGFUNC("dir_name= %s\n", dir.name.c_str());
        }

        rapidxml::xml_node<>* isFileCntNode = inputNode->first_node("fileCnt");
        if(NULL != isFileCntNode)
        {
            string file_cnt = isFileCntNode->value();
            dir.file_cnt = atoi(file_cnt.c_str());
            LOGFUNC("file_cnt= %s\n", file_cnt.c_str());
        }
        rapidxml::xml_node<>* iscppFileCntNode = inputNode->first_node("cppfileCnt");
        if (NULL != iscppFileCntNode )
        {
            string file_cnt = iscppFileCntNode->value();
            dir.cpp_file_cnt = atoi(file_cnt.c_str());
            LOGFUNC("cppfile_cnt= %s\n", file_cnt.c_str());
        }
        rapidxml::xml_node<>* isheadFileCntNode = inputNode->first_node("cppfileCnt");
        if (NULL != isheadFileCntNode )
        {
            string file_cnt = isheadFileCntNode->value();
            dir.head_file_cnt = atoi(file_cnt.c_str());
            LOGFUNC("headfile_cnt= %s\n", file_cnt.c_str());
        }
    }

}
