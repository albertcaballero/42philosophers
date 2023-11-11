/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:49:21 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/11 15:56:00 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	numb;
	int	flag;

	i = 0;
	numb = 0;
	flag = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			flag = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		numb = (numb * 10 + (str[i] - 48));
		i++;
	}
	return (numb * flag);
}

unsigned long	my_time(void)
{
	struct timeval	abstime;

	if (gettimeofday(&abstime, NULL) == -1)
		return (write(2, "ERROR getting time", 18));
	return ((abstime.tv_sec * (u_int64_t)1000) + (abstime.tv_usec / 1000));
}

void	my_sleep(useconds_t time)
{
	u_int64_t	start;

	start = my_time();
	while ((my_time() - start) < time)
		usleep(time / 10);
}
