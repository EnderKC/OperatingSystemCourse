#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "function.h"
using namespace std;
// 初始化用户
/*
    创建10个用户以及用户与文件的映射
    用户名为 0-9
*/
void initUser(MFD *mfd){
    // 创建第一个头部用户
    Map* user = new Map();
    strcpy(user->userName,"0");
    user->file = NULL;
    user->next = NULL;
    // 连接主目录与第一个用户
    mfd->head = user;
    mfd->tail = user;
    for (int i = 1; i < 10; i++)
    {
        Map* userNew = new Map();
        // 把用户的名字取为 i 这个数字
        snprintf(userNew->userName,sizeof(userNew->userName),"%d",i);
        userNew->file = NULL;
        userNew->next = NULL;
        // 将新用户连接到链表的结尾
        mfd->tail->next = userNew;
        mfd->tail = userNew;
    }
}

/* 
    进行系统用户的输出
*/
void displayUser(MFD *mfd){
    // 遍历链表
    printf("遍历用户列表(数字就是用户名)\n");
    Map *thisUser = mfd->head;
    while (thisUser != mfd->tail->next)
    {
        printf("%s\n",thisUser->userName);
        thisUser = thisUser->next;
    }
    printf("系统用户遍历完成!\n");
}

/* 
    进行用户的查找，找到则返回用户映射指针
    如果没有找到就返回空指针
*/
Map* queryUser(char userName[] , MFD *mfd){
    Map *thisUser = mfd->head;
    while(thisUser != mfd->tail->next){
        if(strcmp(thisUser->userName,userName) == 0){
            return thisUser;
        }
        thisUser = thisUser->next;
    }
    return NULL;
}

/*  
    进行文件的创建操作 *成功则返回true ， 否则返回false
*/
bool createFile(Map *user , char file_name[] , bool file_protect[3] , int file_length){
    // 查询用户拥有的文件数量是否大于最大数量
    int fileCount = 0;
    File *thisFile = user->file;
    while (thisFile != NULL)
    {
        // 查找有没有同名的文件，如果有，则返回false
        if(strcmp(thisFile->file_name,file_name) == 0){
            return false;
        }
        fileCount += 1;
        thisFile = thisFile->next;
    }
    if(fileCount > userMaxFile){
        return false;
    }
    // 创建新的文件
    File* fileTmp = new File();
    if(user->file != NULL){
        fileTmp->next = user->file;
    }else{
        fileTmp->next = NULL;
    }
    user->file = fileTmp;
    
    strcpy(user->file->file_name,file_name);
    for (int i = 0; i < 3; i++)
    {
        user->file->file_protect[i] = file_protect[i];
    }
    user->file->file_length = file_length;
    user->file->read = 0;
    user->file->write = 0;
    return true;
}

/*
    进行文件删除操作
*/
bool deleteFile(Map* user, char file_name[], AFD* afd) {
    // 查看文件有没有已经打开
    File* openFile = afd->head;
    while (openFile != NULL) {
        if (strcmp(openFile->file_name, file_name) == 0) {
            cout << "文件已经打开！" << endl;
            return false;
        }
        openFile = openFile->next;
    }

    // 文件的删除操作
    File* thisFile = user->file;
    File* prevFile = NULL;

    // 寻找要删除的节点
    while (thisFile != NULL && strcmp(thisFile->file_name, file_name) != 0) {
        prevFile = thisFile;
        thisFile = thisFile->next;
    }

    // 如果找到了要删除的节点
    if (thisFile != NULL) {
        // 如果要删除的节点是第一个节点
        if (prevFile == NULL) {
            user->file = thisFile->next;
        } else {
            prevFile->next = thisFile->next;
        }

        delete thisFile;
        return true;
    }

    cout << "文件没有找到!" << endl;
    return false;
}



/*
    进行文件打开操作
*/
// 创建AFD已打开文件目录
AFD* createAFD(){
    AFD *afd = new AFD();
    afd->head = NULL;
    afd->tail = NULL;
    afd->max_open = MaxOpenFile;
    afd->current_open = 0;
    return afd;
}

