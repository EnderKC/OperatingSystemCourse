#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "function.h"

using namespace std;

// 菜单 接收选项 执行操作
void menu(int choice,Map *user,MFD *mfd,AFD *afd){
    switch (choice)
    {
    case 1:{
        cout << "===新建文件===" << endl;
        cout << "请输入要【创建】的文件的名称" << endl;
        char fileName[20];
        cin >> fileName;
        bool fileProtect[3] = {true,true,true};
        cout << "请输入文件的长度" << endl;
        int fileLength;
        cin >> fileLength;
        if(createFile(user,fileName,fileProtect,fileLength)){
            cout<<"创建文件成功"<<endl;
        }else{
            cout<<"创建文件失败"<<endl;
        }
        break;
    }
    case 2:{
        cout << "请输入要【删除】的文件的名称" << endl;
        char fileName[20];
        cin >> fileName;
        if(deleteFile(user,fileName,afd)){
            cout<<"删除文件成功"<<endl;
        }else{
            cout<<"删除文件失败，可能是您已经打开文件，或者找不到此文件名称"<<endl;
        }
        break;
    }
    case 3:{
        cout << "请输入要【打开】的文件的名称" << endl;
        char fileName[20];
        cin >> fileName;
        bool open_file_protect[3] = {1,1,1};
        if(openFile(user,fileName,afd,open_file_protect)){
            cout << "打开文件成功！" << endl;
        }else{
            cout << "打开文件失败,可能是权限不足，或着您没有此文件！" << endl;
        }
        break;
    }
    case 4:{
        cout << "请输入要【关闭】的文件的名称" << endl;
        char fileName[20];
        cin >> fileName;
        if(closeFile(afd,fileName)){
            cout << "关闭文件成功" << endl;
        }else{
            cout << "关闭文件失败" << endl;
        }
        break;
    }
    case 5:{
        cout << "请输入要【读取】的文件的名称" << endl;
        char fileName[20];
        cin >> fileName;
        if(readFile(afd,fileName)){
            cout << "读取文件成功" << endl;
        }else{
            cout << "读取文件失败" << endl;
        } 
        break;
    }
    case 6:{
        cout << "======显示文件列表=========" << endl;
        displayUserFile(user);
    }
    case 7:{
        cout << "======显示打开文件列表=========" << endl;
        displayOpenFile(afd,user);
        break;
    }
    case 8:{
        cout << "请输入要【写入】的文件的名称" << endl;
        char fileName[20];
        cin >> fileName;
        if(writeFile(afd,fileName)){
            cout << "写入文件成功" << endl;
        }else{
            cout << "写入文件失败" << endl;
        } 
        break;
    }
    default:{
        break;
    }
    }
}


int main(int argc, char const *argv[])
{
    printf("=====BEGIN=====\n");
    // 新建主目录
    MFD *mfd = new MFD();
    // 初始化AFD已打开文件目录
    AFD *afd = createAFD();
    initUser(mfd);
    // displayUser(mfd);
    // 输入用户名
    char username[20];
    cout << "请输入用户名" << endl;
    cin >> username;
    // 查找相应用户
    Map *user = queryUser(username,mfd);
    if (!user){
        cout << "用户不存在" << endl;
        return -1;
    }
    
    while (1)
    {
        cout << "========仿-LINUX-文件管理=======" << endl;
        cout << "1. 新建文件" << endl;
        cout << "2. 删除文件" << endl;
        cout << "3. 打开文件" << endl;
        cout << "4. 关闭文件" << endl;
        cout << "5. 读出文件" << endl;
        cout << "6. 显示文件列表" << endl;
        cout << "7. 显示打开的文件列表" << endl;
        cout << "8. 写入文件" << endl;
        cout << "9. Bye~" << endl;
        cout << "找到相应用户，请输入操作：" << endl;
        int choice;
        cin >> choice;
        if(choice > 9 && choice < 1){
            cout << "输入错误";
            return -1;
        }else if (choice == 9)
        {
            break;
        }
        menu(choice,user,mfd,afd);
    }
    
    return 0;
}
