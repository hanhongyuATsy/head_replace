/**
 * Copyright (c) 2016, Travelsky
 * All rights reserved.
 * Travelsky CONFIDENTIAL
 *
 * @file       filetxtreader.cc
 * @brief      
 *
 * @details    (��ϸ�����ؼ���)
 *
 * @author     gangwu@
 * @date       2016-4-12
 * @version    ��Ʒ�汾��Ϣ1.0.0 2016-4-12 ��� ����
 * @version    ��Ʒ�汾��Ϣx.x.x yyyy-mm-dd ���� �޸���Ϣ
 */

#include "filetxtreader.h"

string FileTxtReader::getFileTxt(const string& fileName)
{
    // fileName�����ǿ��ַ���
    assert(!fileName.empty());

    string fileTxt;
    try
    {
        // ����rapidxml��rapidxml::fileģ���ṩ�Ķ�ȡ�ļ����ݵĹ���
        rapidxml::file<> file(fileName.c_str());

        // data()����char*ָ�룬ָ���ļ��������
        fileTxt = string(file.data());
    }
    catch(const runtime_error& ex)
    {
        // TODO: д��־�ļ�
        throw runtime_error(ex.what());
    }

    return fileTxt;
}


