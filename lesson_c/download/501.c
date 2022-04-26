// 文件：501.c
// 主题：结构类型
// 目标：定义玩家结构体类型player_t，包含整型编号、数组昵称，
//       声明玩家结构体变量player，编号为1001,昵称为“tx”，
//       输出“Say ”和玩家编号、昵称
// 实例：
//     输出：Say 1001 tx
// 要点：结构体类型的定义、变量的初始化、成员的引用
#include <stdio.h>
struct player_t{
    int id;
    char nick[32];
}; 
int main(void)
{
    struct player_t player = {1001, "tx"};
    printf("Say %d %s\n", player.id, player.nick);
    return 0;
}
