/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       filetxtreader.h
 * @brief      输入文件名,返回文件内容.
 *
 * @details    (详细描述关键点)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    产品版本信息1.0.0 2016-4-12 吴刚 创建
 * @version    产品版本信息x.x.x yyyy-mm-dd 姓名 修改信息
 */

#ifndef UNITTEST_COMMON_FILETXTREADER_H_
#define UNITTEST_COMMON_FILETXTREADER_H_

#include <cassert>

#include <string>

#include "rapidxml_utils.hpp"

using namespace std;

class FileTxtReader
{
public:
    /**
     * @brief       输入文件名,返回文件内容
     * @param[in]   fileName        文件名
     * @return      文件内容
     */
    string getFileTxt(const string& fileName);
};

#endif /* UNITTEST_COMMON_FILETXTREADER_H_ */
