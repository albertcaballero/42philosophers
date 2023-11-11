/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initargs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:24:57 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/11 11:09:27 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_params(char **argv, int argc, t_params *params)
{
	params->num = ft_atoi(argv[1]);
	params->ttdie = ft_atoi(argv[2]);
	params->tteat = ft_atoi(argv[3]);
	params->ttsleep = ft_atoi(argv[4]);
	params->eatmax = -1;
	if (argc == 6)
		params->eatmax = ft_atoi(argv[5]);
	pthread_mutex_init(&params->lock, NULL);
}

void	init_philos(t_params *params)
{
	int			i;

	i = 0;
	params->philos = malloc(sizeof(t_philos) * params->num);
	while (i < params->num)
	{
		params->philos[i].num = i + 1;
		params->philos[i].ttdie = params->ttdie;
		params->philos[i].tteat = params->tteat;
		params->philos[i].ttsleep = params->ttsleep;
		params->philos[i].eatcount = 0;
		params->philos[i].params = params;
		pthread_mutex_init(&params->philos[i].lock, NULL);
		i++;
	}
	params->forks = malloc(sizeof(pthread_mutex_t) * params->num);
	i = 0;
	while (i < params->num)
		pthread_mutex_init(&params->forks[i++], NULL);
}
