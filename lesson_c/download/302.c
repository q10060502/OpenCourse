// 文件：302.c
// 主题：二维数组
// 目标：初始化3行4列数组，输出“Say ”和其所点内存空间字节数
// 要点：二维数组的声明、赋于初值、内存大小
#include <stdio.h>
int main(void)
{
    int a[3][4] = {{1,2},{3,4,5,6},{7,8}};
    printf("Say %d\n", sizeof(int)*3*2);
    //printf("Say %d\n", sizeof(a));
    return 0;
}
