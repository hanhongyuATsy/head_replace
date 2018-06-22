
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

#include"common_tools.h"
#include"text_query.h"
#include"replace_headfile.h"

using namespace std;  
int main(int argc, char *argv[])
{

	if (argc < 2) {
		printf("usage: ls directory_name \n");
        return 0;
    }
#if 0
/*
 *for replace headfile to dir+headfile
 *eg. "xxx.h" to "yyy/xxx.h"
 *
 */

    ReplaceHeadFile dprice(argv[1]);
    int cnt = dprice.run();
    printf("cnt == %d\n", cnt);
#endif

#if 1
/* for caculate file nums
 * for caculate file coding format
 * for caculate file lines
 */

    ListFile proj_root(argv[1]);
    TextQuery text_test;

    //vector<string> file_name_list = proj_root.get_all_fliename();
    vector<string> cpp_name_list = proj_root.get_head_fliename();
    vector<string> head_name_list = proj_root.get_cpp_fliename();
    //cout << "file num == "<< file_name_list.size() << endl;

    printf("file count %d\n", proj_root.get_all_file_count());
    unsigned long lines = 0;
    
    for(auto iter = cpp_name_list.begin(); iter != cpp_name_list.end(); ++iter) 
    {
      text_test.get_coding_format((*iter).c_str());
      //cout<< (*iter) <<endl;
      //text_test.read_file((*iter).c_str());
      //lines += text_test.get_file_lines();

    }

    for(auto iter = head_name_list.begin(); iter != head_name_list.end(); ++iter) 
    {
      text_test.get_coding_format((*iter).c_str());
      //text_test.read_file((*iter).c_str());
      //lines += text_test.get_file_lines();
      //  cout<< (*iter) <<endl;
    }

    //printf("lines %ld\n", lines);

#endif


    return 0;
}
