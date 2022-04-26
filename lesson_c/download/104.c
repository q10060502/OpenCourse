// 文件：104.c
// 主题：整数输出
// 目标：使用整型变量保存整数，
//       在屏幕上输出”Say 65“、”Say A“、”Say 1“
// 要点：（1）0x??代表十六进制数，如0x41（即十进制65）
//       （2）0??代表八进制数，如061（即十进制49）
//       （2）整型变量以字符方式输出时，可以输出对应ASCII码值的字符
#include <stdio.h>
int main(void)
{
    int n1 = 65;
    int n2 = 0x31;
    printf("Say %d\n", n1);
    printf("Say %c\n", n1);
    printf("Say %c\n", n2);
    return 0;
}
