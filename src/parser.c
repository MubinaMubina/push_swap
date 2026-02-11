/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:32:58 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/09 22:33:57 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static int	is_valid_integer(const char *str)
{
	int	i;
	int	has_digits;

	i = 0;
	has_digits = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		has_digits = 1;
		i++;
	}
	return (has_digits);
}

static int	overflow_check(const char *str)
{
	long	num;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[0] == '+')
		i++;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		if (sign == 1 && num > INT_MAX)
			return (0);
		if (sign == -1 && num > (long)INT_MAX + 1)
			return (0);
		i++;
	}
	return (1);
}

static int	has_duplicates(int *array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (array[i] == array[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	str_to_int(const char *str)
{
	long	num;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[0] == '+')
		i++;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}

int	parse_and_create(int argc, char **argv, t_program *prog)
{
	int	i;
	int	*array;

	if (argc < 2)
		return (0);
	array = malloc(sizeof(int) * (argc - 1));
	if (!array)
		return (-1);
	i = 0;
	while (i < argc - 1)
	{
		if (!is_valid_integer(argv[i + 1]))
		{
			free(array);
			write(2, "Error\n", 6);
			return (-1);
		}
		if (!overflow_check(argv[i + 1]))
		{
			free(array);
			write(2, "Error\n", 6);
			return (-1);
		}
		array[i] = str_to_int(argv[i + 1]);
		i++;
	}
	if (has_duplicates(array, argc - 1))
	{
		free(array);
		write(2, "Error\n", 6);
		return (-1);
	}
	prog->size = argc - 1;
	prog->sorted_array = array;
	i = 0;
	while (i < prog->size)
	{
		stack_push(prog->stack_a, array[i]);
		i++;
	}
	return (1);
}
