/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:24:57 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/06 11:55:29 by alcaball         ###   ########.fr       */
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
	return (params);
}

t_philos	*init_philos(t_params params)
{
	t_philos	*philos;
	int			i;

	i = 1;
	philos = malloc(sizeof(t_philos) * params.num);
	while (i <= params.num)
	{
		philos[i].num = i;
		philos[i].tid = (pthread_t)1;
		philos[i].ttdie = params.ttdie;
		philos[i].tteat = params.tteat;
		philos[i].ttsleep = params.ttsleep;
		if (params.eatcount < INT32_MAX)
			philos[i].eatcount = params.eatcount;
		else
			philos[i].eatcount = INT32_MAX;
		i++;
	}
	return (philos);
}
