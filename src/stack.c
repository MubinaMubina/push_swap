/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:33:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 00:53:43 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

t_stack	*stack_new(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->size = 0;
	return (stack);
}

int	stack_push(t_stack *stack, int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (-1);
	new_node->value = value;
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size++;
	return (0);
}

int	stack_pop(t_stack *stack)
{
	t_node	*temp;
	int		value;

	if (stack_is_empty(stack))
		return (INT_MIN);
	temp = stack->top;
	value = temp->value;
	stack->top = temp->next;
	stack->size--;
	free(temp);
	return (value);
}

int	stack_peek(t_stack *stack)
{
	if (stack_is_empty(stack))
		return (INT_MIN);
	return (stack->top->value);
}
