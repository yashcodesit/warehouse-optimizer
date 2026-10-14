#include <stdio.h>
#include <math.h>
#include "../include/knapsack.h"

int main() {
    Warehouse warehouse;
    int selected[MAX_PACKAGES];
    int passed = 0;
    int total = 4;

    initialize_warehouse(&warehouse, 10.0f);

    printf("\n===== KNAPSACK TESTS =====\n");

    float result = solve_knapsack(&warehouse, selected, 0);
    if (result == 0) {
        printf("Test 1 - Empty warehouse: PASS\n");
        passed++;
    } else {
        printf("Test 1 - Empty warehouse: FAIL\n");
    }

    add_package(&warehouse, create_package(1, "Laptop", 2.0f, 100.0f));
    result = solve_knapsack(&warehouse, selected, 0);
    if (fabsf(result - 100.0f) < 0.001f && selected[0] == 1) {
        printf("Test 2 - Single package: PASS\n");
        passed++;
    } else {
        printf("Test 2 - Single package: FAIL\n");
    }
    initialize_warehouse(&warehouse, 1.0f);
    add_package(&warehouse, create_package(2, "Printer", 5.0f, 200.0f));
    result = solve_knapsack(&warehouse, selected, 0);
    if (result == 0 && selected[0] == 0) {
        printf("Test 3 - Package exceeds capacity: PASS\n");
        passed++;
    } else {
        printf("Test 3 - Package exceeds capacity: FAIL\n");
    }
    initialize_warehouse(&warehouse, 5.0f);
    add_package(&warehouse, create_package(1, "A", 2.0f, 40.0f));
    add_package(&warehouse, create_package(2, "B", 3.0f, 50.0f));
    add_package(&warehouse, create_package(3, "C", 4.0f, 70.0f));

    result = solve_knapsack(&warehouse, selected, 0);
    if (fabsf(result - 90.0f) < 0.001f &&
        selected[0] == 1 && selected[1] == 1 && selected[2] == 0) {
        printf("Test 4 - Best combination: PASS\n");
        passed++;
    } else {
        printf("Test 4 - Best combination: FAIL\n");
    }

    printf("\nResult: %d/%d tests passed\n", passed, total);
    return passed == total ? 0 : 1;
}