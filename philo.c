/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/10/30 15:14:08 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(void *info)
{
	printf("")
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_philos	*params;
	int			i;

	if (argc != 5 && argc != 6)
		return (0);
	params = init_params(argv, argc, i);
	if (params.ttdie < 1 || params.tteat < 1 ||\
			params.ttsleep < 1 || params.eatcount < 1)
		return (write(2, "Invalid Params", 14), 1);
	if (params.num > 200 || params.num < 1)
		return (write(2, "Wrong philo count", 17), 1);
	return (0);
}
