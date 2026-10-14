#include <stdio.h>
#include <math.h>
#include "../include/branch_bound.h"
#include "../include/package.h"
#include "../include/warehouse.h"

int main() {
    Warehouse warehouse;
    int selected[MAX_PACKAGES];
    int passed = 0;
    int total = 3;
    float result;

    printf("\n===== BRANCH & BOUND TESTS =====\n");

    // Test 1: Empty warehouse
    initialize_warehouse(&warehouse, 10.0f);
    result = solve_branch_bound(&warehouse, selected);

    if (fabsf(result) < 0.001f) {
        printf("Test 1 - Empty warehouse: PASS\n");
        passed++;
    } else {
        printf("Test 1 - Empty warehouse: FAIL\n");
    }

    // Test 2: Package exceeds capacity
    initialize_warehouse(&warehouse, 1.0f);
    add_package(&warehouse, create_package(1, "Printer", 5.0f, 200.0f));

    result = solve_branch_bound(&warehouse, selected);

    if (fabsf(result) < 0.001f && selected[0] == 0) {
        printf("Test 2 - Package exceeds capacity: PASS\n");
        passed++;
    } else {
        printf("Test 2 - Package exceeds capacity: FAIL\n");
    }

    // Test 3: Best package combination
    initialize_warehouse(&warehouse, 5.0f);
    add_package(&warehouse, create_package(1, "A", 2.0f, 40.0f));
    add_package(&warehouse, create_package(2, "B", 3.0f, 50.0f));
    add_package(&warehouse, create_package(3, "C", 4.0f, 70.0f));

    result = solve_branch_bound(&warehouse, selected);

    if (fabsf(result - 90.0f) < 0.001f &&
        selected[0] == 1 && selected[1] == 1 && selected[2] == 0) {
        printf("Test 3 - Best combination: PASS\n");
        passed++;
    } else {
        printf("Test 3 - Best combination: FAIL\n");
    }

    printf("\nResult: %d/%d tests passed\n", passed, total);

    return passed == total ? 0 : 1;
}