// 文件：201.c
// 主题：选择结构
// 目标：输入两个整数，
//       当a大于0时，如果b大于0则设置b的值为1，否则设置b为0
//       输出“Say ”和b的值
// 实例：
//     输入：1 -1
//     输出：Say 0
//     输入：1  1
//     输出：Say 1
//     输入：-1 123
//     输出：Say 123
// 要点：（1）就近原则，即if和else距离近则为一对判断语句
//       （2）养成if语句使用大括号的习惯
#include <stdio.h>
int main(void)
{
    int a, b;
    scanf("%d %d", &a, &b);
    if(a>0) {
	if(b>0) {
		b = 1;
	} else {
		b = 0;
	}
    }
    printf("Say %d\n", b);
    return 0;
}
