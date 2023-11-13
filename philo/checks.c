/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:30:31 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/13 11:07:02 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philos *philo)
{
	if (philo->tlastmeal > philo->params->ttdie && philo->status != EATING) //studpid comparison
	{ //tlastmeal is abstime, ttdie is reltime you cannot compare them :)
		philo->status = DEAD;
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
