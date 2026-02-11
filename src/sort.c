/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:33:04 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 00:51:43 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_three(t_program *prog)
{
	int	top;
	int	second;
	int	third;

	top = stack_peek(prog->stack_a);
	second = prog->stack_a->top->next->value;
	third = prog->stack_a->top->next->next->value;
	if (top > second && second < third && top < third)
		op_sa(prog);
	else if (top > second && second > third)
	{
		op_sa(prog);
		op_rra(prog);
	}
	else if (top > second && second < third && top > third)
		op_ra(prog);
	else if (top < second && second > third && top < third)
	{
		op_sa(prog);
		op_ra(prog);
	}
	else if (top < second && second > third && top > third)
		op_rra(prog);
}

void	sort_small(t_program *prog)
{
	if (prog->size == 1)
		return ;
	if (prog->size == 2)
	{
		if (prog->stack_a->top->value > prog->stack_a->top->next->value)
			op_sa(prog);
	}
	else if (prog->size == 3)
		sort_three(prog);
}

int	get_max_bits(int *array, int size)
{
	int	max;
	int	i;
	int	bits;

	max = array[0];
	i = 1;
	while (i < size)
	{
		if (array[i] > max)
			max = array[i];
		i++;
	}
	bits = 0;
	while ((max >> bits) > 0)
		bits++;
	return (bits);
}

void	radix_sort_loop(t_program *prog, int bit)
{
	int	size;
	int	i;

	size = prog->stack_a->size;
	i = 0;
	while (i < size)
	{
		if (((prog->stack_a->top->value) >> bit) & 1)
			op_ra(prog);
		else
			op_pb(prog);
		i++;
	}
	while (prog->stack_b->size > 0)
		op_pa(prog);
}

void	sort_stack(t_program *prog)
{
	int	bit;
	int	max_bits;

	if (prog->size <= 3)
	{
		sort_small(prog);
		return ;
	}
	max_bits = get_max_bits(prog->sorted_array, prog->size);
	bit = 0;
	while (bit < max_bits)
	{
		radix_sort_loop(prog, bit);
		bit++;
	}
}
