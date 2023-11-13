#include <stdio.h>
#include <stdlib.h>
#define MAX_ORDER 10

// 内存
typedef struct Memory
{
    // 存储数据
    int size; // 2的幂次
    Memory* link;
}Memory;

// 定义索引结构体
typedef struct MemoryIndex
{
    long index;
    Memory* link;
}MemoryIndex;

// 初始化内存索引
MemoryIndex* initMenoryIndex(){
    MemoryIndex* memoryIndex = (MemoryIndex*)malloc(MAX_ORDER*sizeof(MemoryIndex));
    for (int i = 0; i < MAX_ORDER; i++)
    {
        memoryIndex[i].index = i;
        // 添加空闲内存块
        for (int j = 0; j < 2; j++)
        {
            Memory memory;
            memory.size = i;
            
        }
        
    }
    
    return memoryIndex;
}
