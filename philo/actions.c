/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:26:32 by alcaball          #+#    #+#             */
/*   Updated: 2023/12/03 19:18:32 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	act_sleep(t_philos *philo)
{
	if (check_already_dead(philo) != DEAD)
	{
		printf("%llu %i is sleeping\n", calc_reltime(philo, NOW), philo->num);
		my_sleep(philo->params->ttsleep, philo);
	}
}

void	act_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->params->forks[philo->rfork_ix]);
	if (check_already_dead(philo) != DEAD)
		printf("%llu %i has taken a fork\n", \
			calc_reltime(philo, NOW), philo->num);
	pthread_mutex_lock(&philo->params->forks[philo->lfork_ix]);
	if (check_already_dead(philo) == DEAD)
	{
		pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
		pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
		return ;
	}
	printf("%llu %i has taken a fork\n", calc_reltime(philo, NOW), philo->num);
	printf("%llu %i is eating\n", calc_reltime(philo, NOW), philo->num);
	philo->eatcount++;
	philo->tlastmeal = calc_reltime(philo, NOW);
	my_sleep(philo->params->tteat, philo);
	pthread_mutex_unlock(&philo->params->forks[philo->rfork_ix]);
	pthread_mutex_unlock(&philo->params->forks[philo->lfork_ix]);
}

void	act_think(t_philos *philo)
{
	if (check_already_dead(philo) != DEAD)
		printf("%llu %i is thinking\n", calc_reltime(philo, NOW), philo->num);
}
