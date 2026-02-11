/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 22:32:51 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/09 22:33:52 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

int	main(int argc, char **argv)
{
	t_program	*prog;
	int			parse_result;

	if (argc < 2)
		return (0);
	prog = malloc(sizeof(t_program));
	if (!prog)
		return (1);
	prog->stack_a = stack_new();
	prog->stack_b = stack_new();
	prog->sorted_array = NULL;
	prog->size = 0;
	if (!prog->stack_a || !prog->stack_b)
	{
		free_program(prog);
		return (1);
	}
	parse_result = parse_and_create(argc, argv, prog);
	if (parse_result == -1)
	{
		free_program(prog);
		return (1);
	}
	if (parse_result == 1)
	{
		sort_stack(prog);
	}
	free_program(prog);
	return (0);
}
