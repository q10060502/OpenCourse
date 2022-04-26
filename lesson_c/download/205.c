// 文件：205.c
// 主题：循环结构（for）
// 目标：输入一个正整数n，输出“Say ”和空格分隔的n-1、n-2、……、0
// 实例：
//     输入：3
//     输出：Say 2 1 0
// 要点：迭代变量初值、变化和终止条件写在for后的括号里
#include <stdio.h>
int main(void)
{
    int n, i;
    scanf("%d", &n);
    printf("Say ");
    for(i=n-1;i>=0;i--) {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
