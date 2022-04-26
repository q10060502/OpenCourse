// 文件：108.c
// 主题: 自增自减运算符
// 目标: 输入一个十进制整数，使用自增自减运算符，
//       分别输出“Say ”和它的值后加1、”Say “和它先加1后的值
// 实例：
//     输入：1
//     输出：Say 1
//           Say 3
// 要点：前缀先加（减）1、后缀后加（减）1
#include <stdio.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    printf("Say %d\n", n++);
    //printf("Say %d\n", n++); ---> printf("Say %d\n", n);n++;
    printf("Say %d\n", ++n);
    //printf("Say %d\n", ++n); ---> ++n;printf("Say %d\n", n);
    return 0;
}
