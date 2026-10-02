#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "package.h"

#define MAX_PACKAGES 100

typedef struct {
    Package packages[MAX_PACKAGES];

    int package_count;

    float capacity;

} Warehouse;

void initialize_warehouse(Warehouse *w, float capacity);

int add_package(Warehouse *w, Package p);

void display_warehouse(Warehouse w);

#endif