// 文件：801.c
// 主题：文件
// 目标：只写方式打开文本文件写入"Say Hello"
// 要点：文件多种打开方式、写入、关闭
#include <stdio.h>
int main(void)
{
    char *s = "Say Hello\n";
    FILE *fp;
    fp = fopen("prog.cmd", "wt");
    fwrite(s, strlen(s), 1, fp);
    fclose(fp);
    return 0;
}
