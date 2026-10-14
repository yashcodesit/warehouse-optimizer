# WarehouseOptimizer

A C-based warehouse optimization system that uses classic algorithms to maximize package value under weight constraints and find efficient delivery routes.

## Overview

WarehouseOptimizer helps manage warehouse packages and solve two optimization problems:

- **Package Selection:** Select the most valuable combination of packages without exceeding the warehouse's weight capacity.
- **Delivery Route Optimization:** Find the shortest round-trip route that visits a set of locations and returns to the starting point.

The project demonstrates the practical application of data structures, algorithms, modular programming, input validation, and file handling in C.

## Features

- Add and view warehouse packages.
- Assign package IDs automatically.
- Optimize package selection using 0/1 Knapsack with Dynamic Programming.
- Solve the same problem using Branch and Bound.
- Compare the results of both Knapsack algorithms.
- Find a short delivery route using the Travelling Salesperson Problem (TSP).
- Validate user input.
- Save and load package and location data using CSV files.
- Test algorithms using separate test programs.

## Algorithms Used

### 1. 0/1 Knapsack — Dynamic Programming

Select packages to maximize total value while keeping their combined weight within the capacity limit.

**Time Complexity:** O(nW)  
**Space Complexity:** O(nW)

Here, `n` is the number of packages and `W` is the capacity represented in the algorithm's weight units.

### 2. 0/1 Knapsack — Branch and Bound

Explores possible package selections and uses an upper-bound estimate to prune branches that cannot improve the current best solution.

**Worst-case Time Complexity:** O(2^n)

### 3. Travelling Salesperson Problem — Brute Force

Evaluates possible delivery routes to find the minimum-distance round trip for the provided distance matrix.

**Time Complexity:** O(n!)

The factorial complexity makes this approach suitable primarily for small numbers of locations.

## Tech Stack

- **Language:** C
- **Compiler:** GCC
- **Data Storage:** CSV files
- **Testing:** Separate C test programs

## Project Structure

```text
WarehouseOptimizer/
├── include/       # Header files
├── src/
│   ├── models/    # Package, warehouse, and location models
│   ├── algorithms/# Optimization algorithms
│   ├── utils/     # Input handling and file operations
│   └── main.c     # Application entry point
├── tests/         # Algorithm test programs
├── data/          # CSV data files
└── README.md
```

## Getting Started

### Prerequisites

- GCC compiler
- Windows PowerShell or a compatible terminal

### Compile the Application

Run the following command from the project root directory:

```powershell
gcc src/main.c src/models/package.c src/models/warehouse.c src/models/location.c src/algorithms/knapsack.c src/algorithms/branch_bound.c src/algorithms/algorithm-comparision.c src/algorithms/tsp.c src/utils/input.c src/utils/file_handler.c -o warehouse_optimizer.exe -lm
```

### Run the Application

```powershell
.\warehouse_optimizer.exe
```

Follow the menu displayed by the application to manage packages and run the optimization algorithms.

## Running Tests

Compile and run the Knapsack tests:

```powershell
gcc tests/test_knapsack.c src/algorithms/knapsack.c src/models/package.c src/models/warehouse.c -o test_knapsack.exe -lm
.\test_knapsack.exe
```

Compile and run the Branch and Bound tests:

```powershell
gcc tests/test_branch_bound.c src/algorithms/branch_bound.c src/models/package.c src/models/warehouse.c -o test_branch_bound.exe -lm
.\test_branch_bound.exe
```

Compile and run the TSP tests:

```powershell
gcc tests/test_tsp.c src/algorithms/tsp.c -o test_tsp.exe
.\test_tsp.exe
```

## Learning Objectives

This project demonstrates:

- Dynamic programming
- Branch and Bound
- Combinatorial optimization
- Travelling Salesperson Problem
- Modular C programming
- Input validation
- CSV-based persistence
- Algorithm testing and comparison

## Future Improvements

- Add a graphical user interface.
- Improve scalability for larger datasets.
- Add more comprehensive edge-case tests.
- Improve delivery-route optimization for larger numbers of locations.
- Add performance measurements to compare algorithm execution times.

## Author

Developed as a software engineering and algorithmic optimization project.