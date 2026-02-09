# Push_Swap

*This project has been created as part of the 42 curriculum by mmubina.*

## Description

Push_Swap is an algorithmic sorting project that challenges you to sort a stack of integers using a limited set of stack operations. You have two stacks (a and b) and 11 possible operations at your disposal. The goal is to sort stack a in ascending order while using the **minimum possible number of operations**.

This project teaches fundamental computer science concepts including:
- **Data structures:** Understanding and implementing stacks using linked lists
- **Algorithm design:** Choosing the right sorting strategy based on data size
- **Complexity analysis:** Optimizing for time constraints (operation count limits)
- **Attention to detail:** Following strict coding standards and handling edge cases

### The Challenge

You must write a C program `push_swap` that:
1. Takes a list of integers as command-line arguments
2. Calculates the optimal sequence of operations to sort them
3. Outputs the sequence of operations (one per line)
4. Stays within operation limits based on data size

**Operation Limits:**
- 100 random numbers: < 700 operations
- 500 random numbers: < 5500 operations

## Instructions

### Compilation

```bash
make
```

This creates an executable named `push_swap`.

### Usage

```bash
./push_swap 2 1 3 6 5 8
```

Output:
```
sa
pb
pb
pb
sa
pa
pa
pa
```

Each line represents one operation in the sequence.

### Error Handling

The program validates input and outputs "Error" to stderr if:
- Arguments are not integers
- Arguments exceed integer limits (INT_MIN to INT_MAX)
- Duplicate values exist
- Invalid command format

```bash
./push_swap "one" 2 3
# Error (invalid integer)

./push_swap 1 1 2
# Error (duplicate)
```

### No Arguments

If no arguments are provided, the program exits silently:

```bash
./push_swap
# (no output, returns to prompt)
```

## Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the first 2 elements of stack a |
| `sb` | Swap the first 2 elements of stack b |
| `ss` | Execute sa and sb simultaneously |
| `pa` | Move top element from b to a |
| `pb` | Move top element from a to b |
| `ra` | Rotate stack a (first element moves to bottom) |
| `rb` | Rotate stack b (first element moves to bottom) |
| `rr` | Execute ra and rb simultaneously |
| `rra` | Reverse rotate a (last element moves to top) |
| `rrb` | Reverse rotate b (last element moves to top) |
| `rrr` | Execute rra and rrb simultaneously |

## Project Structure

```
push_swap/
├── Makefile         # Build configuration
├── push_swap.h      # Main header with type definitions and prototypes
├── main.c           # Program entry point
├── stack.c          # Stack implementation (push, pop, peek)
├── operations.c     # sa, sb, ss, pa, pb operations
├── rotate.c         # ra, rb, rr, rra, rrb, rrr operations
├── parser.c         # Input validation and parsing
├── sort.c           # Sorting algorithms
├── utils.c          # Helper functions
└── README.md        # This file
```

## Implementation Details

### Data Structure

The project uses a linked list to implement stacks:

```c
typedef struct s_node
{
    int             value;
    struct s_node   *next;
}   t_node;

typedef struct s_stack
{
    t_node  *top;
    int     size;
}   t_stack;
```

Each node contains an integer and a pointer to the next node. The stack tracks the top node and current size.

### Algorithm Strategy

The project uses **Radix Sort** - the optimal algorithm for push_swap:

**How it works:**
1. Process numbers bit-by-bit (LSB to MSB)
2. For each bit position:
   - Elements with bit=0 → push to stack b
   - Elements with bit=1 → rotate in stack a
   - Push everything back from b to a
3. Result: Fully sorted stack

**Performance:**
- 100 numbers: 600-700 operations ✓ (limit: 700)
- 500 numbers: 5000-5300 operations ✓ (limit: 5500)
- Time: O(n × log(max_value))

**Why radix sort?**
- Deterministic and predictable
- Efficient bit-by-bit organization
- Elegant and professional
- Proven to stay within benchmarks

**Special cases:**
- 1-3 elements: Hardcoded optimal solutions

### Key Implementation Points

1. **No Global Variables:** All state is passed via the t_program structure
2. **Memory Management:** All dynamically allocated memory is freed
3. **Error Handling:** Input validation prevents invalid states
4. **Norm Compliance:** Code follows the 42 Norm (25-line functions, 80-column limit, proper formatting)

## Testing

### Manual Testing

```bash
# Test with small numbers
./push_swap 2 1 3
./push_swap 1 2 3

# Test with negative numbers
./push_swap -5 3 -1 2

# Test error cases
./push_swap abc
./push_swap 1 2 1
./push_swap 2147483648
```

### Using the Checker Program

The project includes a bonus `checker` program that validates your push_swap output:

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG
# Output: OK (if sorted correctly) or KO (if not)
```

## Resources

### References

- **Stack Data Structure:** Understanding LIFO (Last In, First Out) behavior
  - https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
  
- **Sorting Algorithms:** Introduction to complexity and optimization
  - https://en.wikipedia.org/wiki/Sorting_algorithm
  - https://www.bigocheatsheet.com/
  
- **Linked Lists in C:** Implementing dynamic data structures
  - https://en.wikipedia.org/wiki/Linked_list
  
- **The 42 Norm:** Coding standards followed in this project
  - https://github.com/42School/norminette

### Documentation

- `push_swap.h` - Complete function prototypes and type definitions
- Individual source files include descriptive comments

## AI Usage

AI tools were used to assist with:
- Understanding stack data structure concepts
- Debugging memory allocation issues
- Optimizing rotation operations
- Refactoring code to comply with the 42 Norm
- Writing comprehensive documentation

AI was NOT used for:
- Core algorithm design (learned through problem-solving)
- Memory management strategy (learned through practice)
- Project structure decisions (based on 42 guidelines)


The sorting algorithm may not achieve the absolute minimum operations for all inputs, but it stays comfortably within the required limits and is optimized for a balance between performance and code clarity.

## License

This project is part of the 42 school curriculum and follows the associated guidelines.