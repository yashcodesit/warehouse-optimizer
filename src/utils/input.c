#include "../../include/input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_int(const char *prompt) {
    char buffer[100];
    int value;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Input error. Please try again.\n");
            continue;
        }

        char extra;

        if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input. Please enter an integer.\n");
    }
}

float read_float(const char *prompt) {
    char buffer[100];
    float value;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Input error. Please try again.\n");
            continue;
        }

        char extra;

        if (sscanf(buffer, "%f %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid input. Please enter a number.\n");
    }
}

void read_string(
    const char *prompt,
    char *buffer,
    int size
) {
    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, size, stdin) == NULL) {
            printf("Input error. Please try again.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            printf("Input cannot be empty.\n");
            continue;
        }

        return;
    }
}