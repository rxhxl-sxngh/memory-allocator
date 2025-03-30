# Custom Memory Allocator

A lightweight, efficient memory allocation system implemented in C that provides an alternative to the standard library's memory management functions.

## Overview

This project implements a custom memory allocator that manages heap memory, complete with memory block splitting, coalescing, and different allocation strategies. It provides replacements for the standard `malloc()`, `calloc()`, `realloc()`, and `free()` functions, with a focus on efficiency and robustness.

The allocator uses a linked list of free blocks to manage available memory and implements the Next Fit allocation strategy to improve performance and memory utilization.

## Features

- **Next Fit Allocation Strategy**: Starts searching for free memory from where the last allocation ended, improving performance for programs with localized allocation patterns.
- **Memory Block Splitting**: Efficiently divides large free blocks to minimize wasted space.
- **Block Coalescing**: Combines adjacent free blocks to prevent memory fragmentation.
- **Double-Free Protection**: Detects and safely handles attempts to free the same memory multiple times.
- **Memory Corruption Detection**: Uses magic numbers to identify invalid memory operations.
- **Memory Alignment**: Ensures all allocations are properly aligned for optimal performance.

## Implementation Details

The allocator includes the following core functions:

- `tumalloc(size_t size)`: Allocates memory of specified size.
- `tucalloc(size_t num, size_t size)`: Allocates and initializes memory to zero.
- `turealloc(void *ptr, size_t new_size)`: Reallocates memory to a new size.
- `tufree(void *ptr)`: Frees allocated memory.

Additional helper functions include:

- `split()`: Divides free blocks when needed.
- `coalesce()`: Combines adjacent free blocks.
- `find_prev()`/`find_next()`: Locates neighboring memory blocks.
- `remove_free_block()`: Removes blocks from the free list.
- `do_alloc()`: Requests memory from the operating system via `sbrk()`.

## Building and Testing

To compile:
```bash
./build.sh
```

This will create a build directory and compile the project using CMake.

To run the test program:
```bash
cd build
./custom_allocator
```

The test program exercises various aspects of the memory allocator including:
- Simple allocations and frees
- Linked list operations using the allocator
- Zero-initialized memory allocation
- Memory reallocation

## Technical Challenges

Developing this allocator required solving several technical challenges:

1. **Efficient Free List Management**: Maintaining a linked list of free blocks that can be quickly searched and updated.
2. **Memory Fragmentation**: Implementing strategies to minimize internal and external fragmentation.
3. **Edge Cases**: Handling special cases such as zero-sized allocations and NULL pointer arguments.
4. **Double-Free Prevention**: Detecting when memory is freed multiple times to prevent corruption.
5. **Memory Layout**: Designing the memory block structure with headers to track allocation information.

## Future Improvements

Potential enhancements to the allocator include:

- Implementing Best Fit and Worst Fit allocation strategies
- Adding thread safety for multi-threaded applications
- Optimizing the free list search with additional data structures
- Implementing boundary tags for more efficient coalescing
- Adding debugging features for memory leak detection

## License

This project is open source and may be freely used and modified.