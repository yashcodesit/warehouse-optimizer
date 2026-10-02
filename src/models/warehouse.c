#include "../../include/warehouse.h"
#include <stdio.h>

void initialize_warehouse(Warehouse *w, float capacity) {

    w->package_count = 0;
    w->capacity = capacity;
}

int add_package(Warehouse *w, Package p) {

    if (w->package_count >= MAX_PACKAGES) {
        printf("Error: Warehouse is full!\n");
        return 0;
    }

    w->packages[w->package_count] = p;

    w->package_count++;

    return 1;
}

void display_warehouse(Warehouse w) {

    printf("\n========== WAREHOUSE ==========\n");

    printf("Capacity: %.2f kg\n", w.capacity);

    printf("Total Packages: %d\n", w.package_count);

    printf("\n---------- PACKAGE LIST ----------\n");

    for (int i = 0; i < w.package_count; i++) {

        display_package(w.packages[i]);

    }

    printf("\n=================================\n");
}