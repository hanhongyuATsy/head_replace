#ifndef _REPLACE_HEADFILE_H_
#define _REPLACE_HEADFILE_H_


#include<iostream>  
#include<string>  
#include<set>
#include<map>
#include<vector>
#include <dirent.h>

#include<stdio.h>  
#include <errno.h>  
#include<stdlib.h>  
#include<string.h>  
#include <dirent.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>  

#include <fstream>

#include "common_tools.h"
#include "text_query.h"
#define HEADFILE_MULTI

class ReplaceHeadFile {
    public:
        ReplaceHeadFile(const char *dir_name);
        ~ReplaceHeadFile();
        int run();
    private:
        string find_head_name(const string &line_text);
        int build_head_dir_map(const vector<string> &head_file);
        int compare_str_loc(string, string);
        int replace_head_to_headdir(const char *file_name);

        //ListFile *proj; 

        TextQuery file; 
        string proj_name;

#ifdef HEADFILE_MULTI
        multimap<string, string> head_headdir_multimap;
        void display_multimap();
#else
        map<string, string> head_headdir_map;
        void display_map();
#endif
};



#endif
