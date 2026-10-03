#include <stdio.h>
#include "../include/package.h"
#include "../include/warehouse.h"
#include "../include/knapsack.h"

int main() {

    Warehouse warehouse;

    initialize_warehouse(&warehouse, 15.0);

    int choice;
    int next_id = 1;

    do {

        printf("\n================================\n");
        printf("       WAREHOUSE OPTIMIZER\n");
        printf("================================\n");

        printf("1. Add Package\n");
        printf("2. View All Packages\n");
        printf("3. Optimize Package Selection\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {

                char name[50];
                float weight, value;

                printf("Enter package name: ");
                scanf(" %49[^\n]", name);

                printf("Enter weight (kg): ");
                scanf("%f", &weight);

                printf("Enter value: ");
                scanf("%f", &value);

                if (weight <= 0 || value < 0) {
                    printf("Invalid weight or value!\n");
                    break;
                }

                Package p = create_package(
                    next_id++, name, weight, value
                );

                if (add_package(&warehouse, p)) {
                    printf("Package added successfully!\n");
                }

                break;
            }

            case 2:

                display_warehouse(warehouse);
                break;

            case 3: {

                int selected[MAX_PACKAGES];

                solve_knapsack(&warehouse, selected);
                break;
            }

            case 4:

                printf("Exiting WarehouseOptimizer...\n");
                break;

            default:

                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}