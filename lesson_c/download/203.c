// 文件：203.c
// 主题：循环结构（while）
// 目标：输入一个正整数n，输出“Say ”和空格分隔的n-1、n-2、……、0
// 实例：输入：3
//       输出：Say 2 1 0
// 要点：（1）循环体可能1次都不执行
//       （2）当while判断条件为1（即真值）时，循环永不退出，
//            此时可以使用break跳出循环
#include <stdio.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    printf("Say ");
    while(1) {
        n--;
        printf("%d ", n);
	if(n==0) break;
    }
    printf("\n");
    return 0;
}
