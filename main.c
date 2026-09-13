#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 定义13条路线的名称
const char *route_names[] = {
    "AB", "AC", "AD", "BA", "BC", "BD",
    "DA", "DB", "DC", "EA", "EB", "EC", "ED"
};
#define N 13 // 路线总数

// 冲突矩阵：adj[i][j] = 1 表示路线 i 和 j 冲突
int adj[N][N] = {0};

// 初始化冲突关系（根据图片中的连线手动构建）
void init_conflicts() {
    // 为了方便，我们用索引对应路线：
    // 0:AB, 1:AC, 2:AD, 3:BA, 4:BC, 5:BD, 6:DA, 7:DB, 8:DC, 9:EA, 10:EB, 11:EC, 12:ED

    // 根据图片，BA(3), DC(8), ED(12) 是孤立点，没有连线。
    // 第1组：AB(0), AC(1), AD(2) 之间无连线，但它们与以下点有连线：
    // 连线（冲突）：
    // AB(0) 与 BC(4), BD(5), DA(6), DB(7), EB(10), EC(11) 相连（图中大圈连线）
    // AC(1) 与 BC(4), BD(5), DA(6), DB(7), EB(10), EC(11) 相连
    // AD(2) 与 BC(4), BD(5), DA(6), DB(7), EB(10), EC(11) 相连

    // 剩余 6 个点内部连线：
    // BC(4) - DA(6), DB(7)
    // BD(5) - DA(6), DB(7), EC(11)
    // DA(6) - EB(10), EC(11)
    // DB(7) - EB(10), EC(11)
    // EB(10) - BD(5), DB(7)
    // EC(11) - BD(5), DA(6)
    // EA(9) 原本与 AB, AC, AD 相连，去掉第1组后，EA 无连线。

    // 填充矩阵（对称）
    int pairs[][2] = {
        {0,4},{0,5},{0,6},{0,7},{0,10},{0,11},
        {1,4},{1,5},{1,6},{1,7},{1,10},{1,11},
        {2,4},{2,5},{2,6},{2,7},{2,10},{2,11},
        {4,6},{4,7},
        {5,6},{5,7},{5,11},
        {6,10},{6,11},
        {7,10},{7,11},
        {10,5},{10,7},
        {11,5},{11,6},
        {9,0},{9,1},{9,2} // EA 与第1组冲突
    };
    int i;
    for (i = 0; i < sizeof(pairs)/sizeof(pairs[0]); i++) {
        adj[pairs[i][0]][pairs[i][1]] = 1;
        adj[pairs[i][1]][pairs[i][0]] = 1;
    }
}

int color[N]; // 存储每个顶点的颜色（组号）

int main() {
    init_conflicts();
    memset(color, -1, sizeof(color)); // -1 表示未着色

    int current_color = 1;
    int i, j, k;
    // 贪心着色
    for (i = 0; i < N; i++) {
        if (color[i] != -1) continue; // 已着色
        color[i] = current_color;
        for (j = i + 1; j < N; j++) {
            if (color[j] == -1) {
                bool conflict = false;
                for (k = 0; k < N; k++) {
                    if (color[k] == current_color && adj[j][k]) {
                        conflict = true; break;
                    }
                }
                if (!conflict) color[j] = current_color;
            }
        }
        current_color++;
    }

    // 输出分组结果
    int c;
    printf("交通灯分组方案：\n");
    for (c = 1; c < current_color; c++) {
        printf("第 %d 组（颜色 %d）：", c, c);
        for (i = 0; i < N; i++) {
            if (color[i] == c) printf("%s ", route_names[i]);
        }
        printf("\n");
    }
    return 0;
}
