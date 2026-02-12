/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:49:20 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/13 01:33:16 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
