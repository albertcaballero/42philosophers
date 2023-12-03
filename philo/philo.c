/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:13:56 by alcaball          #+#    #+#             */
/*   Updated: 2023/12/03 18:12:34 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo(t_philos *philo)
{
	printf("%llu %i has taken a fork\n", calc_reltime(philo, NOW), 1);
	my_sleep(philo->params->ttdie, philo);
	return ;
}

void	*cycle(void *void_philo)
{
	t_philos	*philo;

	philo = (t_philos *) void_philo;
	if (philo->params->num == 1)
		return (one_philo(philo), NULL);
	if (philo->num % 2 == 0)
		usleep(philo->params->tteat * 1000);
	while (923)
	{
		act_eat(philo);
		if (check_finished(philo) == FIN)
			break ;
		act_sleep(philo);
		if (check_already_dead(philo) == DEAD)
			break ;
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
			if (check_finished(&params->philos[i]) == FIN && \
				params->philos[i].dead != DEAD)
				params->finished++;
			if (params->finished >= params->eatmax)
				break ;
		}
		i++;
	}
}

void	free_params(t_params *params)
{
	pthread_mutex_destroy(&params->death_mtx);
	pthread_mutex_destroy(&params->finish_mtx);
	pthread_mutex_destroy(&params->time_mtx);
	if (params->forks)
		free(params->forks);
	if (params->philos)
		free(params->philos);
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
	free_params(&params);
	return (0);
}

//https://github.com/TommyJD93/Philosophers
//https://github.com/rphlr/42-Evals/blob/main/Cursus/Philosophers/img/all.jpg