/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       filetxtreader.cc
 * @brief      
 *
 * @details    (详细描述关键点)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    产品版本信息1.0.0 2016-4-12 吴刚 创建
 * @version    产品版本信息x.x.x yyyy-mm-dd 姓名 修改信息
 */

#include "filetxtreader.h"

string FileTxtReader::getFileTxt(const string& fileName)
{
    // fileName不能是空字符串
    assert(!fileName.empty());

    string fileTxt;
    try
    {
        // 利用rapidxml的rapidxml::file模板提供的读取文件内容的功能
        rapidxml::file<> file(fileName.c_str());

        // data()返回char*指针，指向文件里的内容
        fileTxt = string(file.data());
    }
    catch(const runtime_error& ex)
    {
        // TODO: 写日志文件
        throw runtime_error(ex.what());
    }

    return fileTxt;
}


