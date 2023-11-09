/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:14:09 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/09 16:27:50 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

# define SLEEPING 3
# define EATING 1
# define THINKING 2
# define FINISHED 4

struct	s_params;

typedef struct s_ph
{
	struct s_params	*params;
	pthread_t		tid;
	int				num;
	int				status;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eatcount;
	pthread_mutex_t	lock;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
}	t_philos;

typedef struct s_params
{
	t_philos		*philos;
	int				num;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eatcount;
	unsigned long	starttime;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
}	t_params;

int			ft_atoi(const char *str);
t_params	init_params(char **argv, int argc);
void		init_philos(t_params *params);
unsigned long	my_time(void);

#endif