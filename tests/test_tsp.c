#include <stdio.h>
#include "../include/tsp.h"

int main() {
    int passed = 0;
    int total = 2;
    int route[MAX_LOCATIONS + 1];

    printf("\n===== TSP TESTS =====\n");

    // Test 1: Four locations with a known optimal distance
    int distances[MAX_LOCATIONS][MAX_LOCATIONS] = {0};

    distances[0][1] = distances[1][0] = 10;
    distances[0][2] = distances[2][0] = 15;
    distances[0][3] = distances[3][0] = 20;
    distances[1][2] = distances[2][1] = 35;
    distances[1][3] = distances[3][1] = 25;
    distances[2][3] = distances[3][2] = 30;

    int result = solve_tsp(distances, 4, route);

    if (result == 80) {
        printf("Test 1 - Four locations: PASS\n");
        passed++;
    } else {
        printf("Test 1 - Four locations: FAIL (got %d)\n", result);
    }

    // Test 2: Three locations
    int distances2[MAX_LOCATIONS][MAX_LOCATIONS] = {0};

    distances2[0][1] = distances2[1][0] = 10;
    distances2[0][2] = distances2[2][0] = 15;
    distances2[1][2] = distances2[2][1] = 20;

    result = solve_tsp(distances2, 3, route);

    if (result == 45) {
        printf("Test 2 - Three locations: PASS\n");
        passed++;
    } else {
        printf("Test 2 - Three locations: FAIL (got %d)\n", result);
    }

    printf("\nResult: %d/%d tests passed\n", passed, total);

    return passed == total ? 0 : 1;
}