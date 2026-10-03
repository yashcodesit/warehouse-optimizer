#ifndef TSP_H
#define TSP_H

#include "location.h"

int solve_tsp(
    int distances[MAX_LOCATIONS][MAX_LOCATIONS],
    int n,
    int route[]
);

#endif