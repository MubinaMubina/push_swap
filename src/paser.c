/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 20:59:13 by mateon            #+#    #+#             */
/*   Updated: 2026/02/09 22:19:04 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	check_doubles(int argc, char **argv)
{
	int	i;
	int	j;
	int	num;

	i = 1;
	while (i < argc)
	{
		num = ft_atoi(argv[i]);
		j = i + 1;
		while (j < argc)
		{
			if (ft_atoi(argv[j]) == num)
				return (0);
			j++;
		}
		i++;
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

int	validate_range(int argc, char **argv)
{
	int		i;
	long	num;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) > 11) // max length for INT_MIN with sign
			return (0);
		num = ft_atol(argv[i]);
		if (num < INT_MIN || num > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	parser(int argc, char **argv)
{
	if (!validate_arguments(argc, argv)) // check only for numbers
		return (0);
	if (!validate_range(argc, argv)) // check for INT_MIN and INT_MAX
		return (0);
	if (!check_doubles(argc, argv)) // check for duplicates
		return (0);
	return (1);
}
