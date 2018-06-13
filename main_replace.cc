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

using namespace std;  

int  print_file_info(char *pathname);  
static int  read_dir(char *pathname);  
#define MAX_PATH 512  

vector<string> proj_name;
//multimap<string, string> head_dir_map; 
map<string, string> head_dir_map; 

#define EXTEN_NAME_MAX 8
#define HEAD_NAME_MAX 40
#define PROJDIR_NAME_MAX 200

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

static int get_head_projdir_name(const char * pathname, char * head_name, char * projdir_name)
{
    int i = 0,length;  

    if( pathname == NULL) {
        return -1;
    }

    length=strlen(pathname);  

    while(i < length)  
    {  
        if (i > HEAD_NAME_MAX) 
        {
            printf(" i == %d  exten headname overlenth %s\n",i , pathname);
            return -1;
        }

        if (pathname[length - i] == '/')   
        {
            strncpy(head_name, pathname + (length - i + 1), i);
            //cout << "head_name  " << head_name <<endl;
            break;  
        }

        i++;  
    }

    int j = i;

    while(j < length) 
    {  
        if (j > PROJDIR_NAME_MAX) 
        {
            printf(" j == %d  exten headname overlenth %s\n",j , pathname);
            return -1;
        }

        if (pathname[length - j] == '/')   
        {
            if (pathname[length - j - 1] == '/')   
            {
                strncpy(projdir_name, pathname + (length - j), j + 1); // add 1 for "\0"
                //cout << "projdir_name" << projdir_name <<endl;
                break;  
            }
        }

        j++;

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
            char projdir_name[PROJDIR_NAME_MAX];
            proj_name.push_back(pathname);
            get_head_projdir_name(pathname, head_name, projdir_name);
            head_dir_map[head_name] = projdir_name;
        } 
    }

    //printf("%s %8ld\n", pathname, filestat.st_size);  

    return 0;
}  



#if 1

vector<std::string> lines_of_text;

ifstream& open_file(ifstream &in, const string &file)
{
    in.close();  // close in case it was already open
    in.clear();  // clear any existing errors
    lines_of_text.clear();


    // if the open fails, the stream will be in an invalid state
    in.open(file.c_str()); // open the file we were given

    return in; // condition state is good if open succeeded
}

void store_file(ifstream &is)
{
    string textline;
    while (getline(is, textline))
       lines_of_text.push_back(textline);
}

int read_file(const char * file_name)
{
    ifstream infile;
    if (!open_file(infile, file_name)) {
        cerr << "No input file!" << endl;
        return EXIT_FAILURE;
    }

    store_file(infile);
    
    return 0;
}


int get_include_line(map<int,string> &head_line_map)
{

    //for(auto iter = lines_of_text.begin(); iter != lines_of_text.end(); ++iter) 
    for(int i = 0; i < lines_of_text.size(); i++)
    {
        if (lines_of_text[i].find("#include") == 0)
        { 
            int local_start = lines_of_text[i].find_first_of("\"");
            //cout << local_start << endl;
            if (local_start > 0) {
                string temp_str1 = lines_of_text[i].substr(local_start + 1);
                //cout << temp_str1 << endl;
                int local_end = temp_str1.find_first_of("\"");
                string temp_str2 = temp_str1.substr(0, local_end);
                //cout << temp_str2 << endl;
                //cout << "line= " << i << endl;
                head_line_map[i] = temp_str2;
                    
            }
        }
    }
    
    return 0;
}

int replace_str(map<int, string> &head_line_map, map<int, string> &line_headdir_map)
{
    for(auto iter = head_line_map.begin(); iter != head_line_map.end(); ++iter) 
    {
        string head_name ((*iter).second) ;
        auto iter_head_dir_map = head_dir_map.find(head_name);
        //if(iter_head_dir_map )
        
        line_headdir_map [(*iter).first] = (*iter_head_dir_map).second; 

        //cout << (*iter_head_dir_map).second << endl;
    }

    return 0;
}

int write_file()
{
    for(auto iter = lines_of_text.begin(); iter != lines_of_text.end(); ++iter) { 

        cout << (*iter)<< endl;
    }
    //for(int i = 0; i < lines_of_text.size(); i++)
    //    cout << lines_of_text[i] << endl;

    return 0;
}

int replace_file(map<int, string> &line_headdir_map)
{

    if (line_headdir_map.empty()) {
        return 0;         
    } else {
        for(auto iter = line_headdir_map.begin(); iter != line_headdir_map.end(); ++iter) { 
            //cout << (*iter).first<< endl;
            //cout << (*iter).second << endl;
            string temp_include("#include");
            string temp_str(temp_include + ' ' + '\"' + (*iter).second + '\"'); 
            cout << temp_str << endl;
            lines_of_text[(*iter).first] = temp_str;
        }

        write_file();
    }
    return 0;
}

#endif

#if 0
int main(int argc, char *argv[])
{
    map<int,string> head_line_map;

	if (argc != 2) {
		printf("usage: ls directory_name");
        return 0;
    }

    read_file(argv[1]);
    get_include_line(head_line_map);


    for(auto iter = head_line_map.begin(); iter != head_line_map.end(); ++iter) 
    {
        cout<< (*iter).first <<endl;
        cout<< (*iter).second <<endl;
    }

    /*
    for(auto iter = lines_of_text.begin(); iter != lines_of_text.end(); ++iter) 
    {
        cout<< (*iter) <<endl;
    }
    */

    return 0;
}
#endif

#if 1
int main(int argc, char *argv[])
{
    std::cout << "main "<< endl;

	if (argc != 2) {
		printf("usage: ls directory_name");
        return 0;
    }

    read_dir(argv[1]);
    

    map<int,string> head_line_map;
    map<int, string> line_headdir_map;

    for(auto iter = proj_name.begin(); iter != proj_name.end(); ++iter) 
    {
        
        read_file((*iter).c_str());
        get_include_line(head_line_map);

        replace_str(head_line_map, line_headdir_map);
        replace_file(line_headdir_map);

        //for(auto iter_head = line_headdir_map.begin(); iter_head != line_headdir_map.end(); ++iter_head) 
        //{
        //    cout<< (*iter_head).first <<endl;
        //    cout<< (*iter_head).second <<endl;

        //}

        //for(auto iter_head = head_line_map.begin(); iter_head != head_line_map.end(); ++iter_head) 
        //{
        //    //cout<< (*iter_head).first <<endl;
        //    //cout<< (*iter_head).second <<endl;
        //}

        //cout<< (*iter) <<endl;
    }
/*
    for(auto iter = head_dir_map.begin(); iter != head_dir_map.end(); ++iter) 
    {
        cout<< (*iter).first <<endl;
        cout<< (*iter).second <<endl;
    }
    */

    return 0;
}

#endif


