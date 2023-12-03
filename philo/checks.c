/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:30:31 by alcaball          #+#    #+#             */
/*   Updated: 2023/12/03 18:05:14 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	calc_reltime(t_philos *philo, int flag)
{
	uint64_t	currtime;

	pthread_mutex_lock(&philo->params->time_mtx);
	currtime = my_time() - philo->params->starttime;
	pthread_mutex_unlock(&philo->params->time_mtx);
	return (currtime - ((flag == LMEAL) * philo->tlastmeal));
}

//checks if philosophers already died, returns DEAD if true
int	check_already_dead(t_philos *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->params->death_mtx);
	ret = philo->params->death;
	pthread_mutex_unlock(&philo->params->death_mtx);
	return (ret);
}

//check if any philo has to die... and KILLS THEM!! returns DEAD if true
int	kill_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->death_mtx);
	if (calc_reltime(philo, LMEAL) > philo->params->ttdie)
	{
		philo->dead = DEAD;
		philo->params->death = DEAD;
		printf("%llu %i Died\n", calc_reltime(philo, NOW), philo->num);
		pthread_mutex_unlock(&philo->params->death_mtx);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->params->death_mtx);
	return (!DEAD);
}

//check if a philosopher has eaten all times it needs, returns FIN if true
int	check_finished(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->finish_mtx);
	if (philo->finished == FIN)
	{
		pthread_mutex_unlock(&philo->params->finish_mtx);
		return (FIN);
	}
	if (philo->params->eatmax > 0 && philo->eatcount >= philo->params->eatmax)
	{
		philo->finished = FIN;
		if (check_already_dead(philo) != DEAD)
			printf("%llu %i has finished\n", calc_reltime(philo, NOW), philo->num);
		pthread_mutex_unlock(&philo->params->finish_mtx);
		return (FIN);
	}
	pthread_mutex_unlock(&philo->params->finish_mtx);
	return (!FIN);
}
