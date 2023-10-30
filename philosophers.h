/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcaball <alcaball@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:14:09 by alcaball          #+#    #+#             */
/*   Updated: 2023/10/30 15:20:30 by alcaball         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_params
{
	int			num;
	int			status;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			eatcount;
	t_philos	*next;
}	t_philos;

int			ft_atoi(const char *str);
t_philos	init_params(char **argv, int argc, int i);

#endif