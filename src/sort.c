/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:33:04 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/13 01:29:17 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

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
