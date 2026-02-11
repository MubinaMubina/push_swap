/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:47:50 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 00:51:37 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	op_rr(t_program *prog)
{
	rotate_stack(prog->stack_a);
	rotate_stack(prog->stack_b);
	write(1, "rr\n", 3);
}

void	op_rra(t_program *prog)
{
	reverse_rotate_stack(prog->stack_a);
	write(1, "rra\n", 4);
}

void	op_rrb(t_program *prog)
{
	reverse_rotate_stack(prog->stack_b);
	write(1, "rrb\n", 4);
}

void	op_rrr(t_program *prog)
{
	reverse_rotate_stack(prog->stack_a);
	reverse_rotate_stack(prog->stack_b);
	write(1, "rrr\n", 4);
}
