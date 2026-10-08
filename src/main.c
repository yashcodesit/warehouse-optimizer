#include <stdio.h>

#include "../include/package.h"
#include "../include/warehouse.h"
#include "../include/knapsack.h"
#include "../include/tsp.h"
#include "../include/location.h"
#include "../include/input.h"
#include "../include/file_handler.h"
#include "../include/branch_bound.h"
#include "../include/algorithm_comparison.h"

int main() {
    Warehouse warehouse;
    Location locations[MAX_LOCATIONS];

    int location_count = 0;
    int next_id = 1;
    float capacity;

    printf("================================\n");
    printf("       WAREHOUSE OPTIMIZER\n");
    printf("================================\n");

    capacity = read_float("Enter warehouse capacity (kg): ");

    while (capacity <= 0) {
        printf("Capacity must be greater than 0.\n");
        capacity = read_float("Enter warehouse capacity (kg): ");
    }

    initialize_warehouse(&warehouse, capacity);

    load_packages(&warehouse, "data/packages.csv");

    for (int i = 0; i < warehouse.package_count; i++) {
        if (warehouse.packages[i].id >= next_id) {
            next_id = warehouse.packages[i].id + 1;
        }
    }

    location_count = load_locations(
        locations,
        MAX_LOCATIONS,
        "data/locations.csv"
    );

    int choice;

    do {
        printf("\n================================\n");
        printf("       MAIN MENU\n");
        printf("================================\n");
        printf("1. Add Package\n");
        printf("2. View All Packages\n");
        printf("3. Optimize Package Selection\n");
        printf("4. Optimize Using Branch & Bound\n");
        printf("5. Compare Knapsack Algorithms\n");
        printf("6. Find Shortest Delivery Route\n");
        printf("7. Exit\n");

        choice = read_int("\nEnter your choice: ");

        switch (choice) {
        case 1: {
            char name[50];
            float weight;
            float value;

            read_string("Enter package name: ", name, sizeof(name));
            weight = read_float("Enter weight (kg): ");
            value = read_float("Enter value: ");

            if (weight <= 0 || value < 0) {
                printf("\nInvalid weight or value!\n");
                break;
            }

            Package p = create_package(next_id++, name, weight, value);

            if (add_package(&warehouse, p)) {
                printf("\nPackage added successfully!\n");
            }

            break;
        }

        case 2:
            display_warehouse(warehouse);
            break;

        case 3: {
            int selected[MAX_PACKAGES];

            solve_knapsack(&warehouse, selected, 1);;
            break;
        }

        case 4: {
            int selected[MAX_PACKAGES];

            printf("\n===== BRANCH & BOUND SELECTION =====\n");

            float value = solve_branch_bound(&warehouse, selected);

            printf("\nMaximum Value: %.2f\n", value);
            break;
        }

        case 5:
            compare_knapsack_algorithms(&warehouse);
            break;

        case 6: {
            int n;
            int distances[MAX_LOCATIONS][MAX_LOCATIONS] = {0};
            int route[MAX_LOCATIONS + 1];

            printf("\n===== DELIVERY ROUTE OPTIMIZER =====\n");

            if (location_count < 2) {
                n = read_int("Enter total locations (including Warehouse): ");

                if (n < 2 || n > MAX_LOCATIONS) {
                    printf("Please enter between 2 and %d locations.\n", MAX_LOCATIONS);
                    break;
                }

                locations[0] = create_location(0, "Warehouse");

                for (int i = 1; i < n; i++) {
                    char name[50];

                    printf("\nCustomer %d\n", i);
                    read_string("Enter customer name: ", name, sizeof(name));

                    locations[i] = create_location(i, name);
                }

                location_count = n;
            } else {
                n = location_count;

                printf("Using saved locations:\n");

                for (int i = 0; i < n; i++) {
                    printf("%d. %s\n", locations[i].id, locations[i].name);
                }
            }

            printf("\nEnter distances between locations (in km):\n");

            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    char prompt[100];

                    snprintf(
                        prompt,
                        sizeof(prompt),
                        "%s to %s: ",
                        locations[i].name,
                        locations[j].name
                    );

                    int distance = read_int(prompt);

                    if (distance < 0) {
                        printf("Distance cannot be negative.\n");
                        distance = 0;
                    }

                    distances[i][j] = distance;
                    distances[j][i] = distance;
                }
            }

            int minimum_distance = solve_tsp(distances, n, route);

            if (minimum_distance >= 0) {
                printf("\n===== OPTIMIZED DELIVERY ROUTE =====\n");

                for (int i = 0; i <= n; i++) {
                    printf("%s", locations[route[i]].name);

                    if (i < n) {
                        printf(" -> ");
                    }
                }

                printf("\nMinimum Distance: %d km\n", minimum_distance);
            } else {
                printf("Unable to calculate route.\n");
            }

            break;
        }

        case 7:
            save_packages(&warehouse, "data/packages.csv");
            save_locations(locations, location_count, "data/locations.csv");

            printf("\nExiting WarehouseOptimizer...\n");
            break;

        default:
            printf("\nInvalid menu choice!\n");
        }

    } while (choice != 7);

    return 0;
}