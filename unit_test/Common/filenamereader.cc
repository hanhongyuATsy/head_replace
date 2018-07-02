/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       testdatafilenamereader.cc
 * @brief      
 *
 * @details    (详细描述关键点)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    产品版本信息1.0.0 2016-4-12 吴刚 创建
 * @version    产品版本信息x.x.x yyyy-mm-dd 姓名 修改信息
 */

#include "filenamereader.h"
#include "freefunc.h"

int FileNameReader::readFileName(const string& dirName, vector<string>& vecFileName)
{
    // 打开目录
    DIR* dp = opendir(dirName.c_str());

    if(dp != NULL)
    {
        int ret = 0;      // 保存readdir函数的返回值, -1表示读取出错
        struct dirent* dir = NULL;    // 指向从pD读取的struct dirent

        // 循环读取目录里每个文件,将普通文件保存到vecFileName
        while((dir = readdir(dp)) != NULL)
        {
            /*
             * 没有采取下面的写法,是因为不是所有的系统都支持struct dirent结构体里d_type
            string fileName = dirName;
            if(DT_REG == dir->d_type)
            {
                fileName += string(dir->d_name);
                vecFileName.push_back(string(dir->d_name));
            }
            */

            // 路径+文件名
            string fileName = dirName + "/" + string(dir->d_name);

            /*
             * commented at 2016-4-28
             * 在目录里可以存放一些说明文档,所以不能通过文件类型进行区分
            */
            // 判断普通文件
            /*
            struct stat buf;
            stat(fileName.c_str(), &buf);
            if(S_ISREG(buf.st_mode))
            {
                vecFileName.push_back(fileName);
            }
            */

            // 单元测试数据存放在xml文件中
            // if(fileName.find(".xml") != string::npos)
            // 避免.xx.xml.swp临时文件干扰
            if(FreeFun::wildcardCompare("*.xml", fileName.c_str()))
            {
                vecFileName.push_back(fileName);
            }
        }
    }
    else
    {
        // TODO: 记录日志,提示错误(strerrno)
    }

    return vecFileName.size();
}
