/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albert <albert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/05 14:25:50 by albert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(t_params *info)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(info->num * sizeof(pthread_mutex_t));
	pthread_mutex_lock(forks[i]);
	printf("hey %s\n", info);

	free (forks);
	return (NULL);
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_philos	*philos;
	t_params	initial;
	int			i;

	if (argc != 5 && argc != 6)
		return (0);
	initial = init_params(argv, argc);
	philos = init_philos(initial);
	if (initial.ttdie < 1 || initial.tteat < 1 || \
			initial.ttsleep < 1 || initial.eatcount < 1)
		return (write(2, "Invalid params", 14), 1);
	if (initial.num > 200 || initial.num < 1)
		return (write(2, "Wrong philo count", 17), 1);
	while (i < initial.num)
		pthread_create(&philos[i++].tid, NULL, &cycle, &initial);
	free (philos);
	return (0);
}

//a philosopher is a thread (pthread create)
//a fork is a resource (e.g. a variable)
// 		in cycle() create an array of pthread_mutex_t fork(for as many forks as there should be)
// 		it's what's used in the lock
//		struct t_philo.r/lfork points to a member of that array