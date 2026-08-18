# CS509 - PG Software Lab (Individual Assignments) Repository

---

## Student Information

- **Course:** CS509 – PG Software Lab
- **Assignment:** Assignment 1 
- **Mode of Assignment:** Individual
- **Name:** Chiranton Baruah
- **Entry Number:** 2026CSM1009

---

# CS509 – Assignment 1 (Individual Category)

---

# Objective

This assignment implements two fundamental data structures/algorithms:

1. General Matrix-Matrix Multiplication (GEMM)
2. Compressed Sparse Row (CSR) Graph Representation

Both implementations are written in C++17 and executed through a common menu-driven driver.

---

# Directory Structure

```
assignment_01/
│
├── driver/
│   └── driver.cpp
│
├── include/
│   ├── gemm.h
│   └── csr.h
│
├── src/
│   ├── gemm_simple.cpp
│   ├── gemm_blocking.cpp
│   ├── csr.cpp
│   └── graph_reader.cpp
│
├── tests/
│   ├── gemm_*.txt
│   └── csr_*.txt
│
│
└── Makefile
```

---

# Compilation

Compile the project using:

```bash
make
```

Remove the executable using:

```bash
make clean
```

---

# Running

Execute:

```bash
./assignment1
```

---

# Menu

```
======================================
      CS509 Assignment 1
======================================
1. GEMM (Simple + Blocking)
2. CSR Graph Conversion
0. Exit

Enter choice:
```

---

# Task 1 — General Matrix-Matrix Multiplication (GEMM)

## Implementations

Two implementations are provided.

### 1. Simple GEMM

A straightforward triple-nested loop implementation.

Time Complexity:

```
O(MKN)
```

---

### 2. Blocked GEMM

A cache-aware implementation using fixed-size blocks to improve memory locality.

Advantages:

- Better cache utilization
- Reduced cache misses
- Improved execution time for larger matrices

Current block size:

```
32 × 32
```

---

# GEMM Input Format

Input files contain:

```
M K N

Matrix A

Matrix B
```

Example:

```
2 3 2

1 2 3
4 5 6

7 8
9 10
11 12
```

---

# GEMM Output

For each implementation:

- Result matrix
- Execution time (milliseconds)

---

# Task 2 — CSR Graph Representation

The graph is initially supplied as an adjacency list and converted into Compressed Sparse Row (CSR) format.

The implementation supports:

- Unweighted graphs
- Weighted graphs

---

# Graph Input Format

First line:

```
Vertices Edges Weighted
```

where

- Weighted = 0 → Unweighted
- Weighted = 1 → Weighted

---

## Unweighted Example

```
5 6 0
0 1 2
1 0 3
2 0 4
3 1
4 2
```

---

## Weighted Example

```
5 6 1
0 1 5 2 3
1 2 8
2 3 1
3 4 2
4
```

Each edge is stored as

```
destination weight
```

---

# CSR Output

The program displays

- Number of vertices
- Number of edges
- Row Pointer array
- Column Index array
- Weight array (weighted graphs only)
- CSR conversion time

---

# Test Cases

The following graph sizes were prepared according to the assignment specification.

| Test File | Vertices | Graph Type |
|------------|---------:|------------|
| csr_10.txt | 10 | Connected sparse graph |
| csr_100.txt | 100 | Chain graph |
| csr_10000.txt | 10000 | Sparse graph |
| csr_50000.txt | 50000 | Sparse graph |
| csr_100000.txt | 100000 | Sparse graph |

The following GEMM test files are included.

| Test File | Matrix Size |
|------------|------------|
| gemm_test_01.txt | 2 x 3 and 3 x 2 |
| gemm_test_02.txt | 99 x 99 and 99 x 99 |
| gemm_test_03.txt | 70 x 80 and 80 x 90 |
| gemm_test_04.txt | 20 x 25 and 25 x 30 |
| gemm_test_05.txt | 200 x 205 and 205 x 210 |

---

# Performance Measurement

Execution times are measured using

```
std::chrono::high_resolution_clock
```

Reported timings are in milliseconds.

| Test File | Vertices (V) | Edges (E) | Graph Type | Conversion Time (ms) |
|-----------|-------------:|----------:|------------|---------------------:|
| csr_10.txt | 10 | 12 | Connected Sparse | 0.005234 |
| csr_100.txt | 100 | 99 | Chain | 0.003838 |
| csr_10000.txt | 10000 | 9999 | Chain | 0.275331 |
| csr_50000.txt | 50000 | 49999 | Chain | 24.5791 |
| csr_100000.txt | 100000 | 99999 | Chain | 24.6112 |

