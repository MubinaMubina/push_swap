/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:32:54 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/09 22:33:55 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	swap_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (stack_is_empty(stack) || stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack->top = second;
}

void	op_sa(t_program *prog)
{
	swap_stack(prog->stack_a);
	write(1, "sa\n", 3);
}

void	op_sb(t_program *prog)
{
	swap_stack(prog->stack_b);
	write(1, "sb\n", 3);
}

void	op_ss(t_program *prog)
{
	swap_stack(prog->stack_a);
	swap_stack(prog->stack_b);
	write(1, "ss\n", 3);
}

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
