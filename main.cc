
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

using namespace std;  
int main(int argc, char *argv[])
{

	if (argc != 2) {
		printf("usage: ls directory_name \n");
        return 0;
    }

    ListFile proj_root(argv[1]);

    //vector<string> file_name_list = proj_root.get_all_fliename();
    vector<string> file_name_list = proj_root.get_head_fliename();
    cout << "file num == "<< file_name_list.size() << endl;

    for(auto iter = file_name_list.begin(); iter != file_name_list.end(); ++iter) 
    {
        cout<< (*iter) <<endl;
    }

    return 0;
}
