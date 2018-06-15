#ifndef _REPLACE_HEADFILE_H_
#define _REPLACE_HEADFILE_H_





class ReplaceHeadFile {
    public:
        int build_head_dir_map(vector<string> *head_file);
        int replace_head_to_headdir(const char *file_name);
        void display_map();
    prvate:
        map<string, string> head_headdir_map;

}



#endif
