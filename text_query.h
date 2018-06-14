#ifndef _TEXT_QUERY_H_
#define _TEXT_QUERY_H_


#include<iostream>  
#include<string>  
#include<set>
#include<map>
#include<vector>
#include <fstream>

#include<stdio.h>  
#include <errno.h>  
#include<stdlib.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>  

using namespace std;  

class TextQuery {
    public:
        typedef std::vector<std::string>::size_type line_no;

        void read_file(const char *file_name);
        vector<line_no> query_str_location(string str);        
        vector<line_no> query_str_location(string str1, string str2);        

        string  query_str_between_towstr(line_no line, string str_first, string str_last);        

        int file_substitute_string(string src_str, string dst_str);
        int file_substitute_string(line_no line, string src_str, string dst_str);

        void write_file(const char *file_name)
    private:
        vector<string> file_buf;

        ifstream& open_file(ifstream &in, const string &file);
        void store_file(ifstream &is);

}

/*
class ReplaceHeadFile {
    public:
        int build_head_dir_map(vector<string> *head_file);
        int replace_head_to_headdir(const char *file_name);
        void display_map();
    prvate:
        map<string, string> head_headdir_map;

}
*/








#endif
