/*
** EPITECH PROJECT, 2024
** push_swap
** File description:
** Main header file for push_swap project
*/

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

typedef struct s_program
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		*sorted_array;
	int		size;
}	t_program;

/* Stack creation and destruction */
t_stack	*stack_new(void);
void	stack_free(t_stack *stack);

/* Stack operations */
int		stack_push(t_stack *stack, int value);
int		stack_pop(t_stack *stack);
int		stack_peek(t_stack *stack);
int		stack_is_empty(t_stack *stack);

/* Operations sa, sb, ss */
void	op_sa(t_program *prog);
void	op_sb(t_program *prog);
void	op_ss(t_program *prog);

/* Operations pa, pb */
void	op_pa(t_program *prog);
void	op_pb(t_program *prog);

/* Rotations ra, rb, rr */
void	op_ra(t_program *prog);
void	op_rb(t_program *prog);
void	op_rr(t_program *prog);

/* Reverse rotations rra, rrb, rrr */
void	op_rra(t_program *prog);
void	op_rrb(t_program *prog);
void	op_rrr(t_program *prog);

/* Sorting */
void	sort_stack(t_program *prog);
void	sort_three(t_program *prog);
void	sort_two(t_program *prog);

/* Utilities */
int		is_sorted(t_stack *stack, t_program *prog);
void	print_stacks(t_stack *a, t_stack *b);
void	free_program(t_program *prog);

/* Parser */
int		parse_and_create(int argc, char **argv, t_program *prog);

#endif
