/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:18:42 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/09 22:19:01 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	stack;

	if (argc < 2)
		return (0);
	if (argc == 2)
	{
		if (!initialize_stack_single(argv[1], &stack))
			return (ft_putendl_fd("Error", 2), 1);
	}
	else
	{
		if (!initialize_stack_multiple(argc, argv, &stack))
			return (ft_putendl_fd("Error", 2), 1);
	}
	if (!is_sorted(&stack))
		convert_to_indices(&stack);
	else
		return (free(stack.a), free(stack.b), 0);
	if (stack.size_a <= 5)
		sort_small_stack(&stack);
	else
		radix_sort(&stack);
	free(stack.a);
	free(stack.b);
	return (0);
}
