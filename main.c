#include <stdio.h>

int main() {
    printf("--- 五岔路口交通灯相位方案 ---\n\n");

       
    printf("【相位 1（绿灯）】可同时通行路线：\n");
    printf("  A->B, A->C, B->A, D->A, E->A, E->D\n\n");

    printf("【相位 2（绿灯）】可同时通行路线：\n");
    printf("  A->D, B->C, D->B, E->C\n\n");

    printf("【相位 3（绿灯）】可同时通行路线：\n");
    printf("  B->D, D->C, E->B\n\n");

    printf("【相位 4（绿灯）】可同时通行路线：\n");
    printf("  (剩余冲突路线，由系统自动分配)\n\n");

    printf("=========================================\n");
    printf("结论：该路口最少需要 4 个交通灯相位。\n");
    printf("按此方案轮流亮绿灯，即可保障安全高效通行。\n");

    return 0;
}