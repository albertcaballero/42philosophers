/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:24:57 by alcaball          #+#    #+#             */
/*   Updated: 2023/10/30 15:20:54 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philos	*init_philos(char **argv, int argc)
{
	t_philos	*params;
	t_philos	*first;
	int			i;

	i = 0;
	params = malloc(sizeof(params));
	first = params;
	while (i < ft_atoi(argv[1]))
	{
		params->num = ft_atoi(argv[1]);
		params->ttdie = ft_atoi(argv[2]);
		params->tteat = ft_atoi(argv[3]);
		params->ttsleep = ft_atoi(argv[4]);
		if (argc == 6)
			params->eatcount = ft_atoi(argv[5]);
		else
			params->eatcount = 1;
		params->next = malloc(sizeof(params));
		params = params->next;
		i++;
	}
	return (params);
}
