/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:32:58 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 02:17:15 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	is_valid_integer(const char *str)
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

int	overflow_check(const char *str)
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

int	has_duplicates(int *array, int size)
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

int	str_to_int(const char *str)
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

int	count_numbers(const char *str)
{
	int	count;
	int	in_number;
	int	i;

	count = 0;
	in_number = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || ((str[i] == '-'
					|| str[i] == '+') && (i == 0 || str[i - 1] == ' ')))
		{
			if (!in_number)
			{
				count++;
				in_number = 1;
			}
		}
		else if (str[i] == ' ')
			in_number = 0;
		else
			return (-1);
		i++;
	}
	return (count);
}
