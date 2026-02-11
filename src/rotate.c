/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:33:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 00:51:40 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	rotate_stack(t_stack *stack)
{
	t_node	*first;
	t_node	*current;

	if (stack_is_empty(stack) || stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	current = stack->top;
	while (current->next)
		current = current->next;
	current->next = first;
	first->next = NULL;
}

static void	reverse_rotate_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*prev;
	t_node	*last;

	if (stack_is_empty(stack) || stack->size < 2)
		return ;
	current = stack->top;
	prev = NULL;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	last = current;
	prev->next = NULL;
	last->next = stack->top;
	stack->top = last;
}

void	op_ra(t_program *prog)
{
	rotate_stack(prog->stack_a);
	write(1, "ra\n", 3);
}

void	op_rb(t_program *prog)
{
	rotate_stack(prog->stack_b);
	write(1, "rb\n", 3);
}
