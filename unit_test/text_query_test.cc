#include    "text_query_test.h"

TEST_F(TextQueryTest,read_file_Test)
{
    read_file_Test();
}

void TextQueryTest::SetUp()
{
    cout << "TextQueryTestgtest setup"<<endl;
    // 存放测试数据目录,直接赋值,没有采用xml文件管理是为了方便配置
    string dirName;

    // 数单元测试数据存放目录
    dirName = "./unit_test/data/text_query";
    _fileNameReader.readFileName(dirName, _vecOperatorFileName);    // 获取目录下所有.xml文件

    // 排序,为了方便排查
    stable_sort(_vecOperatorFileName.begin(), _vecOperatorFileName.end());
}

void TextQueryTest::TearDown()
{
    cout << "TextQueryTestgtest gtest teardown()"<<endl;
}

void TextQueryTest::read_file_Test()
{
    cout<< "read_file_Test"<<endl;

    string file_name;
    string file_cnt;
    int retval = 0;
    for(unsigned int i = 0; i < _vecOperatorFileName.size(); i++)
    {
        parseOperatorParam(_vecOperatorFileName[i], file_name);

        //ASSERT_GE(retval, file.read_file(file_name.c_str()));
        EXPECT_EQ(0, file.read_file(file_name.c_str()));

    }
}

void TextQueryTest::parseOperatorParam(const string& fileName, string &file)
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
        rapidxml::xml_node<>* isReadFileNameNode= inputNode->first_node("file");
        if(NULL != isReadFileNameNode)
        {
            file = isReadFileNameNode->value();
            cout << "parseOperatorParam get dir name = " << file << endl;
        }
    }

    rapidxml::xml_node<>* outputNode = rootNode->first_node("output");
    string retval;
    if(NULL != outputNode)
    {
        rapidxml::xml_node<>* isretValNode = outputNode->first_node("retVal");
        if(NULL != isretValNode)
        {
            retval = isretValNode->value();
            cout << "parseOperatorParam get retval= " << retval << endl;
        }
    }

}
