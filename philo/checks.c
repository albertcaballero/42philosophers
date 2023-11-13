/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albert <albert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:30:31 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/13 20:18:44 by albert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	calc_reltime(t_philos *philo, int flag)
{
	unsigned long	result;
	unsigned long	currtime;

	currtime = my_time() - philo->params->starttime;
	if (flag == NOW)
		return (currtime);
	else if (flag == LMEAL)
		result = currtime - philo->tlastmeal;
	return (result);
}

int	check_dead(t_philos *philo)
{
	if (calc_reltime(philo, LMEAL) > philo->params->ttdie && philo->status != EATING)
	{
		philo->status = DEAD;
		if (philo->params->death == DEAD)
			return(0);
		pthread_mutex_lock(&philo->params->death_mtx);
		printf("%lu %i Died\n", my_time() - philo->params->starttime, philo->num);
		philo->params->death = DEAD;
		pthread_mutex_unlock(&philo->params->death_mtx);
		return (DEAD);
	}
	return (0);
}

int	check_finished(t_philos *philo)
{
	if (philo->params->eatmax > 0 && philo->eatcount > philo->params->eatmax)
	{
		philo->status = FINISHED;
		pthread_mutex_lock(&philo->params->msg_mtx);
		printf("%lu %i has finished\n", my_time() - philo->params->starttime, philo->num);
		pthread_mutex_unlock(&philo->params->msg_mtx);
		return (FINISHED);
	}
	return (0);
}