| Test File | Matrix Size | Simple GEMM (ms) | Blocked GEMM (ms) |
|-----------|------------:|-----------------:|------------------:|
| gemm_test_01.txt | 2 x 3 and 3 x 2 | 0.002371 | 0.001847 |
| gemm_test_02.txt | 99 x 99 and 99 x 99 | 0.815193 | 0.938234 |
| gemm_test_03.txt | 70 x 80 and 80 x 90 | 0.937587 | 0.96552 |
| gemm_test_04.txt | 20 x 25 and 25 x 30 | 0.026406 | 0.041937 |
| gemm_test_05.txt | 200 x 205 and 205 x 210 | 6.77056 | 12.4146| 

---

# Software Requirements

- C++17
- GNU g++
- GNU Make
- Linux / WSL2

---

# References

1. CS509 PG Software Lab – Assignment 1 Specification
2. C++17 Standard Library Documentation
3. GNU Compiler Collection (GCC)

# Assignment 02 - Shortest Path Algorithms (Individual)

## Assignment Mode

**Individual**

## Objective

Implement and evaluate the following shortest-path algorithms:

- **Bellman-Ford** (single-source shortest path on directed weighted graphs with possible negative edge weights)
- **Floyd-Warshall** (all-pairs shortest path on weighted graphs)

The assignment follows the CS509 Assignment 2 specification and the CS509 Lab Work Guidelines.

---

## Algorithms / Approach

### Bellman-Ford

- Input graph is read as a **directed weighted adjacency list**.
- The adjacency list is converted to **CSR (Compressed Sparse Row)** format before execution.
- The algorithm relaxes all edges **V-1 times** and performs one additional pass to detect a reachable negative-weight cycle.
- Distances are stored using `long long`.

**Complexity**

- Time: **O(V * E)**
- Space: **O(V + E)**

### Floyd-Warshall

- Input graph is read as a **V × V adjacency matrix**.
- `INF` denotes the absence of a direct edge.
- The algorithm uses the standard dynamic-programming update:

`dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`

- A negative cycle is detected if any diagonal entry becomes negative after the algorithm finishes.

**Complexity**

- Time: **O(V^3)**
- Space: **O(V^2)**

---

## Input Format

### Bellman-Ford

```text
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 ...
...
SOURCE s
```

### Floyd-Warshall

```text
V
row0
row1
...
row(V-1)
```

Use `INF` for missing edges.

---

## Helper Functions / CSR Conversion

The CSR conversion is implemented in:

- `include/csr_graph.hpp`

This conversion is **preprocessing** and is **not included in the reported execution time**, as required by the assignment.

---

## File Structure

```text
assignment_02/
├── Makefile
├── include/
│   ├── csr_graph.hpp
│   ├── bellman_ford.hpp
│   ├── floyd_warshall.hpp
│   ├── bf_runner.hpp
│   ├── fw_runner.hpp
│   └── test_utils.hpp
├── driver/
│   └── assignment_02_driver.cpp
├── tests/
│   ├── bellman_ford/
│   └── floyd_warshall/
├── tools/
│   ├── generate_bf_graph.cpp
│   └── generate_fw_matrix.cpp
└── bin/
```

### Description

- `include/` - Core algorithms and helper modules.
- `driver/` - Assignment 02 menu driver.
- `tests/` - Input test files.
- `tools/` - Optional graph/matrix generators (not part of the build).
- `bin/` - Generated executables.

---

## Compilation

From the `assignment_02` directory:

```bash
make
```

This builds:

```text
bin/assignment_02_driver
```

---

## Execution

### Run the assignment menu

```bash
make run
```

or

```bash
./bin/assignment_02_driver
```

### Menu options

```text
1. Run Bellman-Ford (one file)
2. Run Floyd-Warshall (one file)
3. Run all Bellman-Ford tests
4. Run all Floyd-Warshall tests
0. Exit
```

---

## Running a Single Test

### Bellman-Ford

```text
tests/bellman_ford/bf_10.txt
```

### Floyd-Warshall

```text
tests/floyd_warshall/fw_10.txt
```

