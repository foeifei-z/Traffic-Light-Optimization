#include <stdio.h>
#include <stdbool.h>

#define TOTAL_ROUTES 13 // 总共 13 条路线
#define MAX_COLORS 4    // 最大相位数

// 路线名称映射 (按图例字母排序)
const char* route_names[TOTAL_ROUTES] = {
    "AB", "AC", "AD", "BA", "BC", "BD", "DA", "DB", "DC", "EA", "EB", "EC", "ED"
};

// 路线索引定义，方便代码阅读
enum {
    IDX_AB, IDX_AC, IDX_AD, IDX_BA, IDX_BC, IDX_BD, 
    IDX_DA, IDX_DB, IDX_DC, IDX_EA, IDX_EB, IDX_EC, IDX_ED
};

// 存储每条路线的最终相位分配
int colors[TOTAL_ROUTES];

// 根据最后一张图的连线，定义剩余6个点（BC, BD, DA, DB, EB, EC）的冲突矩阵
// 顺序：BC, BD, DA, DB, EB, EC
int conflict_matrix[6][6] = {
    // BC BD DA DB EB EC
    { 0, 0, 1, 0, 1, 0 }, // BC 冲突于 DA, EB
    { 0, 0, 1, 1, 0, 0 }, // BD 冲突于 DA, DB
    { 1, 1, 0, 0, 1, 0 }, // DA 冲突于 BC, BD, EB
    { 0, 1, 0, 0, 1, 1 }, // DB 冲突于 BD, EB, EC
    { 1, 0, 1, 1, 0, 0 }, // EB 冲突于 BC, DA, DB
    { 0, 0, 0, 1, 0, 0 }  // EC 冲突于 DB
};

// 剩余6个点的原始索引
int remaining_indices[6] = { IDX_BC, IDX_BD, IDX_DA, IDX_DB, IDX_EB, IDX_EC };

// 检查给剩余节点中的第 node 个分配 color 是否合法
bool is_safe(int node, int color) {
    for (int i = 0; i < 6; i++) {
        if (conflict_matrix[node][i] == 1 && colors[remaining_indices[i]] == color) {
            return false;
        }
    }
    return true;
}

// 贪心着色算法
void greedy_coloring_remaining() {
    // 初始化这6个点的颜色
    for (int i = 0; i < 6; i++) {
        colors[remaining_indices[i]] = 0;
    }

    // 为这 6 个节点分配颜色
    for (int i = 0; i < 6; i++) {
        // 从颜色 2 开始尝试（颜色 1 已经被 AB/AC/AD 占用，且 EA 不能与 1 冲突）
        for (int c = 2; c <= MAX_COLORS; c++) {
            if (is_safe(i, c)) {
                colors[remaining_indices[i]] = c;
                break; 
            }
        }
    }
}

// 打印结果
void print_results() {
    int max_color = 0;
    printf("--- 五岔路口交通灯相位优化方案 ---\n\n");
    
    // 1. 明确区分 EA 和 完全不受限的右转线
    printf("【完全不受灯控限制路线】（可随意通行）:\n");
    printf("  BA, DC, ED\n\n");

    printf("【受相位1限制的特殊路线】（只能在相位 2,3,4 通行）:\n");
    printf("  EA\n\n");

    // 2. 颜色 1 组
    printf("【相位 1】:\n");
    printf("  AB, AC, AD\n\n");

    // 3. 剩余 6 个点的分配情况
    printf("【剩余6个顶点的贪心着色结果】:\n");
    for (int i = 0; i < 6; i++) {
        int idx = remaining_indices[i];
        printf("  路线 %-3s 分配相位: %d\n", route_names[idx], colors[idx]);
        if (colors[idx] > max_color) {
            max_color = colors[idx];
        }
    }

    // 4. 按相位分组打印
    printf("\n--- 相位分组汇总 ---\n");
    for (int c = 1; c <= max_color; c++) {
        printf("相位 %d 包含路线: ", c);
        
        // 相位1 包含固定的三个和 EA 的排除逻辑
        if (c == 1) {
            printf("AB AC AD ");
            // 注意：此处刻意不打印 EA，因为 EA 不能在相位1通行
        } else {
            // 相位 2,3,4 可以包含 EA (由于它此时相当于孤立点，不会与其他冲突)
            printf("EA "); 
        }
        
        // 打印剩余6个点中符合条件的
        for (int i = 0; i < 6; i++) {
            if (colors[remaining_indices[i]] == c) {
                printf("%s ", route_names[remaining_indices[i]]);
            }
        }
        printf("\n");
    }
    
    printf("（注：BA, DC, ED 不受灯控限制；EA 仅在相位 1 时禁止通行）\n");
    printf("\n最少需要的相位总数为: %d\n", max_color);
}

int main() {
    printf("开始计算交通灯相位分配...\n\n");
    
    greedy_coloring_remaining();
    print_results();

    return 0;
}
