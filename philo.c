/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/02 14:49:10 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(void *info)
{
	printf("hey %s\n", info);
	return(NULL);
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_philos	*philos;
	pthread_t	tid;

	if (argc != 5 && argc != 6)
		return (0);
	philos = init_params(argv, argc);
	if (philos->ttdie < 1 || philos->tteat < 1 ||\
			philos->ttsleep < 1 || philos->eatcount < 1)
		return (write(2, "Invalid params", 14), 1);
	if (philos->num > 200 || philos->num < 1)
		return (write(2, "Wrong philo count", 17), 1);
	pthread_create(&tid, NULL, &cycle, &philos);
	free (philos);
	exit(EXIT_SUCCESS);
	return (0);
}
