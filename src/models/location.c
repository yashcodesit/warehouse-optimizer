#include "../../include/location.h"
#include <stdio.h>
#include <string.h>

Location create_location(int id, const char *name) {
    Location location;

    location.id = id;

    strncpy(location.name, name, sizeof(location.name) - 1);
    location.name[sizeof(location.name) - 1] = '\0';

    return location;
}

void display_location(Location location) {
    printf("Location ID: %d\n", location.id);
    printf("Location Name: %s\n", location.name);
}