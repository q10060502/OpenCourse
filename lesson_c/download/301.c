// 文件：301.c
// 主题：一维数组
// 目标：循环输入3个整数并存入已初始化为{1,2,3,4}的数组，
//       循环输出“Say ”和空格分隔的3个整数
// 实例：
//     输入：10 20 30
//     输出：Say 10 20 30 4
// 要点：一维数组的声明、赋于初值、内存大小、使用和遍历
#include <stdio.h>
int main(void)
{
    int a[] = {1,2,3,4};
    for(i=0;i<3;i++) {
        scanf("%d", &a[i]);
    }
    printf("Say ");
    for(i=0;i<sizeof(a)/sizeof(int);i++) {
        printf("%d", a[i]);
    }
    printf("\n");
    return 0;
}
