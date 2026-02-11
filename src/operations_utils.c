/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:49:20 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 01:08:39 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	op_pa(t_program *prog)
{
	int	value;

	if (stack_is_empty(prog->stack_b))
		return ;
	value = stack_pop(prog->stack_b);
	stack_push(prog->stack_a, value);
	write(1, "pa\n", 3);
}

void	op_pb(t_program *prog)
{
	int	value;

	if (stack_is_empty(prog->stack_a))
		return ;
	value = stack_pop(prog->stack_a);
	stack_push(prog->stack_b, value);
	write(1, "pb\n", 3);
}
