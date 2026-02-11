/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:33:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/09 22:34:04 by mmubina          ###   ########.fr       */
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
