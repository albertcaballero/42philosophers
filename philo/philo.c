/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/30 12:30:01 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//the cycle the threads repeat all time
void	*cycle(void *void_philo)
{
	t_philos	*philo;

	philo = (t_philos *) void_philo;
	while (check_finished(philo) != FINISHED)
	{
		if (check_dead(philo) != DEAD)
		{
			pthread_mutex_lock(&philo->params->forks[philo->rfork_ix]);
			pthread_mutex_lock(&philo->params->msg_mtx);
			if (check_dead(philo) != DEAD)
				printf("%lu %i has taken rfork\n", calc_reltime(philo, NOW), philo->num);
			pthread_mutex_unlock(&philo->params->msg_mtx);
		}
		else
			break ;
		pthread_mutex_lock(&philo->params->forks[philo->lfork_ix]);
		if (check_dead(philo) != DEAD)
		{
			pthread_mutex_lock(&philo->params->msg_mtx);
			printf("%lu %i has taken lfork\n", calc_reltime(philo, NOW), philo->num);
			printf("%lu %i is eating\n", calc_reltime(philo, NOW), philo->num);
			pthread_mutex_unlock(&philo->params->msg_mtx);
		}
		else
		{
			pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
			pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
			break ;
		}
		philo->eatcount++;
		philo->status = EATING;
		my_sleep(philo->params->tteat, philo);
		philo->tlastmeal = calc_reltime(philo, NOW);
		pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
		pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
		act_sleep(philo);
		act_think(philo);
	}
	return (NULL);
}

//monitor, constantly checks all threads
void	demiurge(t_params *params)
{
	int	i;

	i = 0;
	while (923)
	{
		if (i > params->num - 1)
			i = 0;
		if (check_dead(&params->philos[i]) == DEAD)
			break ;
		if (params->eatmax > 0)
		{
			if (check_finished(&params->philos[i]) == FINISHED && params->philos[i].status != DEAD)
				params->finished++;
			if (params->finished >= params->eatmax)
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
	i = 0;
	while (i < params.num)
	{
		pthread_create(&params.philos[i].tid, NULL, &cycle, &params.philos[i]);
		usleep(10);
		i++;
	}
	demiurge(&params);
	i = 0;
	while (i < params.num)
	{
		pthread_join(params.philos[i].tid, NULL);
		pthread_mutex_destroy(&params.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params.death_mtx);
	pthread_mutex_destroy(&params.msg_mtx);
	pthread_mutex_destroy(&params.finish_mtx);
	pthread_mutex_destroy(&params.time_mtx);
	return (0);
}
//un solo filosofo es graciosillo :)
//antes de imprimir cualquier mensaje comprobar if dead

//https://github.com/TommyJD93/Philosophers
//https://github.com/rphlr/42-Evals/blob/main/Cursus/Philosophers/img/all.jpg 