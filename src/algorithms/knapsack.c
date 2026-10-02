#include "../../include/knapsack.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

float solve_knapsack(Warehouse *w, int selected[]) {

    int n = w->package_count;

    int capacity = (int)roundf(w->capacity * 1000);

    if (n == 0 || capacity < 0) {
        return 0;
    }

    if (capacity > INT_MAX / (n + 1) - 1) {
        printf("Capacity too large for DP table.\n");
        return -1;
    }

    int cols = capacity + 1;

    float *dp = calloc((size_t)(n + 1) * cols, sizeof(float));

    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        selected[i] = 0;
    }

    for (int i = 1; i <= n; i++) {

        int weight = (int)roundf(
            w->packages[i - 1].weight * 1000
        );

        float value = w->packages[i - 1].value;

        for (int j = 0; j <= capacity; j++) {

            float exclude = dp[(size_t)(i - 1) * cols + j];

            float include = -1;

            if (weight <= j) {
                include = value +
                    dp[(size_t)(i - 1) * cols + j - weight];
            }

            dp[(size_t)i * cols + j] =
                (include > exclude) ? include : exclude;
        }
    }

    float max_value = dp[(size_t)n * cols + capacity];

    int remaining = capacity;

    for (int i = n; i > 0; i--) {

        float current = dp[(size_t)i * cols + remaining];

        float previous = dp[(size_t)(i - 1) * cols + remaining];

        if (current > previous + 0.00001f) {

            selected[i - 1] = 1;

            int weight = (int)roundf(
                w->packages[i - 1].weight * 1000
            );

            remaining -= weight;
        }
    }

    printf("\n===== OPTIMIZED PACKAGE SELECTION =====\n");

    float total_weight = 0;

    for (int i = 0; i < n; i++) {

        if (selected[i]) {

            printf("%s | Weight: %.2f kg | Value: %.2f\n",
                   w->packages[i].name,
                   w->packages[i].weight,
                   w->packages[i].value);

            total_weight += w->packages[i].weight;
        }
    }

    printf("\nTotal Weight: %.2f kg\n", total_weight);
    printf("Maximum Value: %.2f\n", max_value);

    free(dp);

    return max_value;
}