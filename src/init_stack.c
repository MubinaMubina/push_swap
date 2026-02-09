/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:32:37 by mateon            #+#    #+#             */
/*   Updated: 2026/02/09 22:18:50 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	initialize_stack_multiple(int argc, char **argv, t_stack *stack)
{
	int	i;

	if (!parser(argc, argv))
		return (ft_putendl_fd("Error", 2), 0);
	stack->size_a = argc - 1;
	stack->size_b = 0;
	stack->a = (int *)malloc(sizeof(int) * stack->size_a);
	if (!stack->a)
		return (0);
	stack->b = (int *)malloc(sizeof(int) * stack->size_a);
	if (!stack->b)
	{
		free(stack->a);
		return (0);
	}
	i = 0;
	while (i < stack->size_a)
	{
		stack->a[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	return (1);
}

int	initialize_stack_single(char *arg, t_stack *stack)
{
	char	**numbers;
	int		i;
	int		count;

	numbers = ft_split(arg, ' ');
	if (!numbers)
		return (0);
	count = 0;
	while (numbers[count])
		count++;
	if (initialize_stack_multiple(count + 1, numbers - 1, stack) == 0)
	{
		free_split(numbers);
		return (0);
	}
	free_split(numbers);
	return (1);
}
