/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:26:32 by alcaball          #+#    #+#             */
/*   Updated: 2023/12/02 17:28:09 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	act_sleep(t_philos *philo)
{
	if (check_already_dead(philo) != DEAD)
	{
		//pthread_mutex_lock(&philo->params->msg_mtx);
		printf("%llu %i is sleeping\n", my_time() - philo->params->starttime, philo->num);
		//pthread_mutex_unlock(&philo->params->msg_mtx);
		philo->status = SLEEPING;
		my_sleep(philo->params->ttsleep, philo);
		philo->status = THINKING;
	}
}

void	act_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->rfork_ix]);
	if (check_already_dead(philo) != DEAD)
		printf("%llu %i has taken rfork\n", calc_reltime(philo, NOW), philo->num);
	pthread_mutex_lock(&philo->params->forks[philo->lfork_ix]);
	if (check_already_dead(philo) == DEAD)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
		pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
		return ;
	}
	printf("%llu %i has taken lfork\n", calc_reltime(philo, NOW), philo->num);
	printf("%llu %i is eating\n", calc_reltime(philo, NOW), philo->num);
	philo->eatcount++;
	philo->status = EATING;
	my_sleep(philo->params->tteat, philo);
	philo->tlastmeal = calc_reltime(philo, NOW);
	philo->status = THINKING;
	pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
	pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
}

void	act_think(t_philos *philo)
{
	if (check_already_dead(philo) != DEAD)
	{
		//pthread_mutex_lock(&philo->params->msg_mtx);
		printf("%llu %i is thinking\n", my_time() - philo->params->starttime, philo->num);
		// pthread_mutex_unlock(&philo->params->msg_mtx);
	}
}
