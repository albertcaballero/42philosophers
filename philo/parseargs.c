/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:24:57 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/07 18:41:16 by alcaball         ###   ########.fr       */
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

void	init_philos(t_params *params)
{
	int			i;

	i = 1;
	params->philos = malloc(sizeof(t_philos) * params->num);
	while (i <= params->num)
	{
		params->philos[i].num = i;
		params->philos[i].ttdie = params->ttdie;
		params->philos[i].tteat = params->tteat;
		params->philos[i].ttsleep = params->ttsleep;
		if (params->eatcount < INT32_MAX)
			params->philos[i].eatcount = params->eatcount;
		else
			params->philos[i].eatcount = INT32_MAX;
		i++;
		params->philos[i].params = params;
	}
}
