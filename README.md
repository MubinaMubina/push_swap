*This project has been created as part of the 42 curriculum by mmubina.*

# push_swap

## Description

**push_swap** is a sorting algorithm project from the 42 school curriculum. The goal is to sort a stack of integers using two stacks (`a` and `b`) and a restricted set of operations, while producing the **smallest possible number of instructions**.

The available operations are:

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the top 2 elements of stack a |
| `sb` | Swap the top 2 elements of stack b |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push top of stack b onto stack a |
| `pb` | Push top of stack a onto stack b |
| `ra` | Rotate stack a upward (first becomes last) |
| `rb` | Rotate stack b upward (first becomes last) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate stack a (last becomes first) |
| `rrb` | Reverse rotate stack b (last becomes first) |
| `rrr` | `rra` and `rrb` simultaneously |

### Algorithm

- **2–5 elements**: hand-coded optimal routines for each case
- **6+ elements**: radix sort on coordinate-compressed indices

### Performance (average)

| Input size | Operations |
|------------|------------|
| 100 numbers | ~855 |
| 500 numbers | ~5740 |

---

## Instructions

### Compilation

```bash
make        # build push_swap
make clean  # remove object files
make fclean # remove object files and binary
make re     # full rebuild
```

### Usage

```bash
# Multiple arguments
./push_swap 4 67 3 87 23

# Single quoted string
./push_swap "4 67 3 87 23"

# Verify with checker
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker_linux $ARG
```

### Error cases

The program prints `Error` to stderr and exits for:
- Non-integer arguments
- Arguments exceeding `INT_MAX` / `INT_MIN`
- Duplicate values

---

## Resources

- [Radix sort explanation](https://en.wikipedia.org/wiki/Radix_sort)
- [Push_swap visualizer](https://github.com/o-reo/push_swap_visualizer)
- [42 push_swap community guide](https://medium.com/@jamierobertdawson/push-swap-the-least-number-of-moves-with-two-stacks-d1e76a71789a)

### AI usage

Claude Code (Anthropic) was used during this project for:
- Reviewing code for bugs (duplicate detection logic, input validation edge cases)
- Fixing identified bugs (exit code handling, no-argument behaviour)
- Fixing test script issues (valgrind output capture, exit code assertions)

All AI-generated suggestions were reviewed, understood, and validated before being applied.
