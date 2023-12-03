/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:14:09 by alcaball          #+#    #+#             */
/*   Updated: 2023/12/03 17:41:15 by alcaball         ###   ########.fr       */
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
# define FIN 4
# define DEAD 5

/* TIME FLAGS -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-=-=*/
# define NOW 1
# define LMEAL 2

struct	s_params;

typedef struct s_ph
{
	struct s_params	*params;
	pthread_t		tid;
	int				num;
	int				dead;
	int				finished;
	int				eatcount;
	uint64_t		tlastmeal;
	int				rfork_ix;
	int				lfork_ix;
}	t_philos;

typedef struct s_params
{
	t_philos		*philos;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	msg_mtx;
	pthread_mutex_t	time_mtx;
	pthread_mutex_t	finish_mtx;
	int				num;
	int				death;
	int				finished;
	uint64_t		ttdie;
	int				tteat;
	int				ttsleep;
	int				eatmax;
	uint64_t		starttime;
	pthread_mutex_t	*forks;
}	t_params;

/* PHILO.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/

void		*cycle(void *void_philo);
void		demiurge(t_params *params);

/* UTILS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/

uint64_t	my_time(void);
int			ft_atoi(const char *str);
void		my_sleep(useconds_t time, t_philos *philo);

/* INITARGS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-=--*/

void		init_params(char **argv, int argc, t_params *params);
void		init_philos(t_params *params);

/* CHECKS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/

int			kill_philo(t_philos *philo);
int			check_already_dead(t_philos *philo);
int			check_finished(t_philos *philo);
uint64_t	calc_reltime(t_philos *philo, int flag);

/* ACTIONS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/

void		act_think(t_philos *philo);
void		act_sleep(t_philos *philo);
void		act_eat(t_philos *philo);

/* PARSEARGS.C -==-=-=-==-=-=-=-==-=-=-==-=-=-==-=-=-==-=-==--==-=-=-=-=-==-*/

int			check_input(int argc, char **argv);

#endif