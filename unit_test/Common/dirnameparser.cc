/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       testdatadirnameparser.cc
 * @brief      
 *
 * @details    (详细描述关键点)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    产品版本信息1.0.0 2016-4-12 吴刚 创建
 * @version    产品版本信息x.x.x yyyy-mm-dd 姓名 修改信息
 */

#include "dirnameparser.h"

string DirNameParser::parseDirName(const string& fileName, const string& funName)
{
    // 读取xml文件里的内容
    FileTxtReader fileTxtReader;
    string fileTxt;
    try
    {
        // 如果传递文件名为空,尝试默认路径
        if(fileName.empty())
        {
            fileTxt = fileTxtReader.getFileTxt(string("./data.xml"));
        }
        else
        {
            fileTxt = fileTxtReader.getFileTxt(fileName);
        }
    }
    catch(const runtime_error& ex)
    {
        throw runtime_error(ex.what());
    }

    // rapidxml 解析xml字符串
    rapidxml::xml_document<> doc;
    char* pFileTxt =  const_cast<char*>(fileTxt.c_str());;
    try
    {
        doc.parse<0>(pFileTxt);
    }
    catch(const rapidxml::parse_error& ex)
    {
        // TODO: 记录日志,出错位置和出错信息
    }

    // 从xml文件里解析出指定节点,读取其中保存单元测试数据目录名
    string dirName;    // 保存返回值
    rapidxml::xml_node<>* funNameNode = doc.first_node(funName.c_str());
    if(funNameNode != NULL)
    {
        dirName = string(funNameNode->value());
    }

    return dirName;
}
