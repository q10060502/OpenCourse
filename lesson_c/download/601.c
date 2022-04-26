// 文件：601.c
// 主题：指向一维数组的指针
// 目标：定义已初始化为{1,2,3,4}的数组，
//       定义指针p指向该数组，
//       定义指针q指向该数组第3个数组元素，
//       使用指针p输出“Say ”和第3个数组元素的值
//       使用指针q输出“Say ”和第3个数组元素的值
//       使用数组名称输出“Say ”和第3个数组元素的值
// 实例：
//     输出：Say 3
// 要点：（1）指针指向数组的方法
//       （2）使用指针、数组名称访问数组元素
#include <stdio.h>
int main(void)
{
    int a[] = {1,2,3,4};
    int *p = a;
    int *q;
    q = a + 2;
    printf("Say %d\n", *(p+2));
    printf("Say %d\n", *q);
    printf("Say %d\n", *(a+2));
    return 0;
}
