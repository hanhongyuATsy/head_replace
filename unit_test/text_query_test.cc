#include    "text_query_test.h"

TEST_F(TextQueryTest,read_file_Test)
{
    read_file_Test();
}

void TextQueryTest::SetUp()
{
    LOGFUNC("setup\n");
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
    LOGFUNC("TearDown\n");
}

void TextQueryTest::read_file_Test()
{
    struct file_info file_info;

    int retval = 0;
    for(unsigned int i = 0; i < _vecOperatorFileName.size(); i++)
    {
        parseOperatorParam(_vecOperatorFileName[i], file_info);

        EXPECT_EQ(0, file.read_file(file_info.name.c_str()));
        EXPECT_EQ(file_info.lines, file.get_file_lines());
    }
}

void TextQueryTest::parseOperatorParam(const string& fileName, struct file_info &file)
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
        rapidxml::xml_node<>* isReadFileNameNode= inputNode->first_node("file");
        if(NULL != isReadFileNameNode)
        {
            file.name = isReadFileNameNode->value();
            LOGFUNC("file.name = %s\n", file.name.c_str());
        }
        rapidxml::xml_node<>* isReadFileLinesNode= inputNode->first_node("lines");
        if(NULL != isReadFileLinesNode)
        {
            string lines = isReadFileLinesNode->value();
            file.lines = atoi(lines.c_str());
            LOGFUNC("file.lines = %d\n", file.lines);
        }
    }

    rapidxml::xml_node<>* outputNode = rootNode->first_node("output");

    if(NULL != outputNode)
    {
        rapidxml::xml_node<>* isretValNode = outputNode->first_node("retVal");
        if(NULL != isretValNode)
        {
            string retval = isretValNode->value();
            LOGFUNC("retval = %s\n", retval.c_str());
        }
    }

}
