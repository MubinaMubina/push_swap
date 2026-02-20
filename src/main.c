/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:32:51 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/18 15:23:11 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	init_and_validate(int argc, char **argv, t_stack **arr)
{
	*arr = (t_stack *)malloc(sizeof(t_stack));
	if (!*arr)
		return (write(2, "Error\n", 6), 1);
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

	if (argc < 2)
		return (0);
	if (argv[1][0] == '\0')
		return (write(2, "Error\n", 6), 1);
	if (argv[1][0] == ' ' && argv[1][1] == '\0')
		return (write(2, "Error\n", 6), 1);
	if ((!validate_arguments(argc, argv) && argc > 2)
		|| validate_format(argv) == 0)
		return (write(2, "Error\n", 6), 1);
	if (init_and_validate(argc, argv, &arr) != 0)
		return (1);
	if (arr->size_a > 1 && !is_sorted(arr))
	{
		convert_to_indices(arr);
		if (arr->size_a <= 5)
			sort_small_stack(arr);
		else
			radix_sort(arr);
	}
	free_stacks(arr);
	return (0);
}
