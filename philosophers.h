/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:14:09 by alcaball          #+#    #+#             */
/*   Updated: 2023/11/03 19:46:34 by alcaball         ###   ########.fr       */
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

typedef struct s_ph
{
	pthread_t		t;
	int				num;
	int				status;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				eatcount;
	struct s_ph		*next;
	pthread_mutex_t	rfork;
	pthread_mutex_t	lfork;
}	t_philos;

typedef struct s_params
{
	int	num;
	int	ttdie;
	int	tteat;
	int	ttsleep;
	int	eatcount;
}	t_params;

int			ft_atoi(const char *str);
t_philos	*init_philos(char **argv, int argc);

#endif