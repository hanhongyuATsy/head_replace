
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
    dirName = "./unit_test/data/";
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

    string file_cnt;
    string dir_name;
    for(unsigned int i = 0; i < _vecOperatorFileName.size(); i++)
    {
        parseOperatorParam(_vecOperatorFileName[i], file_cnt, dir_name);

        ListFile   proj_dir(dir_name.c_str());    
        int num = atoi(file_cnt.c_str());
        EXPECT_EQ(num, proj_dir.get_all_file_count());
    }
}

void ListFileValidationTest::parseOperatorParam(const string& fileName, string &file_cnt,string &dir_name)
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
            dir_name = isDateDirNode->value();
            LOGFUNC("dir_name= %s\n", dir_name.c_str());
        }

        rapidxml::xml_node<>* issueDateTimeNode = inputNode->first_node("fileCnt");
        if(NULL != issueDateTimeNode)
        {
            file_cnt = issueDateTimeNode->value();
            LOGFUNC("file_cnt= %s\n", file_cnt.c_str());
        }
    }

}
