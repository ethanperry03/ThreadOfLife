# Parallel Game of Life with Pthreads

## Overview
This project implements a parallel version of Conway's Game of Life in C using the pthreads library. It focuses on shared-memory parallelization, synchronization, and scalability analysis. The project builds upon a sequential implementation and introduces multi-threading to enhance performance.

## Features
- Parallel execution using pthreads.
- Row-wise or column-wise grid partitioning.
- Synchronization using mutexes and barriers.
- Performance measurement and debugging with GDB and Valgrind.
- Configurable number of threads for scalability testing.

## Compilation & Execution
### Build
```sh
make
```

### Run
```sh
./gol <input_file> <num_threads> <partition_method> <wrap|nowrap> <show|hide> [slow|med|fast]
```
#### Examples
```sh
./gol file1.txt 8 row wrap hide
./gol file2.txt 15 col nowrap show fast
```

## Implementation Details
The project is structured as follows:
- `gol.c`: Initializes the game board, manages threads, and runs the simulation.
- `gol_parallel.c`: Contains the logic for multi-threaded execution.
- `gol_io.c`: Handles file I/O and board printing.

### Parallelization Strategy
- The grid is partitioned either row-wise or column-wise among threads.
- Each thread updates its assigned portion of the grid in parallel.
- Mutexes and barriers ensure correct synchronization between threads.

### Synchronization
- A barrier ensures all threads complete a round before proceeding.
- A designated printing thread handles board output to avoid interleaved prints.
- Global counters track live cell counts across threads safely.

### Timing Execution
The `gettimeofday` function is used to measure the execution time of the simulation.

## Debugging
Use GDB and Valgrind to debug memory errors:
```sh
gdb ./gol
valgrind --leak-check=full ./gol file.txt 8 row wrap hide
```

## Code Style & Best Practices
- No global variables; use function parameters.
- Functions should ideally be ≤ 20 lines.
- Use `malloc()` for dynamic memory allocation.
- Handle file errors gracefully.
- Ensure proper synchronization to avoid race conditions.

## Additional Notes
- `CTRL+C` terminates an infinite loop.
- Validate command-line arguments before execution.
- Ensure proper cleanup of threads and dynamically allocated memory.

Happy coding!
