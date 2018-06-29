/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       testdatadirnameparser.h
 * @brief      ��������Ŀ¼������
 *
 * @details    ָ�����Ժ������ַ�������ȡ�������ݴ�ŵ�Ŀ¼
 *             ��ϣ������������Ŀ¼��������ģʽ,�����ĳ����ڲ��Դ�����ֱ��Ӳ�����˲���Ŀ¼,�����ø�����ά������
 *
 * @author     gangwu@
 * @date       2016��4��12��
 * @version    ��Ʒ�汾��Ϣ1.0.0 2016-4-12 ��� ����
 * @version    ��Ʒ�汾��Ϣx.x.x yyyy-mm-dd ���� �޸���Ϣ
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
     * @brief       ָ���ļ����ͱ��⺯���������������⺯����Ӧ�ĵ�Ԫ�����������ڵ�Ŀ¼��
     * @param[in]   fileName        �ļ������ļ����ŵ�Ԫ�����������ڵ�Ŀ¼��
     * @param[in]   funName         ���⺯����
     * @return      ���⺯����Ӧ�ĵ�Ԫ�����������ڵ�Ŀ¼��
     */
    string parseDirName(const string& fileName, const string& funName);
};

#endif /* UNITTEST_COMMON_DIRNAMEPARSER_H_ */
