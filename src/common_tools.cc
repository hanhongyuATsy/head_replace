#include<iostream>  
#include<string>  
#include<vector>
#include <dirent.h>

#include<stdio.h>  
#include <dirent.h>  
#include <sys/types.h>
#include<string.h>  

#include "common_tools.h"
#define MAX_PATH 500

using namespace std;  

enum file_type ListFile::analyse_file_types(const char *file_name)
{
    struct stat filestat;  

    if(file_name == NULL) {
        printf("input file is NULL!!!\n");
        return unknow_file;
    }

    if (stat(file_name, &filestat) == -1) {  
        printf("cannot access the file %s", file_name);  
        return unknow_file;  
    }  

    if ((filestat.st_mode & S_IFMT) == S_IFDIR)   
        return dir_file;  
    else if ((filestat.st_mode & S_IFMT) == S_IFREG)
        return text_file;  


    return unknow_file;  
}

int ListFile::traverse_dir(const char * dir_name)
{
	DIR				*dfd;
	struct dirent	*dp;
    char name[MAX_PATH];  

    if(dir_name == NULL) {
        printf("input dir is NULL!!!\n");
        return -1;
    }

    dfd = opendir(dir_name);
	if (dfd == NULL)
		printf("can't open %s", dir_name); 

	while ((dp = readdir(dfd)) != NULL) {
        if (strncmp(dp->d_name, ".", 1) == 0)  
            continue;
        if (strlen(dir_name) + strlen(dp->d_name) + 2 > sizeof(name))  {  
            printf("read_dir: name %s %s too long\n", dir_name, dp->d_name);  
            continue;
        }

        memset(name, 0, sizeof(name));  
        sprintf(name, "%s/%s", dir_name, dp->d_name);  

        enum file_type type = analyse_file_types(name);
        if(type == dir_file) {
            traverse_dir(name);
        }else if(type == text_file) {
            all_file_name.push_back(name);
            analyse_exten_name_types(name);
        }
    }


    return 0;
}

int ListFile::analyse_exten_name_types(string file_name) 
{
    int local = file_name.find_last_of(".");  

    if(local < 0) {
        printf("can not find exten_name at %s\n",file_name.c_str());
        return -1;
    }
    string exten_name = file_name.substr(local); 
    //cout << exten_name << endl;

    if ((exten_name.compare(".cc") == 0) || (exten_name.compare(".cpp") == 0) 
            ||(exten_name.compare(".c") == 0) || (exten_name.compare(".hpp") == 0) ) 
    {
        cpp_file_name.push_back(file_name);
    } 
    else if (exten_name.compare(".h") == 0)
    {
        head_file_name.push_back(file_name);
    }



    return 0;
}

ListFile::ListFile(const char * dir_name)
{
    int ret = traverse_dir(dir_name);
    if(ret < 0) {
        printf("create ListFile faile!!\n");
    }
}

ListFile::~ListFile()
{
}

const vector<string> & ListFile::get_all_fliename()
{
    return all_file_name;
}

const vector<string> & ListFile::get_cpp_fliename()
{
    return cpp_file_name;
}

const vector<string> & ListFile::get_head_fliename()
{
    return head_file_name;
}

int ListFile::get_all_file_count()
{
    return all_file_name.size();
}
int ListFile::get_cpp_file_count()
{
    return cpp_file_name.size();
}
int ListFile::get_head_file_count()
{
    return head_file_name.size();
}



