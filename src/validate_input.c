/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 01:27:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/16 10:04:12 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	parse_and_validate(t_stack *arr, int argc)
{
	if (!validate_no_duplicates(arr, argc))
		return (write(2, "Error\n", 6));
	if (!validate_range(arr, argc))
		return (write(2, "Error\n", 6));
	if (arr->size_a > 1 && is_sorted(arr))
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
	while (i < length)
	{
		if ((a[1][i] == '-' || a[1][i] == '+') && (++i >= length
				|| (a[1][i] < '0' || a[1][i] > '9')))
			return (0);
		while (i < length && a[1][i] >= '0' && a[1][i] <= '9')
			i++;
		if (i >= length)
			break ;
		if (a[1][i] != ' ' || ++i >= length)
			return (0);
	}
	return (1);
}