// 深拷贝函数
File* deep_copy_file(const File* original) {
    if (original == NULL) {
        return NULL;  // 处理空指针情况
    }

    File* new_file = (File*)malloc(sizeof(File));
    if (new_file == NULL) {
        return NULL;  // 内存分配失败
    }

    // 拷贝结构体成员
    strcpy(new_file->file_name, original->file_name);
    memcpy(new_file->file_protect, original->file_protect, sizeof(original->file_protect));
    memcpy(new_file->open_file_protect, original->open_file_protect, sizeof(original->open_file_protect));
    new_file->read = original->read;
    new_file->write = original->write;
    new_file->file_length = original->file_length;

    // 递归深拷贝下一个结点
    new_file->next = NULL;

    return new_file;
}

bool openFile(Map *user , char file_name[] , AFD *afd , bool open_file_protect[]){
    File *thisFile = user->file;
    while (thisFile != NULL)
    {
        if(strcmp(thisFile->file_name,file_name) == 0){
            // 查看文件是否已经打开
            File *isOpenFile = afd->head;
            while (isOpenFile != NULL)
            {
                if(strcmp(isOpenFile->file_name,file_name) == 0){
                      return false;
                }
                isOpenFile = isOpenFile->next;
            }
            // 添加文件到已打开文件目录
            if(++afd->current_open > afd->max_open){
                // 如果已打开的文件数量大于最大打开数量，则减去刚刚加的数字
                afd--;
                return false;
            }
            // 对文件进行深拷贝，不用影响到以后的文件遍历
            File *newFile = deep_copy_file(thisFile);
            if(afd->tail == NULL){
                afd->head = newFile;
            }else{
                afd->tail->next = newFile;
            }
            afd->tail = newFile;
            // 设置打开文件的权限
            for (int i = 0; i < 3; i++)
            {
                thisFile->open_file_protect[i] = open_file_protect[i];
            }
            return true;
        }
        thisFile = thisFile->next;
    }
    return false;
}

/*
    进行文件读操作
*/
bool readFile(AFD *afd , char file_name[]){
    // 找到相应文件（遍历ADF目录，找到相应文件）
    File *thisFile = afd->head;
    while (thisFile != NULL)
    {
        // 比对文件的名称
        if(strcmp(thisFile->file_name,file_name) == 0){
            // 文件读取成功
            return true;
        }
        thisFile = thisFile->next;
    }
    return false;
}

/*
    进行文件的写操作
*/
bool writeFile(AFD *afd , char file_name[]){
    // 找到相应文件（遍历ADF目录，找到相应文件）
    File *thisFile = afd->head;
    while (thisFile != NULL)
    {
        // 比对文件的名称
        if(strcmp(thisFile->file_name,file_name) == 0){
            // 文件写入成功
            return true;
        }
        thisFile = thisFile->next;
    }
    return false;
}

/* 进行用户文件的显示 */
void displayUserFile(Map *user){
    // 遍历用户文件的链表
    File *thisFile = user->file;
    while (thisFile != NULL)
    {
        cout << "文件名："<< thisFile->file_name << endl;
        cout << "文件大小" << thisFile->file_length << endl;
        cout << "============" << endl;
        thisFile = thisFile->next;
    }
}

/*
    显示打开的文件
*/
void displayOpenFile(AFD *afd , Map *user){
    File *thisFile = user->file;
    while(thisFile != NULL){
        File *openFile = afd->tail;
        while (openFile != NULL)
        {
            if(strcmp(thisFile->file_name,openFile->file_name) == 0){
                cout << "文件名："<< thisFile->file_name << endl;
                cout << "文件大小" << thisFile->file_length << endl;
                cout << "============";
            }
            openFile = openFile->next;
        }
        thisFile = thisFile->next;
    }
}

/*
    关闭文件
*/
bool closeFile(AFD *afd , char file_name[]){
    File *thisFile = afd->head;
    File *prevFile = NULL;
    // 找到相应文件
    while (thisFile != NULL && strcmp(thisFile->file_name,file_name) != 0)
    {
        prevFile = thisFile;
        thisFile = thisFile->next;
    }
    // 对找到的文件进行操作
    if(thisFile != NULL){
        // 如果删除的节点是第一个节点
        if(prevFile == NULL){
            afd->head = thisFile->next;
        }else{
            prevFile->next = thisFile->next;
        }
        if(strcmp(afd->tail->file_name,file_name) == 0){
            afd->tail = prevFile;
        }
        delete thisFile;
        return true;
    }
    return false;
}
