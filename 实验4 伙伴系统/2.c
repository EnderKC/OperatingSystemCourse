#include <stdio.h>

// 初始化内存数组
int memory[1024] = {0};  // 定义内存数组，0表示空闲，1表示已分配

// 分配内存函数
void allocate(int size) {
    for (int i = 0; i < 1024; i++) {
        if (memory[i] == 0) {  // 找到空闲内存
            if (i + size <= 1024) {  // 检查是否有足够的空间
                for (int j = i; j < i + size; j++) {
                    memory[j] = 1;  // 分配内存
                }
                printf("已经申请 %d 这么多内存\n", size);
                return;
            } else {
                printf("没有足够内存\n");
                return;
            }
        }
    }
    printf("没有足够内存\n");
}

// 释放内存函数
void deallocate(int start, int size) {
    if (start + size <= 1024) {
        for (int i = start; i < start + size; i++) {
            memory[i] = 0;  // 释放内存
        }
        printf("已经释放了 %d 这么多内存\n", size);
    } else {
        printf("无效的开始和大小\n");
    }
}

// 显示内存状态函数
void display() {
    for (int i = 0; i < 1024; i++) {
        printf("%d", memory[i]);
    }
    printf("\n");
}

int main() {
    int choice, size, start;
    while (1) {
        printf("1. 申请内存\n2. 释放内存\n3. 展示当前内存状态\n4. 退出\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("输入申请的内存大小: ");
                scanf("%d", &size);
                allocate(size);
                break;
            case 2:
                printf("输入内存的开始位置和大小: ");
                scanf("%d %d", &start, &size);
                deallocate(start, size);
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("无效输入\n");
        }
    }
}