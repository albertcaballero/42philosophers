/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/07 12:42:26 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(void *info_def)
{
	int			i;
	t_params	*info;

	info = (t_params *) info_def;
	i = info->philos->num;
	printf("time now %lu\n", my_time());
	pthread_mutex_lock(&info->forks[0]);
	info->philos[i].rfork = &info->forks[i]; //bus error
	printf("%lu %i has taken rfork\n", my_time() - info->starttime, info->philos->num);
	pthread_mutex_unlock(&info->forks[0]);
	return (NULL);
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_params	initial;
	int			i;

	if (argc != 5 && argc != 6)
		return (0);
	i = 0;
	initial = init_params(argv, argc);
	initial.philos = init_philos(initial);
	if (initial.ttdie < 1 || initial.tteat < 1 || \
			initial.ttsleep < 1 || initial.eatcount < 1)
		return (write(2, "Invalid params", 14), 1);
	if (initial.num > 200 || initial.num < 1)
		return (write(2, "Wrong philo count", 17), 1);
	initial.forks = malloc(initial.num * sizeof(pthread_mutexattr_t));
	initial.starttime = my_time();
	printf("start time = %lu\n", my_time());
	usleep
	while (i < initial.num)
	{
		initial.philos[i].tid = malloc (sizeof(pthread_t));
		pthread_mutex_init(&initial.forks[i], NULL);
		pthread_create(initial.philos[i].tid, NULL, &cycle, &initial);
		i++;
	}
	i = 0;
	while (i < initial.num)
	{
		pthread_join(*initial.philos[i].tid, NULL);
		pthread_mutex_destroy(&initial.forks[i]);
		i++;
	}
	//free (initial.philos);
	return (0);
}
