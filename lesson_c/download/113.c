// 文件：113.c
// 主题：条件运算符
// 目标：输入两个十进制整数a和b，输出“Say ”和它们中最小的值
// 实例：
//     输入：1 2
//     输出：Say 1
//     输入：2 1
//     输出：Say 1
// 要点：A?B:C，即如果A为真（非0），则整个表达式的值为B的值，否则为C的值
#include <stdio.h>
int main(void)
{
    int a,b;
    scanf("%d %d", &a, &b);
    printf("Say %d\n", a<b?a:b);
    return 0;
}
