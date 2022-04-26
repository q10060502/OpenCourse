// 文件：401.c
// 主题：函数
// 目标：定义全局变量a并赋值0，
//       编写函数f，并在函数内部定义变量a并赋值1
//       函数f输出“Say ”和变量a
//       函数main调用函数f后输出“Say ”和变量a
// 要点：函数内部局部变量和全局变量重名，则屏蔽全局变量
#include <stdio.h>
int a = 0;
void f()
{
    int a = 1;
    printf("Say %d\n", a);
}
int main(void)
{
    f();
    printf("Say %d\n", a);
    return 0;
}
