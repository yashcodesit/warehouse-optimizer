#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "warehouse.h"

#define MAX_DP_CAPACITY 100000

float solve_knapsack(Warehouse *w, int selected[], int display);

#endif