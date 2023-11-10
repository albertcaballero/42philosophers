/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albert <albert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/10 04:05:40 by albert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(void *void_philo)
{
	int			i;
	t_philos	*philo;

	philo = (t_philos *) void_philo;
	printf("%i--\n", philo->num);
	i = philo->num - 1;
	pthread_mutex_lock(&philo->params->forks[i]); //THIS IS NOT THE CORRECT LOCK (probably)
	printf("%lu %i has taken rfork\n", my_time(), philo->num);
	philo->status = EATING;
	pthread_mutex_unlock(&philo->params->forks[i]);
	printf("%lu %i is sleeping\n", my_time(), philo->num);
	philo->status = SLEEPING;
	usleep(philo->ttsleep);
	printf("%lu %i is thinking\n", my_time(), philo->num);
	philo->status = THINKING;
	return (NULL);
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_params	params;
	int			i;

	if (argc != 5 && argc != 6)
		return (write(2, "Invalid params", 14), 1);
	i = 0;
	init_params(argv, argc, &params);
	init_philos(&params);
	if (params.ttdie < 1 || params.tteat < 1 || \
			params.ttsleep < 1 || params.eatcount < 1)
		return (write(2, "Invalid params", 14), 1);
	if (params.num > 200 || params.num < 1)
		return (write(2, "Wrong philo count", 17), 1);
	params.starttime = my_time();
	printf("start time = %lu\n", params.starttime);
	i = 0;
	while (i < params.num)
	{
		pthread_create(&params.philos[i].tid, NULL, &cycle, &params.philos[i]);
		i++;
	}
	i = 0;
	while (i <= params.num)
	{
		pthread_join(params.philos[i].tid, NULL);
		pthread_mutex_destroy(&params.philos[i].lock);
		i++;
	}
	return (0);
}
