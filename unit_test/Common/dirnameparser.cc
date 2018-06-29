/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       testdatadirnameparser.cc
 * @brief      
 *
 * @details    (��ϸ�����ؼ���)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    ��Ʒ�汾��Ϣ1.0.0 2016-4-12 ��� ����
 * @version    ��Ʒ�汾��Ϣx.x.x yyyy-mm-dd ���� �޸���Ϣ
 */

#include "dirnameparser.h"

string DirNameParser::parseDirName(const string& fileName, const string& funName)
{
    // ��ȡxml�ļ��������
    FileTxtReader fileTxtReader;
    string fileTxt;
    try
    {
        // ��������ļ���Ϊ��,����Ĭ��·��
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

    // rapidxml ����xml�ַ���
    rapidxml::xml_document<> doc;
    char* pFileTxt =  const_cast<char*>(fileTxt.c_str());;
    try
    {
        doc.parse<0>(pFileTxt);
    }
    catch(const rapidxml::parse_error& ex)
    {
        // TODO: ��¼��־,����λ�úͳ�����Ϣ
    }

    // ��xml�ļ��������ָ���ڵ�,��ȡ���б��浥Ԫ��������Ŀ¼��
    string dirName;    // ���淵��ֵ
    rapidxml::xml_node<>* funNameNode = doc.first_node(funName.c_str());
    if(funNameNode != NULL)
    {
        dirName = string(funNameNode->value());
    }

    return dirName;
}
