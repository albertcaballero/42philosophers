/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albert <albert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/13 19:09:51 by albert           ###   ########.fr       */
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
		if (philo->params->death == DEAD)
			break ;
		pthread_mutex_lock(&philo->params->forks[philo->rfork_ix]);
		printf("%lu %i has taken rfork\n", my_time() - philo->params->starttime, philo->num);
		pthread_mutex_lock(&philo->params->forks[philo->lfork_ix]);
		if (philo->params->death == DEAD)
			break ;
		printf("%lu %i has taken lfork\n", my_time() - philo->params->starttime, philo->num);
		printf("%lu %i is eating\n", my_time() - philo->params->starttime, philo->num);
		philo->status = EATING;
		my_sleep(philo->params->tteat);
		philo->tlastmeal = my_time() - philo->params->starttime;
		pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
		pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
		if (philo->params->death == DEAD)
			break ;
		act_sleep(philo);
		act_think(philo);
	}
	return (NULL);
}

void	architect(t_params *params)
{
	int	i;

	i = 0;
	while (params->death != DEAD)
	{
		if (i > params->num - 1)
			i = 0;
		my_sleep(10);
		check_dead(&params->philos[i]);
		if (params->death == DEAD)
			break ;
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
		i++;
	}
	architect(&params);
	i = 0;
	while (i < params.num)
	{
		printf("infinito\n"); //bucle infinito
		pthread_join(params.philos[i].tid, NULL);
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	return (0);
} //FLAGS ARE COMMENTED ON MAKEFILE

//https://github.com/TommyJD93/Philosophers
//SHOULD I USE THE SUPERVISOR? How does he stop the other threads?
//How do i constantly check if someone died (even in their sleep)?
	//how do i do it fast enough so that the supervisor can stop all threads before they do smth?
//should i start with my half of the philos on a delay?