/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:30:31 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/27 18:38:57 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	check_dead(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->death_mtx);
	if (philo->params->death == DEAD)
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

int	check_finished(t_philos *philo)
{
	if (philo->params->eatmax > 0 && philo->eatcount >= philo->params->eatmax)
	{
		philo->status = FINISHED;
		pthread_mutex_lock(&philo->params->msg_mtx);
		printf("%lu %i has finished\n", calc_reltime(philo, NOW), philo->num);
		pthread_mutex_unlock(&philo->params->msg_mtx);
		return (FINISHED);
	}
	return (!FINISHED);
}
