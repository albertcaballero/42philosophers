/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albert <albert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:29:34 by albert            #+#    #+#             */
/*   Updated: 2023/11/11 23:44:54 by albert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	input_isnum(char *input)
{
	int	j;

	j = 0;
	if (input[j] == 0)
		return (-1);
	while (input[j] != 0)
	{
		if (ft_isdigit(input[j]) == 0)
			return (-1);
		j++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	int	i;

	if (argc != 5 || argc != 6)
		return (-1);
	i = 1;
	while (i < argc)
		if (input_isnum(argv[i++]) == -1)
			return (-1);
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1)
		return (-1);
	if (ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		return (-1);
	if (argc == 6)
		if (ft_atoi(argv[5]) < 1)
			return (-1);
}
