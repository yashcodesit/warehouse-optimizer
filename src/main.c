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

int main(void)
{
    Warehouse warehouse;
    Location locations[MAX_LOCATIONS];

    int location_count = 0;
    int next_id = 1;
    float capacity;

    printf("================================\n");
    printf("       WAREHOUSE OPTIMIZER\n");
    printf("================================\n");

    capacity = read_float("Enter warehouse capacity (kg): ");

    while (capacity <= 0)
    {
        printf("Capacity must be greater than 0.\n");
        capacity = read_float("Enter warehouse capacity (kg): ");
    }

    initialize_warehouse(&warehouse, capacity);

    load_packages(&warehouse, "data/packages.csv");

    /* Determine the next available package ID */
    for (int i = 0; i < warehouse.package_count; i++)
    {
        if (warehouse.packages[i].id >= next_id)
        {
            next_id = warehouse.packages[i].id + 1;
        }
    }

    location_count = load_locations(
        locations,
        MAX_LOCATIONS,
        "data/locations.csv");

    int choice;

    do
    {
        printf("\n================================\n");
        printf("       MAIN MENU\n");
        printf("================================\n");
        printf("1. Add Package\n");
        printf("2. View All Packages\n");
        printf("3. Update Package\n");
        printf("4. Delete Package\n");
        printf("5. Optimize Package Selection\n");
        printf("6. Optimize Using Branch & Bound\n");
        printf("7. Compare Knapsack Algorithms\n");
        printf("8. Find Shortest Delivery Route\n");
        printf("9. Exit\n");

        choice = read_int("\nEnter your choice: ");

        switch (choice)
        {
        /* ==================================
           1. ADD PACKAGE
           ================================== */
        case 1:
        {
            char name[50];
            float weight;
            float value;

            read_string(
                "Enter package name: ",
                name,
                sizeof(name));

            weight = read_float("Enter weight (kg): ");
            value = read_float("Enter value: ");

            if (weight <= 0 || value < 0)
            {
                printf("\nInvalid weight or value!\n");
                break;
            }

            Package p = create_package(
                next_id,
                name,
                weight,
                value);

            if (add_package(&warehouse, p))
            {
                next_id++;
                printf("\nPackage added successfully!\n");
            }

            break;
        }

        /* ==================================
           2. VIEW ALL PACKAGES
           ================================== */
        case 2:
        {
            display_warehouse(warehouse);
            break;
        }

            /* ==================================
               3. UPDATE PACKAGE
               ================================== */
        case 3:
        {
            int id;
            int found = 0;
            char name[50];
            float weight;
            float value;

            if (warehouse.package_count == 0)
            {
                printf("\nNo packages available to update.\n");
                break;
            }

            display_warehouse(warehouse);
            id = read_int("\nEnter package ID to update: ");

            for (int i = 0; i < warehouse.package_count; i++)
            {
                if (warehouse.packages[i].id == id)
                {
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("\nPackage ID not found!\n");
                break;
            }

            read_string("Enter new package name: ", name, sizeof(name));
            weight = read_float("Enter new weight (kg): ");
            value = read_float("Enter new value: ");

            if (weight <= 0 || value < 0)
            {
                printf("\nInvalid weight or value!\n");
                break;
            }

            Package updated = create_package(id, name, weight, value);

            if (update_package(&warehouse, id, updated))
                printf("\nPackage updated successfully!\n");
            else
                printf("\nFailed to update package.\n");

            break;
        } /* ==================================
              4. DELETE PACKAGE
              ================================== */
        case 4:
        {
            int id;

            if (warehouse.package_count == 0)
            {
                printf("\nNo packages available to delete.\n");
                break;
            }

            display_warehouse(warehouse);

            id = read_int("\nEnter package ID to delete: ");

            if (delete_package(&warehouse, id))
            {
                printf("\nPackage deleted successfully!\n");
            }
            else
            {
                printf("\nPackage ID not found!\n");
            }

            break;
        }

        /* ==================================
           5. DYNAMIC PROGRAMMING KNAPSACK
           ================================== */
        case 5:
        {
            int selected[MAX_PACKAGES];

            solve_knapsack(&warehouse, selected, 1);

            break;
        }

        /* ==================================
           6. BRANCH & BOUND
           ================================== */
        case 6:
        {
            int selected[MAX_PACKAGES];

            printf("\n===== BRANCH & BOUND SELECTION =====\n");

            float value = solve_branch_bound(
                &warehouse,
                selected);

            printf("\nMaximum Value: %.2f\n", value);

            break;
        }

        /* ==================================
           7. COMPARE KNAPSACK ALGORITHMS
           ================================== */
        case 7:
        {
            compare_knapsack_algorithms(&warehouse);
            break;
        }

        /* ==================================
           8. SHORTEST DELIVERY ROUTE (TSP)
           ================================== */
        case 8:
        {
            int n;
            int distances[MAX_LOCATIONS][MAX_LOCATIONS] = {0};
            int route[MAX_LOCATIONS + 1];

            printf("\n===== DELIVERY ROUTE OPTIMIZER =====\n");

            if (location_count < 2)
            {
                n = read_int(
                    "Enter total locations (including Warehouse): ");

                if (n < 2 || n > MAX_LOCATIONS)
                {
                    printf(
                        "Please enter between 2 and %d locations.\n",
                        MAX_LOCATIONS);
                    break;
                }

                locations[0] = create_location(0, "Warehouse");

                for (int i = 1; i < n; i++)
                {
                    char name[50];

                    printf("\nCustomer %d\n", i);

                    read_string(
                        "Enter customer name: ",
                        name,
                        sizeof(name));

                    locations[i] = create_location(i, name);
                }

                location_count = n;
            }
            else
            {
                n = location_count;

                printf("Using saved locations:\n");

                for (int i = 0; i < n; i++)
                {
                    printf(
                        "%d. %s\n",
                        locations[i].id,
                        locations[i].name);
                }
            }

            printf("\nEnter distances between locations (in km):\n");

            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    char prompt[100];

                    snprintf(
                        prompt,
                        sizeof(prompt),
                        "%s to %s: ",
                        locations[i].name,
                        locations[j].name);

                    int distance = read_int(prompt);

                    if (distance < 0)
                    {
                        printf("Distance cannot be negative.\n");
                        distance = 0;
                    }

                    distances[i][j] = distance;
                    distances[j][i] = distance;
                }
            }

            int minimum_distance = solve_tsp(
                distances,
                n,
                route);

            if (minimum_distance >= 0)
            {
                printf("\n===== OPTIMIZED DELIVERY ROUTE =====\n");

                for (int i = 0; i <= n; i++)
                {
                    printf("%s", locations[route[i]].name);

                    if (i < n)
                    {
                        printf(" -> ");
                    }
                }

                printf(
                    "\nMinimum Distance: %d km\n",
                    minimum_distance);
            }
            else
            {
                printf("Unable to calculate route.\n");
            }

            break;
        }

        /* ==================================
           9. EXIT AND SAVE DATA
           ================================== */
        case 9:
        {
            save_packages(&warehouse, "data/packages.csv");

            save_locations(
                locations,
                location_count,
                "data/locations.csv");

            printf("\nExiting WarehouseOptimizer...\n");

            break;
        }

        default:
        {
            printf("\nInvalid menu choice!\n");
            break;
        }
        }

    } while (choice != 9);

    return 0;
}