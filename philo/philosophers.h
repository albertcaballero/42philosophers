/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albert <albert@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:14:09 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/11 23:34:57 by albert           ###   ########.fr       */
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

/* STATUS DEFINITIONS -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-=-=*/
# define SLEEPING 3
# define EATING 1
# define THINKING 2
# define FINISHED 4
# define DEAD 5

struct	s_params;

typedef struct s_ph
{
	struct s_params	*params;
	pthread_t		tid;
	int				num;
	int				status;
	unsigned long	ttdie;
	int				eatcount;
	unsigned long	tlastmeal;
	int				rfork_ix;
	int				lfork_ix;
}	t_philos;

typedef struct s_params
{
	t_philos		*philos;
	int				num;
	unsigned long	ttdie;
	int				tteat;
	int				ttsleep;
	int				eatmax;
	unsigned long	starttime;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msg_mtx;
}	t_params;

/* PHILO.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/
void			*cycle(void *void_philo);

/* UTILS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/
unsigned long	my_time(void);
int				ft_atoi(const char *str);
void			my_sleep(useconds_t time);

/* INITARGS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-=--*/
void			init_params(char **argv, int argc, t_params *params);
void			init_philos(t_params *params);

/* CHECKS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/
int				check_dead(t_philos *philo);
int				check_finished(t_philos *philo);

/* ACTIONS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/
void			act_think(t_philos *philo);
void			act_sleep(t_philos *philo);
void			act_eat(t_philos *philo);

/* PARSEARGS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/
int				check_input(int argc, char **argv);

#endif