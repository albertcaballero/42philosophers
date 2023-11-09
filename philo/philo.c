/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/09 16:28:26 by alcaball         ###   ########.fr       */
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
	pthread_mutex_unlock(&philo->lock);
	printf("%lu %i is sleeping\n", my_time(), philo->num);
	philo->status = SLEEPING;
	usleep(philo->ttsleep);
	printf("%lu %i is thinking\n", my_time(), philo->num);
	philo->status = THINKING;
	return (NULL);
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_params	initial;
	int			i;

	if (argc != 5 && argc != 6)
		return (write(2, "Invalid params", 14), 1);
	i = 0;
	initial = init_params(argv, argc);
	init_philos(&initial);
	if (initial.ttdie < 1 || initial.tteat < 1 || \
			initial.ttsleep < 1 || initial.eatcount < 1)
		return (write(2, "Invalid params", 14), 1);
	if (initial.num > 200 || initial.num < 1)
		return (write(2, "Wrong philo count", 17), 1);
	initial.forks = malloc(initial.num * sizeof(pthread_mutex_t));
	initial.starttime = my_time();
	printf("start time = %lu\n", initial.starttime);
	while (i++ < initial.num)
		initial.philos[i].params = &initial;
	printf("%p||\n", (void *)initial.philos[0].params);
	printf("%p||\n", (void *)&initial);
	i = 0;
	while (i < initial.num)
	{
		printf("%i||\n", initial.philos[i].params->num);
		initial.philos[i].tid = malloc(sizeof(pthread_t));
		pthread_mutex_init(&initial.forks[i], NULL);
		pthread_create(&initial.philos[i].tid, NULL, &cycle, &initial.philos[i]);
		i++;
	}
	i = 0;
	while (i <= initial.num)
	{
		pthread_join(initial.philos[i].tid, NULL);
		pthread_mutex_destroy(&initial.philos[i].lock);
		i++;
	}
	return (0);
}
