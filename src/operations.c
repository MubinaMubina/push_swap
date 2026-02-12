/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:32:54 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/13 01:33:42 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
