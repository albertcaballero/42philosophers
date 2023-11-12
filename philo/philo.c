/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/12 20:38:28 by alcaball         ###   ########.fr       */
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
	params.death = THINKING;
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
//SHOULD I USE THE SUPERVISOR? How does he stop the other threads?
//How do i constantly check if someone died (even in their sleep)?
	//how do i do it fast enough so that the supervisor can stop all threads before they do smth?
//should i start with my half of the philos on a delay?

/*
./philo 2 1 1200 50
0 1 has taken rfork
0 1 has taken lfork
0 1 is eating
1200 1 is sleeping - he should've died right after starting sleeping
1200 2 has taken rfork
1200 2 has taken lfork
1200 2 is eating
1250 1 is thinking - it is always printed
1250 1 Died
2400 2 is sleeping - same here
2450 2 is thinking - same here
2450 2 Died
*/
//with only 1 philo it loops infinitely because it cannot lock the 2nd fork
	//(it is being considered the same as the first)