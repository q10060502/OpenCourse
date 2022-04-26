// 文件：103.c
// 主题：字符输出
// 目标：使用变量保存多个字符”AB“，在屏幕上输出”Say A”、“Say B”
// 要点：（1）标识符命名标准
//       （1.1）必须以字母或下划线作为开头，错误情况如”1x”以数字开头
//       （1.2）只能包含字母、数字或下划线，错误情况如”1.x”包含”.”字符
//       （1.3）不能使用系统保留使用关键字，错误情况如”int”、”if”、”for”
//       （2）字符类型常量使用单引号括起来
//       （3）字符类型常量除转义字符外，不能包含多个字符
//       （4）字符类型常量做加法减法，相当于字符ASCII值的加减，
//	      如”b“-”a“相当于97-96=1
#include <stdio.h>
int main(void)
{
    char ch1 = 'A';
    char ch2 = 'A'+'b'-'a';
    printf("Say %c\n", ch1);
    printf("Say %c\n", ch2);
    return 0;
}