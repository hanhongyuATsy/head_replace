/**
 * Copyright (c) 2014, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       testdatafilenamereader.h
 * @brief      读取指定目录下所有普通文件名
 *
 * @details    (详细描述关键点)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    产品版本信息1.0.0 2016-4-12 吴刚 创建
 * @version    产品版本信息x.x.x yyyy-mm-dd 姓名 修改信息
 */

#ifndef UNITTEST_COMMON_FILENAMEREADER_H_
#define UNITTEST_COMMON_FILENAMEREADER_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <string>
#include <vector>

#include "freefunc.h"

using namespace std;

class FileNameReader
{
public:
    /**
     * @brief           读取dirName目录下的所有普通文件,并保存到vecFileName中
     *                  vecFileName存储的是 路径+文件名
     * @param[in]       dirName        待读取的目录名
     * @param[out]      vecFileName    dirName目录下普通文件名的集合
     * @return          dirName目录下普通文件的个数
     */
    int readFileName(const string& dirName, vector<string>& vecFileName);
};

#endif /* UNITTEST_COMMON_FILENAMEREADER_H_ */
