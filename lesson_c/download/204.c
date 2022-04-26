// 文件：204.c
// 主题：循环结构（do...while）
// 目标：输入一个正整数n，输出“Say ”和空格分隔的n-1、n-2、……、0
// 实例：
//     输入：3
//     输出：Say 2 1 0
// 要点：循环体至少执行1次
#include <stdio.h>
int main(void)
{
    int n, i;
    scanf("%d", &n);
    printf("Say ");
    do{
        n--;
        printf("%d ", n);
    } while(n>0);
    printf("\n");
    return 0;
}
