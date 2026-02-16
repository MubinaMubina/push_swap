/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 01:32:16 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/16 09:39:51 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_small_stack(t_stack *arr)
{
	if (arr->size_a == 1)
		return ;
	if (arr->size_a == 2)
		sa(arr);
	else if (arr->size_a == 3)
		sort_three_elements(arr);
	else if (arr->size_a == 4)
		sort_four_elements(arr);
	else if (arr->size_a == 5)
		sort_five_elements(arr);
}

void	sort_three_elements(t_stack *arr)
{
	int	first;
	int	second;
	int	third;

	first = arr->a[0];
	second = arr->a[1];
	third = arr->a[2];
	if (first > second && second < third && first < third)
		sa(arr);
	else if (first > second && second > third && first > third)
	{
		sa(arr);
		rra(arr);
	}
	else if (first > second && second < third && first > third)
		ra(arr);
	else if (first < second && second > third && first < third)
	{
		sa(arr);
		ra(arr);
	}
	else if (first < second && second > third && first > third)
		rra(arr);
}

void	sort_four_elements(t_stack *arr)
{
	int	min_index;
	int	i;

	min_index = 0;
	i = 1;
	while (i < arr->size_a)
	{
		if (arr->a[i] < arr->a[min_index])
			min_index = i;
		i++;
	}
	while (min_index > 0)
	{
		ra(arr);
		min_index--;
	}
	pb(arr);
	sort_three_elements(arr);
	pa(arr);
}

void	sort_five_elements(t_stack *arr)
{
	int	min_index;
	int	i;

	min_index = 0;
	i = 1;
	while (i < arr->size_a)
	{
		if (arr->a[i] < arr->a[min_index])
			min_index = i;
		i++;
	}
	if (min_index <= 2)
	{
		while (min_index-- > 0)
			ra(arr);
	}
	else
	{
		while (min_index++ < arr->size_a)
			rra(arr);
	}
	pb(arr);
	sort_four_elements(arr);
	pa(arr);
}
