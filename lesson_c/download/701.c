// 文件：701.c
// 主题：宏
// 目标：编写宏求两数最大值，
//       输入两个十进制整数a和b，
//       输出“Say ”和10加它们中最大的值
// 实例：
//     输入：1 2
//     输出：Say 1
//          Say 12
// 要点：宏的简单替换导致的副作用
#include <stdio.h>
#define MAX1(x,y)  (x)>(y)?(x):(y)
#define MAX2(x,y)  ((x)>(y)?(x):(y))
int main(void)
{
    int a,b;
    scanf("%d %d", &a, &b);
    printf("Say %d\n", 10+MAX1(a,b));
    printf("Say %d\n", 10+MAX2(a,b));
    return 0;
}
