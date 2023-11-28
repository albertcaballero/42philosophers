/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:30:31 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/28 13:47:33 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//calculates time relative to start of program, accepts one of 2 flags (NOW || LMEAL)
unsigned long	calc_reltime(t_philos *philo, int flag)
{
	unsigned long	result;
	unsigned long	currtime;

	pthread_mutex_lock(&philo->params->time_mtx);
	currtime = my_time() - philo->params->starttime;
	if (flag == NOW)
	{
		pthread_mutex_unlock(&philo->params->time_mtx);
		return (currtime);
	}
	else if (flag == LMEAL)
		result = currtime - philo->tlastmeal;
	pthread_mutex_unlock(&philo->params->time_mtx);
	return (result);
}

//check if any philosopher died, returns DEAD if true
int	check_dead(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->death_mtx);
	if ((philo->params->death == DEAD || philo->status == DEAD))
	{
		pthread_mutex_unlock(&philo->params->death_mtx);
		return (DEAD);
	}
	if (calc_reltime(philo, LMEAL) > philo->params->ttdie && philo->status != EATING)
	{
		philo->status = DEAD;
		pthread_mutex_lock(&philo->params->msg_mtx);
		printf("%lu %i Died\n", calc_reltime(philo, NOW), philo->num);
		pthread_mutex_unlock(&philo->params->msg_mtx);
		philo->params->death = DEAD;
		pthread_mutex_unlock(&philo->params->death_mtx);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->params->death_mtx);
	return (!DEAD);
}

//check if a philosopher has eaten all times it needs, returns FINISHED if true
int	check_finished(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->finish_mtx);
	if (philo->finished == FINISHED)
	{
		pthread_mutex_unlock(&philo->params->finish_mtx);
		return (FINISHED);
	}
	if (philo->params->eatmax > 0 && philo->eatcount >= philo->params->eatmax)
	{
		philo->finished = FINISHED;
		pthread_mutex_lock(&philo->params->msg_mtx);
		printf("%lu %i has finished\n", calc_reltime(philo, NOW), philo->num);
		pthread_mutex_unlock(&philo->params->msg_mtx);
		pthread_mutex_unlock(&philo->params->finish_mtx);
		return (FINISHED);
	}
	pthread_mutex_unlock(&philo->params->finish_mtx);
	return (!FINISHED);
}
