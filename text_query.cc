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

#include "text_query.h"
using namespace std;  

ifstream& TextQuery:: open_file(ifstream &in, const string &file)
{
    in.close();  // close in case it was already open
    in.clear();  // clear any existing errors
    file_buf.clear();
    //cout<< "read file size =="<< file_buf.size()<<endl;

    // if the open fails, the stream will be in an invalid state
    in.open(file.c_str()); // open the file we were given

    return in; // condition state is good if open succeeded
}

void TextQuery::store_file(ifstream &is)
{
    string textline;
    while (getline(is, textline))
       file_buf.push_back(textline);
}

int TextQuery::read_file(const char *file_name)
{

    ifstream infile;
    if (!open_file(infile, file_name)) {
        cerr << "No input file!" << endl;
        return EXIT_FAILURE;
    }

    store_file(infile);
    //cout<< "read file size =="<< file_buf.size()<<endl;

    infile.close();
    return 0;
}

vector<TextQuery::line_no> TextQuery::query_str_location(string str)       
{
    vector<line_no> line_no_vec;
    for (line_no line_num = 0; line_num != file_buf.size(); ++line_num)
    {
        int local = file_buf[line_num].find(str); 
        if(local >= 0) {
            line_no_vec.push_back(line_num);
        }
    }
    return line_no_vec;
}

vector<TextQuery::line_no> TextQuery::query_str_location(string str1, string str2)        
{
    vector<line_no> line_no_vec;
    for (line_no line_num = 0; line_num != file_buf.size(); ++line_num)
    {
        int local1 = file_buf[line_num].find(str1); 
        int local2 = file_buf[line_num].find(str2); 
        if ((local1 >= 0) && (local2 >= 0)) {
            line_no_vec.push_back(line_num);
        }
    }
    return line_no_vec;
}

int TextQuery::file_substitute_string(string src_str, string dst_str)
{
    int sub_cnt = 0;
    for (line_no line_num = 0; line_num != file_buf.size(); ++line_num)
    {
        int local = file_buf[line_num].find(src_str);    
        //int len_src = src_str.length();
        //cout << len_src << endl;
        if(local >= 0) {
            file_buf[line_num].replace(local, src_str.length(),dst_str);
            //cout<<file_buf[line_num]<<endl;
            sub_cnt++;
        } 
    }

    return sub_cnt;
}

int TextQuery::file_substitute_string(line_no line_num, string src_str, string dst_str)
{
    if(line_num >= 0 && file_buf.size())
    {
        int local = file_buf[line_num].find(src_str);    
        if(local >= 0) {
            file_buf[line_num].replace(local, src_str.length(),dst_str);
            //cout<<file_buf[line_num]<<endl;
        }else {
            printf("can not find src_str\n");
        }
    }
    else
    {
        printf("input line_no over bufsize\n");
        return -1;
    }
}


int TextQuery::write_file(const char * file_name)
{
    ofstream os(file_name);
    if(!os) {
        cout << "ofstream create fail :file name " << file_name << endl;
    }

    for(auto iter = file_buf.begin(); iter != file_buf.end(); ++iter) { 
        //cout << (*iter) << endl;
        os << (*iter) << endl;
    }

    os.close();

    return 0;
}

string TextQuery::get_line_text(line_no line_num) 
{
//    cout<<"fun get_line_text"<< line_num<<endl;
    if (line_num < file_buf.size())
    {
//        cout<<file_buf[line_num]<<endl;
        return file_buf[line_num];    
    }

}

int TextQuery::show_file()
{
    for(auto iter=file_buf.begin(); iter!=file_buf.end();++iter)
        cout<<*iter<<endl;

}
