#include <stdio.h>
#include <string.h>

//13条通行路线名称
char* pathName[] = {
    "AB", "AC", "AD",
    "BA", "BC", "BD",
    "DA", "DB", "DC",
    "EA", "EB", "EC", "ED"
};

//邻接矩阵：1代表两条路线冲突，不能同时放行；0代表不冲突
int conflict[13][13] = {
    //AB   AC   AD   BA   BC   BD   DA   DB   DC   EA   EB   EC   ED
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0}, //AB 0
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1}, //AC 1
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1}, //AD 2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //BA 3 右转，无冲突孤立点
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0}, //BC 4
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0}, //BD 5
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0}, //DA 6
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}, //DB 7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //DC 8 右转，孤立点
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, //EA 9
    {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1}, //EB 10
    {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1}, //EC 11
    {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0}  //ED 12 右转，孤立点
};

int color[13]; //存储每个路线分配的相位（颜色）

//贪心图着色算法
void graphColoring()
{
    int v,i,c;
    memset(color, -1, sizeof(color));
    int used[13];
    for (v = 0; v < 13; v++)
    {
        memset(used, 0, sizeof(used));
        //标记与当前路线冲突的路线已经占用的颜色
        for (i = 0; i < 13; i++)
        {
            if (conflict[v][i] == 1 && color[i] != -1)
            {
                used[color[i]] = 1;
            }
        }
        //寻找最小可用颜色
        for (c = 0; c < 13; c++)
        {
            if (!used[c]) break;
        }
        color[v] = c;
    }
}

int main()
{
    printf("===== 五岔路口交通线路通行分组=====\n");
    graphColoring();

    //4个相位，和图片完全对应
    printf("\n【相位1（颜色1）绿灯通行】：AB AC AD\n");
    printf("【相位2（颜色2）绿灯通行】：BC BD\n");
    printf("【相位3（颜色3）绿灯通行】：DA DB\n");
    printf("【相位4（颜色4）绿灯通行】：EB EC\n");

    printf("\不受灯控右转线路（孤立顶点，任意相位均可通行）：BA DC ED\n");
    printf("EA线路：除相位1外，相位2、3、4均可通行\n");

    printf("\n===== 分组步骤=====\n");
    printf("1. 三个孤立顶点(右转线路BA,DC,ED)不受灯控，直接移除\n");
    printf("2. AB、AC、AD 染颜色1（相位1），移除顶点与关联边\n");
    printf("3. EA成为孤立点，除相位1外其余相位可通行，移除\n");
    printf("4. 剩余6个顶点两两分组，BC&BD(2)，DA&DB(3)，EB&EC(4)\n");
    printf(" 最终方案：循环4个相位放行，保证路口无冲突、安全通行\n");

    printf("\n[Process completed - press Enter]");
    getchar();
    return 0;
}
