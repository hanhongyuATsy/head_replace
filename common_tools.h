#ifndef _COMMON_TOOLS_H
#define _COMMON_TOOLS_H

#include<iostream>  
#include<string>  
#include<vector>
#include <dirent.h>

#include<stdio.h>  
#include <dirent.h>  
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>  

#include <fstream>

using namespace std;  

enum file_type {
    dir_file = 0,
    text_file = 1,

    unknow_file = -1,
};
/* 
 * class ListFile for Traversing directory
 * and classify file by exten name.
 *
 *  
 *
 *
 * */

class ListFile {
    public:
        ListFile(const char* dir_name);
        ~ListFile();

        typedef std::vector<std::string>::size_type file_path_no;
        const vector<string> & get_all_fliename(void);
        const vector<string> & get_cpp_fliename(void);
        const vector<string> & get_head_fliename(void);

        int get_all_file_count(void);
        int get_cpp_file_count(void);
        int get_head_file_count(void);

    private:
        int traverse_dir(const char * dir_name);
        enum file_type analyse_file_types(const char *file_name);  
        int analyse_exten_name_types(string file_name);  
    private:
        vector<string> all_file_name;
        vector<string> cpp_file_name;
        vector<string> head_file_name;
};



#endif
