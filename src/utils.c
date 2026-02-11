/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:33:16 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 00:52:48 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	free_program(t_program *prog)
{
	if (!prog)
		return ;
	if (prog->stack_a)
		stack_free(prog->stack_a);
	if (prog->stack_b)
		stack_free(prog->stack_b);
	if (prog->sorted_array)
		free(prog->sorted_array);
	free(prog);
}

int	is_sorted(t_stack *stack, t_program *prog)
{
	t_node	*current;
	int		i;

	if (!stack || !prog)
		return (0);
	if (stack_is_empty(stack) || stack->size != prog->size)
		return (0);
	current = stack->top;
	i = prog->size - 1;
	while (current && i > 0)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
		i--;
	}
	return (1);
}

void	print_stacks(t_stack *a, t_stack *b)
{
	t_node	*current_a;
	t_node	*current_b;

	current_a = a->top;
	current_b = b->top;
	while (current_a || current_b)
	{
		if (current_a)
		{
			printf("%d\t", current_a->value);
			current_a = current_a->next;
		}
		else
			printf("_\t");
		if (current_b)
		{
			printf("%d\n", current_b->value);
			current_b = current_b->next;
		}
		else
			printf("_\n");
	}
	printf("--\n");
}
