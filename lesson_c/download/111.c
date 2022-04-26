// 文件：111.c
// 主题：逻辑运算符
// 目标：输入一个十进制整数a，
//       如果a和0之前的差小于4，则输出“Say 1”，否则输出”Say 0“
// 实例：
//     输入：3
//     输出：Say 1
//     输入：-3
//     输出：Say 1
//     输入：4
//     输出：Say 0
// 要点：零值为逻辑假，非零为逻辑真
#include <stdio.h>
int main(void)
{
    int a;
    scanf("%d", &a);
    printf("Say %d\n", a>-4&&a<4);
    return 0;
}
