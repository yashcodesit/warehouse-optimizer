#include "../../include/file_handler.h"

#include <stdio.h>

void save_packages(
    Warehouse *warehouse,
    const char *filename)
{
  FILE *file = fopen(filename, "w");

  if (file == NULL)
  {
    printf("Error: Could not open package file.\n");
    return;
  }

  fprintf(
      file,
      "id,name,weight,value\n");

  for (int i = 0; i < warehouse->package_count; i++)
  {

    Package p = warehouse->packages[i];

    fprintf(
        file,
        "%d,%s,%.2f,%.2f\n",
        p.id,
        p.name,
        p.weight,
        p.value);
  }

  fclose(file);

  printf("Packages saved successfully.\n");
}

void load_packages(
    Warehouse *warehouse,
    const char *filename)
{
  FILE *file = fopen(filename, "r");

  if (file == NULL)
  {
    printf("No existing package data found.\n");
    return;
  }

  char line[200];

  // Skip CSV header
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file))
  {

    int id;
    char name[50];
    float weight;
    float value;

    if (sscanf(
            line,
            "%d,%49[^,],%f,%f",
            &id,
            name,
            &weight,
            &value) == 4)
    {

      Package p = create_package(
          id,
          name,
          weight,
          value);

      add_package(
          warehouse,
          p);
    }
  }

  fclose(file);

  printf("Packages loaded successfully.\n");
}
void save_locations(
    Location locations[],
    int count,
    const char *filename)
{
  FILE *file = fopen(filename, "w");

  if (file == NULL)
  {
    printf("Error: Could not open location file.\n");
    return;
  }

  fprintf(
      file,
      "id,name\n");

  for (int i = 0; i < count; i++)
  {

    fprintf(
        file,
        "%d,%s\n",
        locations[i].id,
        locations[i].name);
  }

  fclose(file);

  printf("Locations saved successfully.\n");
}

int load_locations(
    Location locations[],
    int max_locations,
    const char *filename)
{
  FILE *file = fopen(filename, "r");

  if (file == NULL)
  {
    printf("No existing location data found.\n");
    return 0;
  }

  char line[100];
  int count = 0;

  // Skip CSV header
  fgets(
      line,
      sizeof(line),
      file);

  while (
      count < max_locations &&
      fgets(line, sizeof(line), file))
  {

    int id;
    char name[50];

    if (
        sscanf(
            line,
            "%d,%49[^\n]",
            &id,
            name) == 2)
    {

      locations[count] =
          create_location(
              id,
              name);

      count++;
    }
  }

  fclose(file);

  printf(
      "%d locations loaded successfully.\n",
      count);

  return count;
}