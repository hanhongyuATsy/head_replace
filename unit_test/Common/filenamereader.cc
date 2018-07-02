/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       testdatafilenamereader.cc
 * @brief      
 *
 * @details    (��ϸ�����ؼ���)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    ��Ʒ�汾��Ϣ1.0.0 2016-4-12 ��� ����
 * @version    ��Ʒ�汾��Ϣx.x.x yyyy-mm-dd ���� �޸���Ϣ
 */

#include "filenamereader.h"
#include "freefunc.h"

int FileNameReader::readFileName(const string& dirName, vector<string>& vecFileName)
{
    // ��Ŀ¼
    DIR* dp = opendir(dirName.c_str());

    if(dp != NULL)
    {
        int ret = 0;      // ����readdir�����ķ���ֵ, -1��ʾ��ȡ����
        struct dirent* dir = NULL;    // ָ���pD��ȡ��struct dirent

        // ѭ����ȡĿ¼��ÿ���ļ�,����ͨ�ļ����浽vecFileName
        while((dir = readdir(dp)) != NULL)
        {
            /*
             * û�в�ȡ�����д��,����Ϊ�������е�ϵͳ��֧��struct dirent�ṹ����d_type
            string fileName = dirName;
            if(DT_REG == dir->d_type)
            {
                fileName += string(dir->d_name);
                vecFileName.push_back(string(dir->d_name));
            }
            */

            // ·��+�ļ���
            string fileName = dirName + "/" + string(dir->d_name);

            /*
             * commented at 2016-4-28
             * ��Ŀ¼����Դ��һЩ˵���ĵ�,���Բ���ͨ���ļ����ͽ�������
            */
            // �ж���ͨ�ļ�
            /*
            struct stat buf;
            stat(fileName.c_str(), &buf);
            if(S_ISREG(buf.st_mode))
            {
                vecFileName.push_back(fileName);
            }
            */

            // ��Ԫ�������ݴ����xml�ļ���
            // if(fileName.find(".xml") != string::npos)
            // ����.xx.xml.swp��ʱ�ļ�����
            if(FreeFun::wildcardCompare("*.xml", fileName.c_str()))
            {
                vecFileName.push_back(fileName);
            }
        }
    }
    else
    {
        // TODO: ��¼��־,��ʾ����(strerrno)
    }

    return vecFileName.size();
}
