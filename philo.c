/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/06 17:20:35 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(t_params *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->forks[i], NULL);
	pthread_mutex_lock(&info->forks[i]);
	printf("hey\n");
	pthread_mutex_unlock(&info->forks[i]);
	pthread_mutex_destroy(&info->forks[i]);
	return (NULL);
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_philos	*philos;
	t_params	initial;
	int			i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 0;
	initial = init_params(argv, argc);
	philos = init_philos(initial);
	if (initial.ttdie < 1 || initial.tteat < 1 || \
			initial.ttsleep < 1 || initial.eatcount < 1)
		return (write(2, "Invalid params", 14), 1);
	if (initial.num > 200 || initial.num < 1)
		return (write(2, "Wrong philo count", 17), 1);
	initial.forks = malloc(initial.num * sizeof(pthread_mutexattr_t));
	initial.starttime = my_time();
	printf("time = %lu", my_time());
	while (i < initial.num)
	{
		philos[i].tid = malloc (sizeof(pthread_t));
		pthread_create(philos[i].tid, NULL, &cycle, &initial);
		i++;
	}
	i = 0;
	while (i < initial.num)
		pthread_join(*philos[i++].tid, NULL);
	free (philos);
	return (0);
}
