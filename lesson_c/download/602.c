// 文件：602.c
// 主题：指向结构类型的指针
// 目标：定义玩家结构体类型player_t，包含整型编号、数组昵称，
//       声明玩家结构体变量player，编号为1001,昵称为“tx”，
//       使用指针p指向player，
//       输出“Say ”和玩家编号、昵称
// 实例：
//     输出：Say 1001 tx
// 要点：指向结构类型指针的定义和引用
#include <stdio.h>
struct player_t{
    int id;
    char nick[32];
} player = {1001, "tx"};
struct player_t *p = &player;
int main(void)
{
    printf("Say %d %s\n", p->id, (*p).nick);
    return 0;
}
