// 文件：110.c
// 主题：关系运算符
// 目标：输入两个十进制整数a和b，
//       如果a<b则输出“Say 1”，否则输出”Say 0“
// 实例：
//     输入：1 2
//     输出：Say 1
//     输入：2 1
//     输出：Say 0
// 要点：关系运算符组成表达式的值为真值（1）或假值（0）
#include <stdio.h>
int main(void)
{
    int a,b;
    scanf("%d %d", &a, &b);
    printf("Say %d\n", a<b);
    return 0;
}
