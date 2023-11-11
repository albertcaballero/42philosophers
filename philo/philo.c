/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/11 19:31:16 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(void *void_philo)
{
	int			i;
	t_philos	*philo;

	philo = (t_philos *) void_philo;
	i = philo->num - 1;
	if (philo->num != 1)
		my_sleep(10);
	//hay  gente que pone los pares a pensar ahora
	while (check_dead(philo) != DEAD && check_finished(philo) != FINISHED)
	{
		pthread_mutex_lock(&philo->params->forks[philo->rfork_ix]);
		printf("%lu %i has taken rfork\n", my_time() - philo->params->starttime, philo->num);
		pthread_mutex_lock(&philo->params->forks[philo->lfork_ix]);
		printf("%lu %i has taken lfork\n", my_time() - philo->params->starttime, philo->num);
		printf("%lu %i is eating\n", my_time() - philo->params->starttime, philo->num);
		philo->status = EATING;
		philo->tlastmeal = my_time() - philo->params->starttime;
		pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
		pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
		printf("%lu %i is sleeping\n", my_time() - philo->params->starttime, philo->num);
		philo->status = SLEEPING;
		my_sleep(philo->ttsleep);
		printf("%lu %i is thinking\n", my_time() - philo->params->starttime, philo->num);
		philo->status = THINKING;
	}
	return (NULL);
}

int	main(int argc, char **argv) //https://github.com/TommyJD93/Philosophers
{
	t_params	params;
	int			i;

	if (argc != 5 && argc != 6)
		return (write(2, "Invalid param count", 19), 1);
	i = 0;
	init_params(argv, argc, &params);
	init_philos(&params);
	if (params.ttdie < 1 || params.tteat < 1 || \
			params.ttsleep < 1)
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
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	return (0);
}
