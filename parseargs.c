/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:24:57 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/04 17:21:52 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_params	init_params(char **argv, int argc)
{
	t_params	params;

	params.num = ft_atoi(argv[1]);
	params.ttdie = ft_atoi(argv[2]);
	params.tteat = ft_atoi(argv[3]);
	params.ttsleep = ft_atoi(argv[4]);
	if (argc == 6)
		params.eatcount = ft_atoi(argv[5]);
	else
		params.eatcount = INT32_MAX;
}

t_philos	*init_philos(t_params params)
{
	t_philos	*philos;
	int			i;

	i = 1;
	philos = malloc(sizeof(t_philos) * ft_atoi(argv[1]));
	while (i <= ft_atoi(argv[1]))
	{
		philos[i].num = i;
		philos[i].tid = i;
		philos[i].ttdie = ft_atoi(argv[2]);
		philos[i].tteat = ft_atoi(argv[3]);
		philos[i].ttsleep = ft_atoi(argv[4]);
		if (argc == 6)
			philos[i].eatcount = ft_atoi(argv[5]);
		else
			philos[i].eatcount = 1;
		i++;
	}
	return (philos);
}
