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
    void parseOperatorParam(const string& fileName,int &file_cnt,string &dir_name);
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
    dirName = "./data/";
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

    int file_cnt = 0;
    string dir_name;
    for(unsigned int i = 0; i < _vecOperatorFileName.size(); i++)
    {
        parseOperatorParam(_vecOperatorFileName[i], file_cnt, dir_name);
    }

    ListFile   proj_dir("/home/hhy/cpp_test/my");    
    EXPECT_EQ(14, proj_dir.get_all_file_count());
}

void ListFileValidationTest::parseOperatorParam(const string& fileName, int &fine_cnt,string &dir_name)
{
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
        rapidxml::xml_node<>* issueDateTimeNode = inputNode->first_node("dir");
        if(NULL != issueDateTimeNode)
        {
            dir_name = issueDateTimeNode->value();
        }
    }

}
