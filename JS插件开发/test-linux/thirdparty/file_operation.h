#ifndef FILE_OPERATION_H_
#define FILE_OPERATION_H_

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class FileOperation{

public:
    FileOperation(char *root_path);
    ~FileOperation();



    bool SetRootPath(const char *root_path);  
    vector<string> GetFileList() { return file_list_; }
    char *GetRootPath() { return root_path_; } 

    char *OpenFileOrFolderByName(const char *file_or_folder_name);
    char *OpenFileOrFolderByPath(const char *file_or_folder_path); 
    vector<string> SearchFileOrFolderByName(const char *file_or_folder_name, const char *root_path);
    bool ReturnPreFolder();

    //读写所操作的文件，都在当前文件夹下
    char *ReadFileByPath(const char *file_path);
    bool WriteFile(const char *file_name, const char *write_content, bool type);
   
    //复制和剪切为拷贝到当前文件夹下
    void CopyFile(const char *src_path, const char *dst_path);
    void CutFile(const char *src_path, const char *dst_path);
    void DeleteFile(const char *file_name);

private:
    bool SearchFileList();                  //搜索路径下文件名
    char *root_path_;                       //当前文件夹绝对路径
    vector<string> file_list_;              //当前文件夹目录文件名
};



#endif