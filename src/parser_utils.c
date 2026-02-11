/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:43:56 by mmubina           #+#    #+#             */
/*   Updated: 2026/02/12 02:06:46 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	sort_int_array(int *array, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	extract_number(const char *str, int *pos, char *num_str)
{
	int	i;
	int	j;

	i = *pos;
	j = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (-1);
	while (str[i] && str[i] != ' ')
	{
		num_str[j] = str[i];
		j++;
		i++;
	}
	num_str[j] = '\0';
	*pos = i;
	return (j);
}

static int	parse_space_separated(const char *str, int **array)
{
	int		count;
	int		i;
	int		j;
	char	num_str[20];

	count = count_numbers(str);
	if (count <= 0)
		return (-1);
	*array = malloc(sizeof(int) * count);
	if (!*array)
		return (-1);
	i = 0;
	j = 0;
	while (j < count)
	{
		if (extract_number(str, &i, num_str) <= 0)
			return (free(*array), -1);
		if (!is_valid_integer(num_str))
			return (free(*array), -1);
		if (!overflow_check(num_str))
			return (free(*array), -1);
		(*array)[j] = str_to_int(num_str);
		j++;
	}
	return (count);
}

int	get_int_array(int argc, char **argv, int **array)
{
	int	count;
	int	i;

	if (argc == 2)
		return (parse_space_separated(argv[1], array));
	count = argc - 1;
	*array = malloc(sizeof(int) * count);
	if (!*array)
		return (-1);
	i = 0;
	while (i < count)
	{
		if (!is_valid_integer(argv[i + 1]) || !overflow_check(argv[i + 1]))
		{
			free(*array);
			ft_putendl_fd("Error\n", 2);
			return (-1);
		}
		(*array)[i] = str_to_int(argv[i + 1]);
		i++;
	}
	return (count);
}

int	parse_and_create(int argc, char **argv, t_program *prog)
{
	int	*array;
	int	count;
	int	i;

	if (argc < 2)
		return (0);
	count = get_int_array(argc, argv, &array);
	if (count <= 0)
		return (-1);
	if (has_duplicates(array, count))
	{
		free(array);
		ft_putendl_fd("Error\n", 2);
		return (-1);
	}
	prog->size = count;
	prog->sorted_array = array;
	i = prog->size - 1;
	while (i >= 0)
	{
		stack_push(prog->stack_a, array[i]);
		i--;
	}
	return (1);
}
