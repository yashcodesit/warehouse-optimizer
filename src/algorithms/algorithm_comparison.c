#include "../../include/algorithm_comparison.h"
#include "../../include/knapsack.h"
#include "../../include/branch_bound.h"

#include <stdio.h>

void compare_knapsack_algorithms(Warehouse *warehouse) {
    int dp_selected[MAX_PACKAGES];
    int bb_selected[MAX_PACKAGES];

    printf("\n========== ALGORITHM COMPARISON ==========\n");

    float dp_value = solve_knapsack(warehouse, dp_selected, 0);;
    float bb_value = solve_branch_bound(warehouse, bb_selected);

    printf("\n---------- RESULTS ----------\n");
    printf("Dynamic Programming : %.2f\n", dp_value);
    printf("Branch & Bound      : %.2f\n", bb_value);
    if (dp_value == bb_value) {
        printf("Both algorithms found the same optimal value.\n");
    } else {
        printf("Results are different. Check the algorithms.\n");
    }

    printf("==========================================\n");
}