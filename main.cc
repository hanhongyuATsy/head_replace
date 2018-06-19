
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

	if (argc != 2) {
		printf("usage: ls directory_name \n");
        return 0;
    }
#if 0
    ReplaceHeadFile dprice(argv[1]);
    int cnt = dprice.run();
    printf("cnt == %d\n", cnt);
#endif


#if 1
    ListFile proj_root(argv[1]);
    TextQuery text_test;
    //ReplaceHeadFile dprice;


    //vector<string> file_name_list = proj_root.get_all_fliename();
    vector<string> cpp_name_list = proj_root.get_head_fliename();
    vector<string> head_name_list = proj_root.get_cpp_fliename();
    //cout << "file num == "<< file_name_list.size() << endl;
    //dprice.build_head_dir_map(file_name_list);
    //dprice.display_map();

    
    for(auto iter = cpp_name_list.begin(); iter != cpp_name_list.end(); ++iter) 
    {
      text_test.get_coding_format((*iter).c_str());
      //  cout<< (*iter) <<endl;
    }

    for(auto iter = head_name_list.begin(); iter != head_name_list.end(); ++iter) 
    {
      text_test.get_coding_format((*iter).c_str());
      //  cout<< (*iter) <<endl;
    }

#endif

#if 1
    //TextQuery text_test;
   // ReplaceHeadFile price;

    //text_test.get_coding_format(argv[1]);
    //vector<TextQuery::line_no> line  = text_test.query_str_location("#include", "\"");
    //text_test.file_substitute_string("test/xxx", "hehe"); 

    //for (TextQuery::line_no line_num = 0; line_num != line.size(); ++line_num)
    //{
    //    cout<< text_test.get_line_text(line[line_num]) << endl;
    //    string head_name = price.find_head_name(text_test.get_line_text(line[line_num]));
    //}
#endif

    return 0;
}
