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
        string headfile_full_dir(*iter_head); 
        string::size_type loc_dir = headfile_full_dir.find("//"); 
        string::size_type loc_end = headfile_full_dir.find(".h");

        string headfile_dir = headfile_full_dir.substr(loc_dir+2,loc_end+1);
        //cout<<headfile_dir<<endl;
        string::size_type loc_name = headfile_full_dir.find_last_of("/");
        string head_file_name = headfile_full_dir.substr(loc_name+1);
        //cout<<head_file_name<<endl;

#ifdef HEADFILE_MULTI
        head_headdir_multimap.insert(pair<string, string>(head_file_name, headfile_dir));    
#else
        head_headdir_map[head_file_name]=headfile_dir;    
#endif

    }

    return 0;
}

#ifdef HEADFILE_MULTI
void ReplaceHeadFile::display_multimap()
{
    multimap<string,string>::iterator map_it=head_headdir_multimap.begin();  
    //cout<<"原multimap容器："<<endl; 
    while (map_it!=head_headdir_multimap.end())
    {
        cout<<map_it->first<<":";  
      
        typedef multimap<string,string>::size_type sz_type;//multimap数量类型  
        sz_type cnt=head_headdir_multimap.count(map_it->first);//返回一个键对应的值个数  
        for (sz_type i=0;i!=cnt;++map_it,++i)//循环输出各值，同时自增map_it  
        {  
            cout<<map_it->second<<" ";  
        }  
        cout<<endl;  
    }
}
#else
void ReplaceHeadFile::display_map()
{
    for(auto iter = head_headdir_map.begin(); iter != head_headdir_map.end(); ++iter) 
    {
        cout<<(*iter).first<<" "<<(*iter).second<<endl;
    }
}
#endif
int ReplaceHeadFile::compare_str_loc(string ops_file_name, string head_file_name)
{
    string::size_type loc_dir = ops_file_name.find("//");
    string file_name = ops_file_name.substr(loc_dir+2);
    //cout<<"file_name "<<file_name<<endl;
    //cout<<"head_file_name "<<head_file_name<<endl;
    int loc = 0;
    for (string::size_type i = 0; i < file_name.length(); i++)
    {
        if(i < head_file_name.length()) {
            if(file_name[i] != head_file_name[i]) {
                loc = i;
                break;
            }
        }else {
            loc = i;
            break;
        }
    }
    //cout<< "loc" <<loc<<endl;

    return loc;
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

        //cout<<"head file name:"<<head_file<<endl;
#ifdef HEADFILE_MULTI
        typedef multimap<string, string>::size_type sz_type;
        sz_type entries = head_headdir_multimap.count(head_file);
        multimap<string,string>::iterator iter = head_headdir_multimap.find(head_file);
        string headdir_name;

        if (entries == 0) {
            cout<<"ERROR:can not find dir head_file:"<<head_file<<endl;
            continue;
        }else if (entries == 1) {
           headdir_name = iter->second;
        }else{
            cout<<"multi head map:";
            string headdir_name_temp;
            int loc = 0;
            multimap<string,string>::iterator iter_most_map = iter;
            for (sz_type cnt = 0; cnt != entries; ++cnt, ++iter) {
                headdir_name_temp = iter->second;
                int loc_cur =  compare_str_loc(file_name, headdir_name_temp);
                if( loc_cur > loc) {
                    loc = loc_cur;
                    iter_most_map = iter;
                }
                cout<<headdir_name_temp<<" "<<endl;
            }
            headdir_name = iter_most_map->second;
            cout<<file_name<<" and "<<headdir_name<<" last mate"<<endl;
        }

        file.file_substitute_string(line[line_num], head_file,headdir_name);
#else
        if(head_headdir_map.count(head_file)>0)
            file.file_substitute_string(line[line_num], head_file,head_headdir_map[head_file]);
        else
            cout<<"ERROR:can not find dir head_file:"<<head_file<<endl;
#endif
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

#ifdef HEADFILE_MULTI
    //display_multimap();
#else
    //display_map();
#endif


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


