#ifndef LOCATION_H
#define LOCATION_H

#define MAX_LOCATIONS 10

typedef struct {
    int id;
    char name[50];
} Location;

Location create_location(int id, const char *name);

void display_location(Location location);

#endif