// 文件：115.c
// 主题：移位运算符
// 目标：使用移位运算符输出“Say ”和3*16的值
//       使用移位运算符输出“Say ”和1024/16的值
// 实例：输出：Say 48
//             Say 64
// 要点：左移N位相当于乘以2的N次幂、右移N位相当于除以2的N次幂
#include <stdio.h>
int main(void)
{
    printf("Say %d\n", 3<<4);
    printf("Say %d\n", 1024>>4);
    return 0;
}
