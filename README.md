# WarehouseOptimizer

A terminal-based warehouse optimization system built in C that helps select valuable packages within a given weight capacity and find optimal delivery routes between locations.

WarehouseOptimizer demonstrates the practical application of optimization algorithms, data structures, file handling, and modular programming through a single application.

## Overview

Warehouses often need to select packages while respecting storage or transportation capacity constraints. Delivery planning also requires finding efficient routes between multiple locations.

WarehouseOptimizer addresses these problems using classical optimization algorithms:

- **0/1 Knapsack using Dynamic Programming** to maximize the total value of selected packages within a weight limit.
- **Branch and Bound** to solve the package selection problem using a different optimization approach.
- **Travelling Salesman Problem (TSP)** to find a minimum-distance delivery route that visits the given locations and returns to the starting location.

The application provides a menu-driven terminal interface and uses CSV files to store package and location data between executions.

## Features

### 1. Package Management

Manage warehouse packages through the terminal interface.

- Add new packages.
- View all available packages.
- Update existing package details.
- Delete packages.
- Assign package IDs.
- Validate package weight and value.
- Store package information in a CSV file.

Each package contains the following information:

| Attribute | Description |
|---|---|
| ID | Unique identifier assigned to the package |
| Name | Package name |
| Weight | Package weight in kilograms |
| Value | Monetary or application-defined value of the package |

### 2. Knapsack Optimization

The application implements the 0/1 Knapsack problem using Dynamic Programming.

Given a collection of packages and a warehouse capacity, the algorithm selects a combination of packages that maximizes total value without exceeding the available capacity.

Each package can either be selected completely or excluded.

The optimization results include the selected packages, their total weight, and the maximum achievable value.

### 3. Branch and Bound Optimization

WarehouseOptimizer also implements the package selection problem using Branch and Bound.

The algorithm explores possible package combinations while using bounds to avoid exploring branches that cannot improve the current solution.

This provides an alternative approach to the Knapsack Dynamic Programming implementation.

### 4. Algorithm Comparison

The application provides a feature to compare the results of the Knapsack Dynamic Programming and Branch and Bound implementations.

This helps verify whether both algorithms identify the same optimal package value for a given input.

### 5. Delivery Route Optimization

The application implements the Travelling Salesman Problem (TSP) to find a minimum-distance route among the available locations.

The program accepts distances between location pairs and calculates a route that visits the locations and returns to the starting point.

The output includes the selected route and its total distance.

The current implementation uses a brute-force approach to examine possible routes.

### 6. CSV-Based Data Persistence

Package and location information is stored using CSV files.

The application loads existing data when it starts and saves changes when the user exits through the application menu.

This allows package and location information to persist between executions without requiring a database.

### 7. Input Validation

The application includes input validation for important package-management operations, including checks for invalid package IDs and non-positive package weights.

It also rejects negative package values.

## Algorithms Used

| Algorithm | Purpose | General Complexity |
|---|---|---|
| 0/1 Knapsack — Dynamic Programming | Maximize package value within a capacity limit | O(nW) time and O(nW) space for the standard 2D implementation |
| Branch and Bound | Optimize package selection by exploring and pruning candidate solutions | Worst-case exponential; depends on the implementation and input |
| Travelling Salesman Problem — Brute Force | Find a minimum-distance route through all locations | O(n!) time, with route-evaluation overhead depending on the implementation |

Here, `n` represents the number of packages or locations, and `W` represents the capacity in the Knapsack problem's chosen integer units.

The Dynamic Programming complexity assumes the standard capacity-indexed implementation. Actual complexity depends on the implementation details.

The TSP brute-force approach is suitable for a small number of locations because the number of possible routes grows factorially.

## Technology Stack

- **Programming Language:** C
- **Compiler:** GCC
- **Interface:** Command-line / terminal
- **Data Storage:** CSV files
- **Version Control:** Git and GitHub

## Project Structure

```text
WarehouseOptimizer/
├── src/
│   ├── main.c
│   ├── models/
│   │   ├── package.c
│   │   ├── warehouse.c
│   │   └── location.c
│   ├── algorithms/
│   │   ├── knapsack.c
│   │   ├── branch_bound.c
│   │   ├── algorithm_comparison.c
│   │   └── tsp.c
│   └── utils/
│       ├── input.c
│       └── file_handler.c
├── include/
│   ├── package.h
│   ├── warehouse.h
│   ├── location.h
│   ├── knapsack.h
│   ├── branch_bound.h
│   ├── algorithm_comparison.h
│   ├── tsp.h
│   ├── input.h
│   └── file_handler.h
├── data/
│   ├── packages.csv
│   └── locations.csv
├── tests/
│   ├── test_knapsack.c
│   ├── test_branch_bound.c
│   └── test_tsp.c
├── docs/
├── .gitignore
└── README.md
```

