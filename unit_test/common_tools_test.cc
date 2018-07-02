#include "gtest/gtest.h"
#include "../common_tools.h"

#include "filenamereader.h"
#include "filetxtreader.h"

//using ::testing::Return; 
//using ::testing::_;
//using ::testing::DoAll;
//
using namespace std;

class ListFileValidationTest: public testing::Test
{

protected:
    void SetUp();
    void TearDown();

public:
    /**
     * @brief     测试TicketTimeValidation::operator()
     * @param[in]
     * @param[out]
     * @return
     */
    void operatorTest();

private:
    void parseOperatorParam(const string& fileName,string &file_cnt,string &dir_name);
    // 读取测试数据文件名
    FileNameReader _fileNameReader;
    // 解析测试数据
    FileTxtReader _fileTxtReader;

    vector<string> _vecOperatorFileName;

};

TEST_F(ListFileValidationTest, operatorTest)
{
    operatorTest();
}

void ListFileValidationTest::SetUp()
{
    cout << "ListFile gtest setup"<<endl;
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
    cout << "ListFile gtest teardown()"<<endl;
}

void ListFileValidationTest::operatorTest()
{
    cout<< "operatorTest"<<endl;

    string file_cnt;
    string dir_name;
    for(unsigned int i = 0; i < _vecOperatorFileName.size(); i++)
    {
        parseOperatorParam(_vecOperatorFileName[i], file_cnt, dir_name);
    }

    ListFile   proj_dir(dir_name.c_str());    
    int num = atoi(file_cnt.c_str());
    EXPECT_EQ(num, proj_dir.get_all_file_count());
}

void ListFileValidationTest::parseOperatorParam(const string& fileName, string &file_cnt,string &dir_name)
{
    cout<< "parseOperatorParam"<<endl;

    cout<< "fileName = " << fileName<<endl;
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
            cout << "parseOperatorParam get dir name = " << dir_name<< endl;
        }

        rapidxml::xml_node<>* issueDateTimeNode = inputNode->first_node("fileCnt");
        if(NULL != issueDateTimeNode)
        {
            file_cnt = issueDateTimeNode->value();
            cout << "parseOperatorParam get file_cnt = " << file_cnt<< endl;
        }
    }

}
