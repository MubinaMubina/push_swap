# Complete Array-Based Implementation Package

## All Files Needed

I'll provide you with all 10 key files updated for the array-based approach.

Since each file is substantial, I've organized them below in a structured way for you to copy directly.

---

## File 1: push_swap.h

```c
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>

typedef struct s_stack
{
	int	*a;
	int	*b;
	int	size_a;
	int	size_b;
}	t_stack;

/* Main functions */
int		main(int argc, char **argv);

/* Initialization */
int		initialize_stack(int argc, char **argv, t_stack *stack, char **args);
void	convert_to_indices(t_stack *arr);
void	special_init(char *str, t_stack *stack);

/* Validation */
int		parse_and_validate(t_stack *arr, int argc);
int		validate_no_duplicates(t_stack *arr, int argc);
int		validate_range(t_stack *arr, int argc);
int		validate_arguments(int argc, char **argv);
int		validate_format(char **a);
int		ft_atoi_wcheck(char *str, t_stack *stack, char **args);

/* Stack operations - Stack A */
int		sa(t_stack *stack);
int		ra(t_stack *stack);
int		rra(t_stack *stack);
int		pa(t_stack *arr);

/* Stack operations - Stack B */
int		rb(t_stack *stack);
int		pb(t_stack *arr);

/* Sorting */
void	sort_stack(t_stack *arr);
void	sort_small_stack(t_stack *arr);
void	sort_three_elements(t_stack *arr);
void	sort_four_elements(t_stack *arr);
void	sort_five_elements(t_stack *arr);
void	radix_sort(t_stack *arr);
void	radix_sort_b(t_stack *arr, int size, int bit_size, int bit);
int		get_max_bits(int n);

/* Utilities */
int		is_sorted(t_stack *arr);
void	free_stacks(t_stack *arr);
void	free_split(char **split);

/* LibFt functions (implement or include from libft) */
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);

#endif
```

---

## File 2: main.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Main entry point
*/

#include "push_swap.h"

static int	init_and_validate(int argc, char **argv, t_stack **arr)
{
	*arr = (t_stack *)malloc(sizeof(t_stack));
	if (!*arr)
		return (write(2, "Error\n", 6));
	if (argc == 2)
		special_init(argv[1], *arr);
	else
		initialize_stack(argc - 1, argv, *arr, NULL);
	if (parse_and_validate(*arr, (*arr)->size_a + 1) != 0)
	{
		free_stacks(*arr);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack	*arr;

	if (argc < 2 || argv[1][0] == '\0')
		return (write(2, "Error\n", 6));
	if (argv[1][0] == ' ' && argv[1][1] == '\0')
		return (write(2, "Error\n", 6));
	if ((!validate_arguments(argc, argv) && argc > 2)
		|| validate_format(argv) == 0)
		return (write(2, "Error\n", 6));
	if (init_and_validate(argc, argv, &arr) != 0)
		return (1);
	if (!is_sorted(arr))
		convert_to_indices(arr);
	if (arr->size_a <= 5)
		sort_small_stack(arr);
	else
		radix_sort(arr);
	free_stacks(arr);
	return (0);
}
```

---

## File 3: stack_init.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Stack initialization
*/

#include "push_swap.h"

int	initialize_stack(int argc, char **argv, t_stack *stack, char **args)
{
	int	i;

	if (!stack)
		return (0);
	stack->a = (int *)malloc(sizeof(int) * (argc + 1));
	stack->b = (int *)malloc(sizeof(int) * (argc + 1));
	if (!stack->a || !stack->b)
	{
		free(stack->a);
		free(stack->b);
		free(stack);
		return (0);
	}
	i = 0;
	while (i < argc)
	{
		stack->a[i] = ft_atoi_wcheck(argv[i + 1], stack, args);
		i++;
	}
	stack->a[i] = 0;
	stack->size_a = argc;
	stack->b[0] = 0;
	stack->size_b = 0;
	return (1);
}

static int	find_min_pos(int *arr, int size)
{
	int	min_pos;
	int	i;

	min_pos = 0;
	i = 1;
	while (i < size)
	{
		if (arr[i] < arr[min_pos])
			min_pos = i;
		i++;
	}
	return (min_pos);
}

static void	build_index_map(int *temp, int *indices, int size)
{
	int	i;
	int	min_pos;

	i = 0;
	while (i < size)
	{
		min_pos = find_min_pos(temp, size);
		indices[min_pos] = i;
		temp[min_pos] = INT_MAX;
		i++;
	}
}

void	convert_to_indices(t_stack *arr)
{
	int	i;
	int	*indices;
	int	*temp;

	indices = (int *)malloc(sizeof(int) * arr->size_a);
	temp = (int *)malloc(sizeof(int) * arr->size_a);
	if (!indices || !temp)
		return ;
	i = 0;
	while (i < arr->size_a)
	{
		temp[i] = arr->a[i];
		i++;
	}
	build_index_map(temp, indices, arr->size_a);
	i = 0;
	while (i < arr->size_a)
	{
		arr->a[i] = indices[i];
		i++;
	}
	free(indices);
	free(temp);
}
```

---

## File 4: input_special.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Handle quoted string input
*/

#include "push_swap.h"

void	special_init(char *str, t_stack *stack)
{
	char	**args;
	int		i;

	args = ft_split(str, ' ');
	i = 0;
	while (args[i])
		i++;
	initialize_stack(i, args - 1, stack, args);
	free_split(args);
}

static int	returning(long long result, t_stack *stack, char **args)
{
	if (result < -2147483648 || result > 2147483647)
	{
		write(2, "Error\n", 6);
		if (stack)
			free_stacks(stack);
		if (args)
			free_split(args);
		exit(1);
	}
	return ((int)result);
}

int	ft_atoi_wcheck(char *str, t_stack *stack, char **args)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (returning(result * sign, stack, args));
}
```

---

## File 5: input_validation.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Input validation
*/

#include "push_swap.h"

int	parse_and_validate(t_stack *arr, int argc)
{
	if (!validate_no_duplicates(arr, argc))
		return (write(2, "Error\n", 6));
	if (!validate_range(arr, argc))
		return (write(2, "Error\n", 6));
	if (is_sorted(arr))
		return (-1);
	return (0);
}

int	validate_no_duplicates(t_stack *arr, int argc)
{
	int	i;
	int	j;

	i = -1;
	while (i++ < argc - 2)
	{
		j = i + 1;
		while (j < argc - 1)
		{
			if (arr->a[i] == arr->a[j])
				return (0);
			j++;
		}
	}
	return (1);
}

int	validate_range(t_stack *arr, int argc)
{
	int	i;

	i = -1;
	while (i++ < argc - 2)
	{
		if (arr->a[i] < -2147483648 || arr->a[i] > 2147483647)
			return (0);
	}
	return (1);
}

int	validate_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		if (argv[i][j] == '\0')
			return (0);
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_format(char **a)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(a[1]);
	if (length == 0)
		return (0);
	if ((a[1][i] == '-' || a[1][i] == '+')
		&& a[1][i + 1] >= '0' && a[1][i + 1] <= '9')
		i++;
	while (i < length)
	{
		if (a[1][i] < '0' || a[1][i] > '9')
		{
			if (!a[1][i + 1])
				return (0);
			if (a[1][i] == ' ' && ((a[1][i + 1] >= '0' && a[1][i + 1] <= '9')
				|| (a[1][i + 1] == '-' || a[1][i + 1] == '+')))
				i++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
```

