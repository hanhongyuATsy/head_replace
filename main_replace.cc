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

using namespace std;  

int  print_file_info(char *pathname);  
static int  read_dir(char *pathname);  
#define MAX_PATH 512  

vector<string> proj_name;
map<string, string> head_dir_map; 

#define EXTEN_NAME_MAX 8
#define HEAD_NAME_MAX 30

static int  get_exten_name(const char * pathname, char *exten_name)
{
    int i = 1,length;  
    //char exten_name[EXTEN_NAME_MAX];

    if( pathname == NULL) {
        return -1;
    }

    length=strlen(pathname);  

    while(i < length)  
    {  
        if (i > EXTEN_NAME_MAX) {
            printf(" i == %d;  exten name overlenth %s \n", i, pathname);
            return -1;
        }

        if(pathname[length - i]=='.')  
        {
            strncpy(exten_name, pathname + (length - i), (i + 1));
            break;  
        }

        i++;  
    }  


    return 0;
}

static int get_head_name(const char * pathname, char * head_name)
{
    int i = 1,length;  

    if( pathname == NULL) {
        return -1;
    }

    length=strlen(pathname);  

    while(i < length)  
    {  
        if (i > HEAD_NAME_MAX) {
            printf(" i == %d  exten headname overlenth %s\n",i , pathname);
            return -1;
        }

        if(pathname[length - i] == '/')  
        {
            strncpy(head_name, pathname + (length - i), (i + 1));
            cout << "head_name" << head_name <<endl;
            break;  
        }

        i++;  
    }

    return 0;

}

static int is_cpp_file(const char *exten_name )
{

   // printf("%s\n", exten_name);
    if ( (strcmp (exten_name , ".cc") == 0) || (strcmp (exten_name , ".cpp") == 0)
             || (strcmp (exten_name , ".hpp") == 0))  {
        return 1;
    }
    return 0;
}

static int is_head_file(const char *exten_name)
{
    if ( strcmp (exten_name , ".h") == 0)  {
        return 1;
    }
    return 0;
}


static int read_dir(char *pathname)
{
    //int fd = opendir(dir_proj,r);
	DIR				*dfd;
	struct dirent	*dp;
    char name[MAX_PATH];  

    dfd = opendir(pathname);
	if (dfd == NULL)
		printf("can't open %s", pathname); 

	while ((dp = readdir(dfd)) != NULL) {
        if (strncmp(dp->d_name, ".", 1) == 0)  
            continue; /* 跳过当前目录和上一层目录以及隐藏文件*/  
        if (strlen(pathname) + strlen(dp->d_name) + 2 > sizeof(name))  
        {  
            printf("read_dir: name %s %s too long\n", pathname, dp->d_name);  
        }
        else  
        {  
            memset(name, 0, sizeof(name));  
            sprintf(name, "%s/%s", pathname, dp->d_name);  
            print_file_info(name);  
        }  
    }  

	closedir(dfd);

    return 0;
}

int print_file_info(char *pathname)  
{  
    struct stat filestat;  
    if (stat(pathname, &filestat) == -1)  
    {  
        printf("cannot access the file %s", pathname);  
        return -1;  
    }  
    if ((filestat.st_mode & S_IFMT) == S_IFDIR) //判断是一个路径  
    {  
        read_dir(pathname);  
    } 
    else if ((filestat.st_mode & S_IFMT) == S_IFREG) // 判断是一个文件
    {
        char exten_name[EXTEN_NAME_MAX];
        get_exten_name(pathname, exten_name);

        if (is_cpp_file(exten_name) == 1) {
            proj_name.push_back(pathname);
        } 

        if (is_head_file(exten_name) == 1) {
            char head_name[HEAD_NAME_MAX];
            proj_name.push_back(pathname);
            get_head_name(pathname, head_name);
            head_dir_map[head_name] = pathname;
        } 
    }

    //printf("%s %8ld\n", pathname, filestat.st_size);  

    return 0;
}  


int get_head_name_map(const char file_name, set<string> head_name)
{
    std::cout << "###get_head_name_map####" <<std::endl;
    //open(file);
    //getline();
    //if(head == "#include")
    //{            
    //    head_dir.add(head);
    //}

    return 0;
}

int find_head_dir(set<string> head_name, map<string, string> head_dir)
{
    std::cout << "###find_head_dir####" <<std::endl;

    return 0;
}

int replace_head_str(void)
{
    std::cout << "###find_head_dir####" <<std::endl;
}

#if 0

int read_file(int fd, vector<string> &file_vec)
{
    return 0;
}

int get_head_str(string line_str, string head_name)
{
    return 0;
}

int get_include_line(vector<string> &file_vec, map<int,string> &head_line_map)
{
    return 0;
}

int replace_str(map<int, string> &head_line_map, map<string, string> &head_dir_map, map<int, string> &line_headdir_map)
{
    return 0;
}

int replace_file(vector<string> &file_vec, map<int, string> &line_headdir_map)
{
    return 0;
}
int write_file(int fd, vector<string> &file_vec)
{
    return 0;

}
#endif




int main(int argc, char *argv[])
{
    std::cout << "main "<< endl;

	if (argc != 2) {
		printf("usage: ls directory_name");
        return 0;
    }

    read_dir(argv[1]);
    

    for(auto iter = proj_name.begin(); iter != proj_name.end(); ++iter) 
    {
        cout<< (*iter) <<endl;
    }

    for(auto iter = head_dir_map.begin(); iter != head_dir_map.end(); ++iter) 
    {
        cout<< (*iter).first <<endl;
        cout<< (*iter).second <<endl;
    }

    return 0;
}



