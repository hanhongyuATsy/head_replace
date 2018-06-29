/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       filetxtreader.h
 * @brief      �����ļ���,�����ļ�����.
 *
 * @details    (��ϸ�����ؼ���)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    ��Ʒ�汾��Ϣ1.0.0 2016-4-12 ��� ����
 * @version    ��Ʒ�汾��Ϣx.x.x yyyy-mm-dd ���� �޸���Ϣ
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
     * @brief       �����ļ���,�����ļ�����
     * @param[in]   fileName        �ļ���
     * @return      �ļ�����
     */
    string getFileTxt(const string& fileName);
};

#endif /* UNITTEST_COMMON_FILETXTREADER_H_ */
