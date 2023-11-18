/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:26:32 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/18 14:15:27 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	act_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->death_mtx);
	if (philo->params->death == DEAD){
		pthread_mutex_unlock(&philo->params->death_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->params->death_mtx);
	pthread_mutex_lock(&philo->params->msg_mtx);
	printf("%lu %i is sleeping\n", my_time() - philo->params->starttime, philo->num);
	pthread_mutex_unlock(&philo->params->msg_mtx);
	philo->status = SLEEPING;
	my_sleep(philo->params->ttsleep);
}

void	act_eat(t_philos *philo)
{
	(void)philo;
}

void	act_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->death_mtx);
	if (philo->params->death == DEAD){
		pthread_mutex_unlock(&philo->params->death_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->params->death_mtx);
	pthread_mutex_lock(&philo->params->msg_mtx);
	printf("%lu %i is thinking\n", my_time() - philo->params->starttime, philo->num);
	pthread_mutex_unlock(&philo->params->msg_mtx);
	philo->status = THINKING;
}
