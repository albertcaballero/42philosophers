/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/12/02 13:20:57 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo(t_philos *philo)
{
	printf("%lu %i has taken a fork\n", calc_reltime(philo, NOW), 1);
	my_sleep(philo->params->ttdie, philo);
	return ;
}

void	*cycle(void *void_philo)
{
	t_philos	*philo;

	philo = (t_philos *) void_philo;
	if (philo->params->num == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->num % 2 == 0)
		usleep(philo->params->tteat); //hay que arreglar esto dependiendo de si ttdie es menor
	while (check_finished(philo) != FINISHED)
	{
		pthread_mutex_lock(&philo->params->forks[philo->rfork_ix]);
		if (check_already_dead(philo) != DEAD)
			printf("%lu %i has taken rfork\n", calc_reltime(philo, NOW), philo->num);
		pthread_mutex_lock(&philo->params->forks[philo->lfork_ix]);
		if (check_already_dead(philo) != DEAD)
		{
			printf("%lu %i has taken lfork\n", calc_reltime(philo, NOW), philo->num);
			printf("%lu %i is eating\n", calc_reltime(philo, NOW), philo->num);
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
		philo->status = THINKING;
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
		i = (i <= (params->num - 1)) * i;
		if (kill_philo(&params->philos[i]) == DEAD)
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
		return (write(2, "Invalid params\n", 15), 1);
	init_params(argv, argc, &params);
	init_philos(&params);
	params.starttime = my_time();
	printf("starttime = %lu\n", params.starttime);
	i = 0;
	while (i < params.num)
	{
		pthread_create(&params.philos[i].tid, NULL, &cycle, &params.philos[i]);
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
	pthread_mutex_destroy(&params.finish_mtx);
	pthread_mutex_destroy(&params.time_mtx);
	return (0);
}

//https://github.com/TommyJD93/Philosophers
//https://github.com/rphlr/42-Evals/blob/main/Cursus/Philosophers/img/all.jpg 