#include "file_operation.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

FileOperation::FileOperation(char *root_path) {

    root_path_ = NULL;
    SetRootPath(root_path);
    SearchFileList();
}

FileOperation::~FileOperation(){

    delete [] root_path_;
    root_path_ = NULL;
}

char *FileOperation::OpenFileOrFolderByName(const char *file_or_folder_name){

    if(file_or_folder_name == NULL)
        return NULL;

    //获取绝对路径
    char *file_path = new char[strlen(root_path_) + 1 + strlen(file_or_folder_name) + 1];
    strcpy(file_path, root_path_);
    strcat(file_path, "/");
    strcat(file_path, file_or_folder_name);

    //通过绝对路径打开文件或文件夹
    char *result = OpenFileOrFolderByPath(file_path);
    delete []file_path;
    return result;
}

char *FileOperation::OpenFileOrFolderByPath(const char *file_or_folder_path){

    if(file_or_folder_path == NULL)
        return NULL;

    struct stat file_info;
    stat(file_or_folder_path, &file_info);
    if(S_ISDIR(file_info.st_mode)) {
        //如果打开的是目录，那么就需要跳转到目录
        SetRootPath(file_or_folder_path);
        SearchFileList();
        return NULL;
    } else if(S_ISREG(file_info.st_mode)) {
        //打开文件
        return ReadFileByPath(file_or_folder_path);
    } else {
        cout << "打开的不是文件夹，也不是常规文件";
        return NULL;
    }
}

vector<string> FileOperation::SearchFileOrFolderByName(const char *file_or_folder_name, const char *root_path){

    DIR *dir = opendir(root_path);
    if(dir == NULL){
        cout << "打开失败" <<endl;
        return vector<string>();
    }
    vector<string> result;
    struct dirent *ptr;
    while((ptr = readdir(dir)) != NULL){ 
        string temp_foldr_path(string(root_path) + '/' + string(ptr->d_name));
        if(S_ISDIR(ptr->d_type)) {
           
            if(strcmp(ptr->d_name, file_or_folder_name) == 0)
                result.push_back(temp_foldr_path);
            //进入下一层目录进行递归
            if(strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") !=0)
                SearchFileOrFolderByName(file_or_folder_name, temp_foldr_path.c_str());
        } else  {
            if(strcmp(ptr->d_name, file_or_folder_name) == 0)
                result.push_back(temp_foldr_path);
        } 
    }
    return result;
}

bool FileOperation::ReturnPreFolder(){

    if(root_path_ == NULL || strlen(root_path_) == 1)
        return false;
    int length = strlen(root_path_);
    char *ptr = root_path_ + length;
    //字符串中如果没有'/'，防止指针越界
    while(ptr != root_path_ && *ptr != '/') ptr--; 
    *ptr = '\0';
 
    //拷贝到新的内存路径中
    char *temp = new char[strlen(root_path_) + 1];
    strcpy(temp, root_path_);
    //这里释放法内存的多少，是由new的时候标记的
    delete [] root_path_;
    root_path_ = temp;
    return SearchFileList();
}

char *FileOperation::ReadFileByPath(const char *file_path){

     if(file_path == NULL)
        return NULL;
    ifstream file(file_path);
    if(!file)
        return NULL;
    //获得文件的长度，用于申请足够的堆内存
    int file_length = 0;
    file.seekg(0, std::ios::end);
    file_length = file.tellg();
    file.seekg(0, std::ios::beg);
    char *read_content = new char[file_length];
    file.read(read_content, file_length);
    file.close();
    return read_content;
}

/*********************************************
 * FunctionName: WriteFile
 * Purpose: 把write_content写入root_path_文件
 *          夹下，指定文件名文件
 * Parameter:
 *      file_name:文件名，包含文件类型，不能为空
 *      write_content：写入文件的内容
 *      type：写入的方式，即是否覆盖原有内容
 * Return: true：成功；false：失败
**********************************************/
bool FileOperation::WriteFile(const char *file_name, const char *write_content, bool type){
    
    if(file_name == NULL)
        return false;

    string file_path(root_path_);
    file_path += "/";
    file_path.append(file_name);
    ofstream file;
    if(type == true)  //覆盖原有内容
        file.open(file_path, std::ios::ate);
    else              //不覆盖原有内容
        file.open(file_path, std::ios::app);
    if(!file) {
        cout << file_path <<endl;
        return false;
    }

    file << write_content;
    file.close();
    return true;
}

bool FileOperation::SetRootPath(const char *root_path){
    if(root_path == NULL)
        return false;

    if(root_path_ != NULL)
        delete [] root_path_;
    root_path_ = new char[strlen(root_path) + 1];
    strcpy(root_path_, root_path);
    return true;
} 

void FileOperation::CopyFile(const char *src_path, const char *dst_path){


}

void FileOperation::DeleteFile(const char *file_name){


}

void FileOperation::CutFile(const char *src_path, const char *dst_path){


}

bool FileOperation::SearchFileList(){

    if(!file_list_.empty())
        file_list_.clear();
    if(root_path_ == NULL)
        cout << "根文件路径为空" << endl; 
    DIR *dir = opendir(root_path_); //不需要delete会出错 
    
    if(dir == NULL){
        return false;
    }
    struct dirent *ptr; //不需要delete会出错
    while((ptr = readdir(dir)) != NULL){

        file_list_.push_back(ptr->d_name);
    }
    closedir(dir);
    return true;
}
