// 文件：202.c
// 主题：选择结构（switch）
// 目标：输入一个整数，
//       如果为1则输出“Say 1”，
//       如果为2则输出“Say 1“、”Say 2”，
//       如果为3或4则输出“Say 3 or 4”，
//       否则输出“Say error”
// 实例：输入：1
//       输出：Say 1
//       输入：2
//       输出：Say 1
//             Say 2
//       输入：3
//       输出：Say 3 or 4
// 要点：（1）遇到break则跳出switch语句块
//       （2）case后的值不能相同
#include <stdio.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    switch(n) {
        case 1:
            printf("Say 1\n");
        case 2:
            printf("Say 2\n");
            break;
        case 3:
        case 4:
            printf("Say 3 or 4\n");
            break;
        default:
            printf("Say error\n");
    }
    return 0;
}
