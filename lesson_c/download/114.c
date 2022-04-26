// 文件：114.c
// 主题：内存大小运算符
// 目标：使用字符变量ch存储字符'\x41'，
//       输出“Say ”和ch所占内存字节数，
//       输出”Say “和字符串”\x41“所占内存字节数
// 要点：（1）sizeof是运算符，不是函数
//       （2）C语言字符串结尾会自动存储ASCII码值为0的字符
//            如sizeof("\x41")占两个字节，
//            包括ASCII码值为0x41和0x0的两个字符
#include <stdio.h>
int main(void)
{
    char ch='\x41';
    printf("Say %d\n", sizeof(ch));
    printf("Say %d\n", sizeof("\x41"));
    return 0;
}
