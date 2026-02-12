/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:16:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/13 01:18:19 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>

typedef struct s_stack
{
	int	*a;
	int	*b;
	int	size_a;
	int	size_b;
}	t_stack;

/* Main functions */
int		main(int argc, char **argv);

/* Initialization */
int		initialize_stack(int argc, char **argv, t_stack *stack, char **args);
void	convert_to_indices(t_stack *arr);
void	special_init(char *str, t_stack *stack);

/* Validation */
int		parse_and_validate(t_stack *arr, int argc);
int		validate_no_duplicates(t_stack *arr, int argc);
int		validate_range(t_stack *arr, int argc);
int		validate_arguments(int argc, char **argv);
int		validate_format(char **a);
int		ft_atoi_wcheck(char *str, t_stack *stack, char **args);

/* Stack operations - Stack A */
int		sa(t_stack *stack);
int		ra(t_stack *stack);
int		rra(t_stack *stack);
int		pa(t_stack *arr);

/* Stack operations - Stack B */
int		rb(t_stack *stack);
int		pb(t_stack *arr);

/* Sorting */
void	sort_stack(t_stack *arr);
void	sort_small_stack(t_stack *arr);
void	sort_three_elements(t_stack *arr);
void	sort_four_elements(t_stack *arr);
void	sort_five_elements(t_stack *arr);
void	radix_sort(t_stack *arr);
void	radix_sort_b(t_stack *arr, int size, int bit_size, int bit);
int		get_max_bits(int n);

/* Utilities */
int		is_sorted(t_stack *arr);
void	free_stacks(t_stack *arr);
void	free_split(char **split);

/* LibFt functions (implement or include from libft) */
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);

#endif
