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

class ListFile {
    public:
        ListFile(const char* dir_name);
        ~ListFile();

        const vector<string> & get_all_fliename(void);
        const vector<string> & get_cpp_fliename(void);
        const vector<string> & get_head_fliename(void);

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
