/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:33:16 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/13 01:28:36 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
