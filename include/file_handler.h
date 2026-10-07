#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "warehouse.h"
#include "location.h"

void save_packages(
    Warehouse *warehouse,
    const char *filename);

void load_packages(
    Warehouse *warehouse,
    const char *filename);

void save_locations(
    Location locations[],
    int count,
    const char *filename);

int load_locations(
    Location locations[],
    int max_locations,
    const char *filename);

#endif