/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:30:31 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/11 11:39:45 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philos *philo)
{
	if (philo->tlastmeal > philo->params->ttdie)
		philo->status = DEAD;
	return (DEAD);
}

int	check_finished(t_philos *philo)
{
	if (philo->eatcount > philo->params->eatmax)
		philo->status = FINISHED;
	return (FINISHED);
}