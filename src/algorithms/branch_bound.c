#include "../../include/branch_bound.h"
#include <stdio.h>

typedef struct {
    int index;
    float weight;
    float value;
    float ratio;
} BBItem;

static float calculate_bound(BBItem items[], int n, int index, float weight, float value, float capacity) {
    if (weight >= capacity) return value;

    float bound = value;

    for (int i = index; i < n; i++) {
        if (weight + items[i].weight <= capacity) {
            weight += items[i].weight;
            bound += items[i].value;
        } else {
            float remaining = capacity - weight;
            bound += remaining * items[i].ratio;
            break;
        }
    }

    return bound;
}

static void branch(
    BBItem items[],
    int n,
    int index,
    float weight,
    float value,
    float capacity,
    int current[],
    int best[],
    float *best_value
) {
    if (index == n) {
        if (value > *best_value) {
            *best_value = value;
            for (int i = 0; i < n; i++) best[i] = current[i];
        }
        return;
    }

    float bound = calculate_bound(items, n, index, weight, value, capacity);

    if (bound <= *best_value) return;

    if (weight + items[index].weight <= capacity) {
        current[items[index].index] = 1;

        branch(
            items, n, index + 1,
            weight + items[index].weight,
            value + items[index].value,
            capacity,
            current, best, best_value
        );

        current[items[index].index] = 0;
    }

    branch(
        items, n, index + 1,
        weight,
        value,
        capacity,
        current, best, best_value
    );
}

float solve_branch_bound(Warehouse *w, int selected[]) {
    int n = w->package_count;

    if (n == 0) return 0;

    BBItem items[MAX_PACKAGES];

    for (int i = 0; i < n; i++) {
        items[i].index = i;
        items[i].weight = w->packages[i].weight;
        items[i].value = w->packages[i].value;
        items[i].ratio = w->packages[i].value / w->packages[i].weight;
        selected[i] = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[i].ratio < items[j].ratio) {
                BBItem temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }

    int current[MAX_PACKAGES] = {0};
    int best[MAX_PACKAGES] = {0};
    float best_value = 0;

    branch(items, n, 0,0, 0,w->capacity,current, best, &best_value
    );

    for (int i = 0; i < n; i++) {
        selected[i] = best[i];

        if (selected[i]) {
            printf("%s | Weight: %.2f kg | Value: %.2f\n",w->packages[i].name,w->packages[i].weight,w->packages[i].value);
        }
    }

    return best_value;
}