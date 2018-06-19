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

enum coding_format {
    UTF8  = 0,
    GB18030 = 0,
};

/* class TextQuery for read a file in buf(vecotr)
 * change file string and read file coding format
 * and file lines et.
 *
 */

class TextQuery {
    public:
        typedef std::vector<std::string>::size_type line_no;

        int read_file(const char *file_name);
        vector<line_no> query_str_location(string str);        
        vector<line_no> query_str_location(string str1, string str2);        

        string get_line_text(line_no);
        //string  query_str_between_towstr(line_no line_num, string str_first, string str_last);        

        int file_substitute_string(string src_str, string dst_str);
        int file_substitute_string(line_no line_num, string src_str, string dst_str);
        //int convert_format(enum coding_format src_format);
        string get_coding_format(const char *file_name);

        int get_file_lines(void);

        int write_file(const char *file_name);
        int show_file();
    private:
        vector<string> file_buf;
        int my_system(char *cmd, char* buff, int len);

        ifstream& open_file(ifstream &in, const string &file);
        void store_file(ifstream &is);
};




#endif