---

## Running All Tests

- Option **3** runs all files inside `tests/bellman_ford/`.
- Option **4** runs all files inside `tests/floyd_warshall/`.

Files are discovered automatically using `std::filesystem`.

---

## Runtime Measurement

Only the **algorithm execution time** is measured.

The following are **outside the timed region**:

- file reading,
- input parsing,
- adjacency-list construction,
- CSR conversion,
- output formatting,
- output printing.

Timing is performed using:

```cpp
std::chrono::high_resolution_clock
```

The reported unit is **seconds (s)**.

---

## Build Environment

- **Language:** C++17
- **Compiler:** g++
- **Flags:** `-std=c++17 -O2 -Wall -Wextra`

---

## Test Cases and Result Tables

### Bellman-Ford Results

| Mode | Test File | Input Type | Input Size | Expected Output | Algorithm Time (seconds) |
|------|-----------|------------|------------|-----------------|----------------|
| Single | bf_10.txt | Directed weighted adjacency list → CSR | V=10, E=40 | Distances / no negative cycle | 0.006 |
| Single | bf_100.txt | Directed weighted adjacency list → CSR | V=100, E=2500 | Distances / no negative cycle | 0.083 |
| Single | bf_10000.txt | Directed weighted adjacency list → CSR | V=10000, E=30000 | Distances / no negative cycle | 0.679 |
| Single | bf_50000.txt | Directed weighted adjacency list → CSR | V=50000, E=150000 | Distances / no negative cycle | 0.991 |
| Single | bf_100000.txt | Directed weighted adjacency list → CSR | V=100000, E=300000 | Distances / no negative cycle | 2.999 |

### Floyd-Warshall Results

| Mode | Test File | Input Type | Input Size | Expected Output | Algorithm Time (seconds) |
|------|-----------|------------|------------|-----------------|----------------|
| Single | fw_10.txt | Adjacency matrix | 10 × 10 | Distance matrix | 0.005 |
| Single | fw_100.txt | Adjacency matrix | 100 × 100 | Distance matrix | 0.031 |
| Single | fw_500.txt | Adjacency matrix | 500 × 500 | Distance matrix | 0.187 |
| Single | fw_1000.txt | Adjacency matrix | 1000 × 1000 | Distance matrix | 0.550 |
| Single | fw_2000.txt | Adjacency matrix | 2000 × 2000 | Distance matrix | 2.481 |

---

## Cross-Check (Required)

For the graph sizes where both algorithms are required (**10 and 100 vertices**):

- Bellman-Ford is executed from **every source vertex**.
- The resulting distance vectors are compared with the corresponding rows of the Floyd-Warshall distance matrix.
- Any mismatch is treated as a validation failure.

---

## Tools

The `tools/` directory contains optional generators:

- `generate_bf_graph.cpp`
- `generate_fw_matrix.cpp`

These files are compiled separately and not by Makefile.

---

## References

- CS509 Assignment 2 Specification
- CS509 Lab Work Guidelines
- T. H. Cormen et al., *Introduction to Algorithms* (Bellman-Ford and Floyd-Warshall)

# Assignment 03 - Minimum Spanning Tree (Individual)

## Assignment Mode

**Individual**

## Objective

Implement and evaluate two Minimum Spanning Tree (MST) algorithms for weighted, undirected graphs:

- **Kruskal's Algorithm**
- **Prim's Algorithm**

Both algorithms are executed on the same graph inputs and their MST results are compared. The total MST weight produced by both algorithms must match.

The graph input is provided as an adjacency list and converted to **Compressed Sparse Row (CSR)** format before algorithm execution. CSR conversion is treated as preprocessing and is excluded from the reported algorithm execution time.

## Algorithm / Approach

### Kruskal's Algorithm

Kruskal's algorithm constructs the MST by:

1. Sorting all graph edges in non-decreasing order of weight.
2. Processing the edges in sorted order.
3. Adding an edge only when it does not form a cycle.
4. Using a Disjoint Set Union (DSU/Union-Find) structure for cycle detection.
5. Stopping after `V - 1` edges have been selected.

**Time Complexity:** `O(E log E)`

**Space Complexity:** `O(V + E)`

### Prim's Algorithm

Prim's algorithm constructs the MST by:

