/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       testdatadirnameparser.h
 * @brief      测试数据目录解析类
 *
 * @details    指定测试函数名字符串，获取测试数据存放的目录
 *             本希望将测试数据目录做成配置模式,后续改成了在测试代码里直接硬编码了测试目录,比配置更方便维护管理
 *
 * @author     gangwu@
 * @date       2016年4月12日
 * @version    产品版本信息1.0.0 2016-4-12 吴刚 创建
 * @version    产品版本信息x.x.x yyyy-mm-dd 姓名 修改信息
 */

#ifndef UNITTEST_COMMON_DIRNAMEPARSER_H_
#define UNITTEST_COMMON_DIRNAMEPARSER_H_

#include <string>

#include "rapidxml.hpp"

#include "filetxtreader.h"

using namespace std;

class DirNameParser
{
public:
    /**
     * @brief       指定文件名和被测函数名，解析出被测函数对应的单元测试数据所在的目录名
     * @param[in]   fileName        文件名，文件里存放单元测试数据所在的目录名
     * @param[in]   funName         被测函数名
     * @return      被测函数对应的单元测试数据所在的目录名
     */
    string parseDirName(const string& fileName, const string& funName);
};

#endif /* UNITTEST_COMMON_DIRNAMEPARSER_H_ */
