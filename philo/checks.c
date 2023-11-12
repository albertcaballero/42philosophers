/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:30:31 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/12 16:44:53 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philos *philo)
{
	if (philo->tlastmeal > philo->params->ttdie && philo->status != EATING)
	{
		philo->status = DEAD;
		printf("%lu %i Died\n", my_time() - philo->params->starttime, philo->num);
		return (DEAD);
	}
	return (0);
}

int	check_finished(t_philos *philo)
{
	if (philo->params->eatmax > 0 && philo->eatcount > philo->params->eatmax)
	{
		philo->status = FINISHED;
		printf("%lu %i has finished\n", my_time() - philo->params->starttime, philo->num);
		return (FINISHED);
	}
	return (0);
}