1. Starting from vertex `0`.
2. Maintaining the set of vertices already included in the MST.
3. Repeatedly selecting the minimum-weight edge connecting the current tree to an unvisited vertex.
4. Continuing until all vertices are included.

A minimum-priority queue is used for efficient minimum-edge selection.

**Time Complexity:** `O(E log V)`

**Space Complexity:** `O(V + E)`

## Input Format

MST test files use a weighted, undirected adjacency-list representation:

```text
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 ...
...
u(V-1) degree neighbor1 weight1 ...
```

Where:

- `V` = number of vertices.
- `E` = number of undirected edges.
- Each undirected edge appears in the adjacency list of both endpoint vertices.
- Each edge has the same weight in both adjacency lists.
- The graph must be connected.
- Vertex numbering follows the `0` to `V-1` convention.

The same input file is used for both Kruskal's and Prim's algorithms.

## Helper Functions / CSR Conversion

The adjacency-list graph is converted into **CSR (Compressed Sparse Row)** format before either MST algorithm is executed.

The CSR representation consists of:

- `row_ptr`
- `col_idx`
- Edge `values` / weights

CSR conversion is preprocessing and is **not included in the reported algorithm execution time**.

## File Structure

```text
assignment_03/
├── include/
├── driver/
├── tests/
│   ├── mst_10.txt
│   ├── mst_100.txt
│   ├── mst_10000.txt
│   ├── mst_50000.txt
│   └── mst_100000.txt
├── generator/
└── bin/
```

## Compilation

From the `assignment_03` directory:

```bash
make
```

## Execution

Run the Assignment 03 driver using:

```bash
make run
```

or execute the generated driver directly:

```bash
./bin/assignment_03_driver
```

The driver executes both Kruskal's and Prim's algorithms on the selected MST test graph and reports the selected MST edges, total MST weight, and algorithm execution time.

## Test Cases and Result Table

The Assignment 3 specification requires MST tests with **10, 100, 10,000, 50,000, and 100,000 vertices**, using the same graph files for both algorithms.

| Mode | Test File | Input Type | Input Size | Expected Output | Actual Output | Kruskal Time (ms) | Prim Time (ms) |
|------|-----------|------------|------------|-----------------|---------------|------------------:|---------------:|
| Single | `mst_10.txt` | Weighted undirected adjacency list → CSR | V=10 | Valid MST; weight = 2613 | Kruskal = 2613, Prim = 2613 — MATCH | 0.004197 | 0.002775 |
| Single | `mst_100.txt` | Weighted undirected adjacency list → CSR | V=100 | Valid MST; weight = 18179 | Kruskal = 18179, Prim = 18179 — MATCH | 0.024177 | 0.020100 |
| Single | `mst_10000.txt` | Weighted undirected adjacency list → CSR | V=10,000 | Valid MST; weight = 1993206 | Kruskal = 1993206, Prim = 1993206 — MATCH | 3.300930 | 3.281290 |
| Single | `mst_50000.txt` | Weighted undirected adjacency list → CSR | V=50,000 | Valid MST; weight = 9870550 | Kruskal = 9870550, Prim = 9870550 — MATCH | 20.620400 | 21.143200 |
| Single | `mst_100000.txt` | Weighted undirected adjacency list → CSR | V=100,000 | Valid MST; weight = 19713150 | Kruskal = 19713150, Prim = 19713150 — MATCH | 39.781700 | 42.438400 |

The recorded report shows matching MST weights for all five test cases. 
## Correctness Check

For every test case:

- Both algorithms produced a valid MST.
- The total MST weight produced by Kruskal's algorithm and Prim's algorithm was identical.
- The driver reported **`MST weight comparison: MATCH`** for all five test cases.
- Different MST edge sets are permitted when multiple valid MSTs exist, provided the total minimum weight is identical.

## Runtime Measurement

Only the **algorithm execution time** is measured.

The following operations are excluded from the timed region:

- Input file reading
- Input parsing
- Adjacency-list construction
- Adjacency-list-to-CSR conversion
- Output formatting
- Output printing

The timer starts immediately before the MST algorithm is called and stops immediately after the algorithm completes, as required by the Assignment 3 specification.

## References

1. CS509 Assignment 3 Specification
2. CS509 Lab Work Guidelines
3. Princeton Algorithms — Minimum Spanning Trees
4. Standard algorithms and data-structure references for Kruskal's Algorithm, Prim's Algorithm, and Disjoint Set Union
