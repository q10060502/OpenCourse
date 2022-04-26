// 文件：106.c
// 主题：数据输入
// 目标：输入一个十进制整数和浮点数，输出“Say ”和它们的值
// 实例：
//     输入：1 3.14
//     输出：Say 1 3.14
// 要点：（1）输入十进制整型数据使用”%d“格式
//	 （2）输入浮点型数据使用”%f“格式
//	 （3）除使用数组、指针获取输入外，
//            其他类型变量前需要加”&“代表取地址操作
#include <stdio.h>
int main(void)
{
    int n;
    float f;
    scanf("%d %f", &n, &f);
    printf("Say %d %f\n", n, f);
    return 0;
}