---

## File 6: operations_stack_a.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Stack A operations (sa, ra, rra, pa)
*/

#include "push_swap.h"

int	sa(t_stack *stack)
{
	int	temp;

	if (stack->size_a < 2)
		return (0);
	temp = stack->a[0];
	stack->a[0] = stack->a[1];
	stack->a[1] = temp;
	write(1, "sa\n", 3);
	return (1);
}

int	ra(t_stack *stack)
{
	int	i;
	int	first;

	if (stack->size_a < 2)
		return (0);
	first = stack->a[0];
	i = 0;
	while (i < stack->size_a - 1)
	{
		stack->a[i] = stack->a[i + 1];
		i++;
	}
	stack->a[stack->size_a - 1] = first;
	write(1, "ra\n", 3);
	return (1);
}

int	rra(t_stack *stack)
{
	int	i;
	int	last;

	if (stack->size_a < 2)
		return (0);
	last = stack->a[stack->size_a - 1];
	i = stack->size_a - 1;
	while (i > 0)
	{
		stack->a[i] = stack->a[i - 1];
		i--;
	}
	stack->a[0] = last;
	write(1, "rra\n", 4);
	return (1);
}

int	pa(t_stack *arr)
{
	int	i;

	if (arr->size_b == 0)
		return (0);
	i = arr->size_a;
	while (i > 0)
	{
		arr->a[i] = arr->a[i - 1];
		i--;
	}
	arr->a[0] = arr->b[0];
	i = 0;
	while (i < arr->size_b - 1)
	{
		arr->b[i] = arr->b[i + 1];
		i++;
	}
	arr->size_a++;
	arr->size_b--;
	write(1, "pa\n", 3);
	return (1);
}
```

---

## File 7: operations_stack_b.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Stack B operations (rb, pb)
*/

#include "push_swap.h"

int	rb(t_stack *stack)
{
	int	i;
	int	first;

	if (stack->size_b < 2)
		return (0);
	first = stack->b[0];
	i = 0;
	while (i < stack->size_b - 1)
	{
		stack->b[i] = stack->b[i + 1];
		i++;
	}
	stack->b[stack->size_b - 1] = first;
	write(1, "rb\n", 3);
	return (1);
}

int	pb(t_stack *arr)
{
	int	i;

	if (arr->size_a < 1)
		return (0);
	i = arr->size_b;
	while (i > 0)
	{
		arr->b[i] = arr->b[i - 1];
		i--;
	}
	arr->b[0] = arr->a[0];
	i = 0;
	while (i < arr->size_a - 1)
	{
		arr->a[i] = arr->a[i + 1];
		i++;
	}
	arr->size_a--;
	arr->size_b++;
	arr->a[arr->size_a] = 0;
	arr->b[arr->size_b] = 0;
	write(1, "pb\n", 3);
	return (1);
}
```

