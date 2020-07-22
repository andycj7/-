#include <stdio.h>
#include <stdlib.h>
#include <file_operation.h>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
	if(argc < 2){
	//main.exe <root_path>
		printf("Usage: %s <root_path>", argv[0], argc);
		return 1;
	}
	FileOperation file(argv[1]);
	vector<string> file_list = file.GetFileList();
	if(file_list.size() == 0)
		cout << "读取失败" << endl;
	cout << "文件夹内容："<<endl;
	for(size_t i = 0; i < file_list.size(); i++){

		cout << file_list[i] << endl;
	}
	string filename = "";
	string operation = "";
	char *content = NULL;
	while(1) {

		cout << "输入：";
		cin >> filename;
		if(filename.empty())
			cout << "文件名为空" << endl;
		
		if(filename == "Return"){
			file.ReturnPreFolder();
			file_list = file.GetFileList();
			for(size_t i = 0; i < file_list.size(); i++)
				cout << file_list[i] << endl;

		} else if(filename == "write"){

			string file_name = "";
			string content = "";
			string type = "";
			cout << "文件名：";
			cin >> file_name;
			cout << "写入内容：";
			cin >> content;
			cout << "是否覆盖";
			cin >> type;

			if(type == "是")
				file.WriteFile(file_name.c_str(), content.c_str(), true);
			else
				file.WriteFile(file_name.c_str(), content.c_str(), false);
	 	} else if(filename == "search"){
			 string search_file_name;
			 cout << "搜索文件名：" << endl;
			 cin >> search_file_name;
			 cout << "结果：" << endl;
			 vector<string> result = file.SearchFileOrFolderByName(search_file_name.c_str(), file.GetRootPath());
			 for(size_t i = 0; i < result.size(); i++){
				 cout << result[i] <<endl;
			 }
		} else {
			content = file.OpenFileOrFolderByName(filename.c_str());
			cout << "打开" << filename << endl;
			if(content== NULL){
				cout << "文件夹内容：" << endl;
				file_list = file.GetFileList();
				for(size_t i = 0; i < file_list.size(); i++)
					cout << file_list[i] << endl;
			} else {
				cout << "文件内容："<< endl << content <<endl;
				delete [] content;
			}
		}
		
		cout << endl;
		filename.clear();
	}
	
	return 0;
}