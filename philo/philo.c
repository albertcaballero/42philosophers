/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/21 12:35:39 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cycle(void *void_philo)
{
	t_philos	*philo;

	philo = (t_philos *) void_philo;
	while (philo->params->death != DEAD && check_finished(philo) != FINISHED)
	{
		pthread_mutex_lock(&philo->params->death_mtx);
		if (philo->params->death == DEAD)
		{
			pthread_mutex_unlock(&philo->params->death_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->params->death_mtx);

		pthread_mutex_lock(&philo->params->death_mtx);
		if (philo->params->death != DEAD)
		{
			pthread_mutex_lock(&philo->params->forks[philo->rfork_ix]);
			printf("%lu %i has taken rfork\n", calc_reltime(philo, NOW), philo->num);
		}
		pthread_mutex_unlock(&philo->params->death_mtx);

		pthread_mutex_lock(&philo->params->death_mtx);
		if (philo->params->death != DEAD)
		{ //cuando se quedan esperando a un lock no se estan muriendo, & demiurge cannot see it cuz deat_mtx is locked :)
			pthread_mutex_lock(&philo->params->forks[philo->lfork_ix]);
			printf("%lu %i has taken lfork\n", calc_reltime(philo, NOW), philo->num);
			printf("%lu %i is eating\n", calc_reltime(philo, NOW), philo->num);
			philo->status = EATING;
			my_sleep(philo->params->tteat);xxx
			pthread_mutex_lock(&philo->params->time_mtx);
			philo->tlastmeal = calc_reltime(philo, NOW);
			pthread_mutex_unlock(&philo->params->time_mtx);
			pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
			pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
		}
		pthread_mutex_unlock(&philo->params->death_mtx);

		pthread_mutex_lock(&philo->params->death_mtx);
		if (philo->params->death == DEAD)
		{
			pthread_mutex_unlock(&philo->params->death_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->params->death_mtx);
		act_sleep(philo);
		act_think(philo);
	}
	return (NULL);
}

void	demiurge(t_params *params)
{
	int	i;

	i = 0;
	while (params->death != DEAD && params->finished != params->num)
	{
		if (i > params->num - 1)
			i = 0;
		pthread_mutex_lock(&params->death_mtx);
		printf("I HAVE THE MUTEEEEX");
		check_dead(&params->philos[i]);
		if (params->death == DEAD)
		{
			i = 0;
			while (i++ < params->num)
			{
				params->philos[i].status = DEAD;
				pthread_mutex_destroy(&params->forks[i]);
			}
		}
		pthread_mutex_unlock(&params->death_mtx);
		if (params->eatmax > 0)
		{
			if (check_finished(&params->philos[i]))
				params->finished++;
			if (params->finished == params->num)
				break ;
		}
		i++;
	}
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
	params.death = THINKING;
	i = 0;
	while (i < params.num)
	{
		pthread_create(&params.philos[i].tid, NULL, &cycle, &params.philos[i]);
		my_sleep(10);
		i++;
	}
	demiurge(&params);
	i = 0;
	while (i < params.num)
	{
		pthread_join(params.philos[i].tid, NULL); //bucle infinito (sometimes)
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	return (0);
} //FLAGS ARE COMMENTED ON MAKEFILE
//falta Supervisor whenever we have 6 params
//when someone dies they're not unlocking mutexes
//you have a lot of data races, a freaking lot

//https://github.com/TommyJD93/Philosophers