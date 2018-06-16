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

#include "text_query.h"
#include "replace_headfile.h"
#include "common_tools.h"

using namespace std;  

string ReplaceHeadFile::find_head_name(const string &line_text)
{
    string head_name;
    int local_start = line_text.find("\"");
    if (local_start > 0) {
        string str_temp = line_text.substr(local_start + 1);
        //cout<<str_temp<<endl;
        
        int local_end = str_temp.find("\"");
        if(local_end > 0) 
            head_name = str_temp.substr(0,local_end);
    }

    //cout<<head_name<<endl;
    return head_name;
}

int ReplaceHeadFile::build_head_dir_map(const vector<string> &head_file)
{

    for(auto iter_head = head_file.begin(); iter_head != head_file.end(); ++iter_head) 
    {
        string head_file_dir = (*iter_head).substr(1); 
        int loc_dir = head_file_dir.find("/"); 
        string headfile_dir;

        while(1) {
            if (loc_dir > 0)
            {
                head_file_dir=head_file_dir.substr(loc_dir+1);
                loc_dir = head_file_dir.find("/"); 
                //cout<< loc_dir <<endl;
                //cout<< head_file_dir <<endl;
            }
            else if(loc_dir == 0)
            {
                int loc_end = head_file_dir.find("h");
                headfile_dir = head_file_dir.substr(1,loc_end+1);
                //cout<< headfile_dir<<endl;;
                break;
            }
        }
        int loc_name = head_file_dir.find_last_of("/");
        string head_file_name = head_file_dir.substr(loc_name+1);
        //cout<<head_file_name<<endl;
        head_headdir_map[head_file_name]=head_file_dir;    
    }

    return 0;
}

void ReplaceHeadFile::display_map()
{
    for(auto iter = head_headdir_map.begin(); iter != head_headdir_map.end(); ++iter) 
    {
        cout<<(*iter).first<<" "<<(*iter).second<<endl;
    }

}

int ReplaceHeadFile::replace_head_to_headdir(const char *file_name)
{

    file.read_file(file_name);
    //cout<<file_name<<endl;
    //file.show_file();
    vector<TextQuery::line_no> line = file.query_str_location("#include","\"");
    //cout<<line.size()<<endl;

    for (TextQuery::line_no line_num = 0; line_num != line.size(); ++line_num)
    {
        string line_str = file.get_line_text(line[line_num]);
        string head_file = find_head_name(line_str);

        cout<<"head file name:"<<head_file<<endl;

        if(head_headdir_map.count(head_file)>0)
        {
            file.file_substitute_string(line[line_num], head_file,head_headdir_map[head_file]);
        }
        else
        {
            cout<<"can not find dir head_file:"<<head_file<<endl;
        }
    }
    file.write_file(file_name);
    return 0;
}


//ReplaceHeadFile::ReplaceHeadFile(const char*dir_name):proj(&ListFile(dir_name))
ReplaceHeadFile::ReplaceHeadFile(const char*dir_name):proj_name(dir_name)
{
    //ListFile listfile(dir_name);
    //*proj = &listfile;
}

ReplaceHeadFile::~ReplaceHeadFile()
{
}

int ReplaceHeadFile::run()
{

    //vector<string> file_name_list = proj_root.get_all_fliename();
    int deal_file_cnt = 0;

    ListFile proj(proj_name.c_str());

    vector<string> head_name_list = proj.get_head_fliename();
    vector<string> cpp_name_list = proj.get_cpp_fliename();

    if(head_name_list.size()>0)
        build_head_dir_map(head_name_list);
    else
        return 0;

    display_map();

    for(auto iter = head_name_list.begin(); iter != head_name_list.end(); ++iter){ 
        replace_head_to_headdir((*iter).c_str());
        deal_file_cnt++;
    }

    for(auto iter = cpp_name_list.begin(); iter != cpp_name_list.end(); ++iter) {
        replace_head_to_headdir((*iter).c_str());
        deal_file_cnt++;
    }

    return deal_file_cnt; 
}


