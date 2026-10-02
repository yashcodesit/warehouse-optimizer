#ifndef PACKAGE_H
#define PACKAGE_H

typedef struct {
    int id;
    char name[50];
    float weight;
    float value;
} Package;

Package create_package(int id, const char *name,float weight, float value);

void display_package(Package p);

#endif