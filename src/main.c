#include <stdio.h>

#include "../include/package.h"
#include "../include/warehouse.h"
#include "../include/knapsack.h"
#include "../include/tsp.h"

int main()
{
  Warehouse warehouse;
  initialize_warehouse(&warehouse, 15.0);

  int choice;
  int next_id = 1;

  do
  {
    printf("\n================================\n");
    printf("       WAREHOUSE OPTIMIZER\n");
    printf("================================\n");

    printf("1. Add Package\n");
    printf("2. View All Packages\n");
    printf("3. Optimize Package Selection\n");
    printf("4. Find Shortest Delivery Route\n");
    printf("5. Exit\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {

    case 1:
    {
      char name[50];
      float weight, value;

      printf("Enter package name: ");
      scanf(" %49[^\n]", name);

      printf("Enter weight (kg): ");
      scanf("%f", &weight);

      printf("Enter value: ");
      scanf("%f", &value);

      if (weight <= 0 || value < 0)
      {
        printf("Invalid weight or value!\n");
        break;
      }

      Package p = create_package(
          next_id++, name, weight, value);

      if (add_package(&warehouse, p))
      {
        printf("Package added successfully!\n");
      }

      break;
    }

    case 2:
      display_warehouse(warehouse);
      break;

    case 3:
    {
      int selected[MAX_PACKAGES];
      solve_knapsack(&warehouse, selected);
      break;
    }

    case 4:
    {
      int n;

      Location locations[MAX_LOCATIONS];

      int distances[MAX_LOCATIONS][MAX_LOCATIONS] = {0};

      int route[MAX_LOCATIONS + 1];

      printf("\n===== DELIVERY ROUTE OPTIMIZER =====\n");

      printf("Enter total locations (including Warehouse): ");
      scanf("%d", &n);

      if (n < 2 || n > MAX_LOCATIONS)
      {
        printf("Please enter between 2 and %d locations.\n",
               MAX_LOCATIONS);
        break;
      }

      locations[0] = create_location(0, "Warehouse");

      for (int i = 1; i < n; i++)
      {
        char name[50];

        printf("Enter name of Customer %d: ", i);
        scanf(" %49[^\n]", name);

        locations[i] = create_location(i, name);
      }

      printf("\nEnter distances between locations (in km):\n");

      for (int i = 0; i < n; i++)
      {
        for (int j = i + 1; j < n; j++)
        {
          printf("%s to %s: ",
                 locations[i].name,
                 locations[j].name);

          scanf("%d", &distances[i][j]);

          distances[j][i] = distances[i][j];
        }
      }

      int minimum_distance =
          solve_tsp(distances, n, route);

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

        printf("\nMinimum Distance: %d km\n",
               minimum_distance);
      }
      else
      {
        printf("Unable to calculate route.\n");
      }

      break;
    }
    case 5:
      printf("Exiting WarehouseOptimizer...\n");
      break;

    default:
      printf("Invalid choice! Try again.\n");
    }

  } while (choice != 5);

  return 0;
}