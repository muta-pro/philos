/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:50:12 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/11 02:16:41 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define STOP_SIM 0
# define RUN_SIM 1

typedef struct info t_info;

typedef struct ph
{
	int				id;
	int				times_ate;
	long			last_meal_ms;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*data;
}	t_ph;



typedef struct info
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_of_philos;
	int				count_must_eat;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	plate_lock;
	t_ph			*philos;
}	t_info;

void	*loop_life_th(void *arg);
int		loop_death_th(t_info *data);
void	ft_usleep(long ms, t_ph *philo);
long	get_useconds(void);
void	print_display(t_ph *philo, char *status);
void	*one_ph_died(t_ph *philo);
int		check_death(t_info *data, t_ph *philo);
int		check_if_full(t_info *data, t_ph *philo);

int		parse(int argc, char **argv, t_info *data);
void	even_fork(t_ph *philo);
void	uneven_fork(t_ph *philo);
int		init_mtx_f(t_info *data);
int		ft_atoi(const char *str);
void	err_input(void);
void	err_mem(void);
void	err_mtx(void);

#endif