The structure separates the application into logical components:

- **`src/main.c`** contains the main menu and application flow.
- **`src/models/`** contains the package, warehouse, and location models.
- **`src/algorithms/`** contains the optimization algorithm implementations.
- **`src/utils/`** contains input-handling and file-handling utilities.
- **`include/`** contains header files declaring shared structures and functions.
- **`data/`** contains the CSV files used for persistent data storage.
- **`tests/`** contains tests for the optimization algorithms.
- **`docs/`** is reserved for project documentation.

## Requirements

To compile and run the application, you need:

- Windows, Linux, or another compatible operating system.
- GCC or a compatible C compiler.
- A terminal or command-line interface.

The commands below use Windows PowerShell.

## Installation and Setup

### 1. Clone the repository

```bash
git clone https://github.com/yashcodesit/warehouse-optimizer.git
```

### 2. Open the project directory

```bash
cd warehouse-optimizer
```

### 3. Compile the application

Run the following command from the project root:

```bash
gcc src/main.c src/models/package.c src/models/warehouse.c src/models/location.c src/algorithms/knapsack.c src/algorithms/branch_bound.c src/algorithms/algorithm_comparison.c src/algorithms/tsp.c src/utils/input.c src/utils/file_handler.c -o warehouse_optimizer.exe -lm
```

### 4. Run the application

```powershell
.\warehouse_optimizer.exe
```

Enter the warehouse capacity when prompted. The application then loads the available package and location data and displays the main menu.

**Important:** Run the application from the project root so the relative paths to the CSV files resolve correctly.

## Application Menu

The application currently provides the following options:

```text
================================
       WAREHOUSE OPTIMIZER
================================

1. Add Package
2. View All Packages
3. Update Package
4. Delete Package
5. Optimize Package Selection
6. Optimize Using Branch & Bound
7. Compare Knapsack Algorithms
8. Find Shortest Delivery Route
9. Exit
```

The menu allows users to manage packages, run optimization algorithms, calculate delivery routes, and exit the application.

Package and location data are saved when the application exits through the Exit menu option.

## Testing

The project includes test source files for its optimization algorithms:

- `tests/test_knapsack.c`
- `tests/test_branch_bound.c`
- `tests/test_tsp.c`

The tests cover scenarios such as empty inputs, packages exceeding capacity, optimal package combinations, and delivery routes with multiple locations.

The test files are compiled separately from the main application because each test program has its own entry point.

## Design Approach

WarehouseOptimizer follows a modular design.

Models, algorithms, input handling, and file operations are separated into different source files. Header files expose the structures and functions needed by other modules.

This approach improves code organization, makes individual components easier to understand, and supports independent testing of the algorithms.

The project also demonstrates how multiple algorithmic approaches can be applied to related optimization problems within one application.

## Current Limitations

The current version intentionally focuses on a terminal-based implementation.

- Package and location information is stored in CSV files rather than a database.
- Delivery distances are entered manually when calculating a route.
- The brute-force TSP implementation is intended for relatively small location sets.
- Algorithm comparison currently focuses on comparing optimization results rather than providing a comprehensive performance benchmark.
- The application does not currently include a graphical interface or web API.

These limitations define the scope of the current version and provide opportunities for future development.

## Future Improvements

Possible future enhancements include:

- Comparing algorithm execution times on larger datasets.
- Persisting delivery distances in a file.
- Improving route optimization for larger location sets.
- Adding more comprehensive input and file-error handling.
- Providing additional optimization reports.
- Developing a graphical interface if required.

These enhancements are not part of the current implementation.

## Learning Outcomes

This project provides practical experience with:

- C programming and modular software design.
- Structures, arrays, and functions.
- File handling and CSV-based persistence.
- Dynamic Programming.
- Branch and Bound.
- Combinatorial optimization.
- The Travelling Salesman Problem.
- Algorithm testing and result verification.
- Git-based version control.

## Author

**Yash Shukla**

GitHub: [yashcodesit](https://github.com/yashcodesit)

## License

No license has been specified for this repository yet. If you intend to distribute the project for reuse, consider adding an appropriate open-source license.