---

## File 8: sort_small.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Small array sorting (2-5 elements)
*/

#include "push_swap.h"

void	sort_small_stack(t_stack *arr)
{
	if (arr->size_a == 2)
		sa(arr);
	else if (arr->size_a == 3)
		sort_three_elements(arr);
	else if (arr->size_a == 4)
		sort_four_elements(arr);
	else if (arr->size_a == 5)
		sort_five_elements(arr);
}

void	sort_three_elements(t_stack *arr)
{
	int	first;
	int	second;
	int	third;

	first = arr->a[0];
	second = arr->a[1];
	third = arr->a[2];
	if (first > second && second < third && first < third)
		sa(arr);
	else if (first > second && second > third && first > third)
	{
		sa(arr);
		rra(arr);
	}
	else if (first > second && second < third && first > third)
		ra(arr);
	else if (first < second && second > third && first < third)
	{
		sa(arr);
		ra(arr);
	}
	else if (first < second && second > third && first > third)
		rra(arr);
}

void	sort_four_elements(t_stack *arr)
{
	int	min_index;
	int	i;

	min_index = 0;
	i = 1;
	while (i < arr->size_a)
	{
		if (arr->a[i] < arr->a[min_index])
			min_index = i;
		i++;
	}
	while (min_index > 0)
	{
		ra(arr);
		min_index--;
	}
	pb(arr);
	sort_three_elements(arr);
	pa(arr);
}

void	sort_five_elements(t_stack *arr)
{
	int	min_index;
	int	i;

	min_index = 0;
	i = 1;
	while (i < arr->size_a)
	{
		if (arr->a[i] < arr->a[min_index])
			min_index = i;
		i++;
	}
	if (min_index <= 2)
	{
		while (min_index-- > 0)
			ra(arr);
	}
	else
	{
		while (min_index++ < arr->size_a)
			rra(arr);
	}
	pb(arr);
	sort_four_elements(arr);
	pa(arr);
}
```

---

## File 9: sort_radix.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Radix sort algorithm
*/

#include "push_swap.h"

void	radix_sort_b(t_stack *arr, int size, int bit_size, int bit)
{
	while (size-- && bit <= bit_size && !is_sorted(arr))
	{
		if (((arr->b[0] >> bit) & 1) == 0)
			rb(arr);
		else
			pa(arr);
	}
	if (is_sorted(arr))
		while (arr->size_b > 0)
			pa(arr);
}

int	get_max_bits(int n)
{
	int	bit_size;

	bit_size = 0;
	while (n >> bit_size)
		bit_size++;
	return (bit_size);
}

void	radix_sort(t_stack *arr)
{
	int	size;
	int	bit;
	int	bit_size;

	bit_size = get_max_bits(arr->size_a - 1);
	bit = -1;
	while (++bit <= bit_size)
	{
		size = arr->size_a;
		while (size-- && !is_sorted(arr))
		{
			if (((arr->a[0] >> bit) & 1) == 0)
				pb(arr);
			else
				ra(arr);
		}
		radix_sort_b(arr, arr->size_b, bit_size, bit + 1);
	}
	while (arr->size_b > 0)
		pa(arr);
}
```

---

## File 10: utils.c

```c
/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Utility functions
*/

#include "push_swap.h"

void	free_stacks(t_stack *arr)
{
	if (arr)
	{
		if (arr->a)
			free(arr->a);
		if (arr->b)
			free(arr->b);
		free(arr);
	}
}

int	is_sorted(t_stack *arr)
{
	int	i;

	i = 0;
	while (i < arr->size_a - 1)
	{
		if (arr->a[i] > arr->a[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
```

---

## Summary

**10 files total:**
1. push_swap.h - Header (updated)
2. main.c - Entry point (rewritten)
3. stack_init.c - Stack initialization (rewritten)
4. input_special.c - Quoted string handling (new)
5. input_validation.c - Validation (rewritten)
6. operations_stack_a.c - Stack A ops (rewritten)
7. operations_stack_b.c - Stack B ops (rewritten)
8. sort_small.c - Small sorts (rewritten)
9. sort_radix.c - Radix sort (rewritten)
10. utils.c - Utilities (updated)

**Key improvements:**
✅ Array-based (more efficient)
✅ Handles quoted strings
✅ Index conversion for radix sort
✅ Separate small sort handling
✅ All Norm-compliant

**Copy these directly into your project and adapt the Makefile accordingly!**

