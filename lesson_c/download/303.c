// 文件：303.c
// 主题：字符串
// 目标：读取字符串a，将其复制到初始化为“Say Hello”的数组s中，
//       输出s
// 实例：
//     输入：hi
//     输出：hi
// 要点：字符串函数
#include <stdio.h>
#include <string.h>
int main(void)
{
    char a[10], s[10]="Say Hello";
    scanf("%s", a);
    strcpy(s, a);
    printf("%s\n", s);
    return 0;
}
