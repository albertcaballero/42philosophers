/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:14:09 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/06 16:38:31 by alcaball         ###   ########.fr       */
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
	pthread_t		*tid;
	int				num;
	int				status;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eatcount;
	struct s_params	*params;
}	t_philos;

typedef struct s_params
{
	int				num;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eatcount;
	unsigned long	starttime;
	pthread_mutex_t	*forks;
	pthread_mutex_t lock;
	t_philos		*philos;
}	t_params;

int			ft_atoi(const char *str);
t_params	init_params(char **argv, int argc);
t_philos	*init_philos(t_params params);
unsigned long	my_time(void);

#endif