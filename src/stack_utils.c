/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:52:04 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 00:53:15 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	stack_is_empty(t_stack *stack)
{
	if (!stack || stack->top == NULL)
		return (1);
	return (0);
}

void	stack_free(t_stack *stack)
{
	t_node	*current;
	t_node	*temp;

	if (!stack)
		return ;
	current = stack->top;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	free(stack);
}
