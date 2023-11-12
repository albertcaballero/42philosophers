/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/12 16:05:48 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(void *void_philo)
{
	t_philos	*philo;

	philo = (t_philos *) void_philo;
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
		my_sleep(philo->params->tteat);
		philo->tlastmeal = my_time() - philo->params->starttime;
		pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
		pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
		act_sleep(philo);
		act_think(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_params	params;
	int			i;

	if (check_input(argc, argv) == -1)
		return (write(2, "Invalid params", 14), 1);
	init_params(argv, argc, &params);
	init_philos(&params);
	params.starttime = my_time();
	i = 0;
	while (i < params.num)
	{
		pthread_create(&params.philos[i].tid, NULL, &cycle, &params.philos[i]);
		i++;
	}
	i = 0;
	while (i < params.num)
	{
		pthread_join(params.philos[i].tid, NULL);
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	return (0);
}

//https://github.com/TommyJD93/Philosophers