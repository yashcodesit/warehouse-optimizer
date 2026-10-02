#include "../../include/package.h"
#include <stdio.h>
#include <string.h>

Package create_package(int id, const char *name,
                       float weight, float value) {

    Package p;

    p.id = id;
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';

    p.weight = weight;
    p.value = value;

    return p;
}

void display_package(Package p) {

    printf("\nPackage ID: %d\n", p.id);
    printf("Name: %s\n", p.name);
    printf("Weight: %.2f kg\n", p.weight);
    printf("Value: %.2f\n", p.value);
}