/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:50:12 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/14 11:31:35 by imutavdz         ###   ########.fr       */
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

typedef struct s_info	t_info;

typedef struct s_ph
{
	int				id;
	int				times_ate;
	long			last_meal_ms;
	int				left_f;
	int				right_f;
	pthread_t		thread_id;
	t_info			*data;
}	t_ph;

typedef struct s_forks
{
	pthread_mutex_t	mtx;
	int				taken;
}	t_f;

typedef struct s_info
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_of_philos;
	int				count_must_eat;
	int				stop;
	t_f				*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	plate_lock;
	t_ph			*philos;
	int	 			f_init_count;
	int				th_init_count;
	int				wr_lock_count;
	int				pl_lock_count;
}	t_info;

void	*loop_life_th(void *arg);
int		loop_death_th(t_info *data);
void	ft_usleep(long ms, t_ph *philo);
long	get_useconds(void);
void	print_display(t_ph *philo, char *status);
void	print_display_rip(t_ph *philo);
void	*one_ph_died(t_ph *philo);
int		check_death(t_info *data, t_ph *philo);
int		check_if_full(t_info *data, t_ph *philo);

int		parse(int argc, char **argv, t_info *data);
int		take_forks(t_ph *philo, t_info *data);
void	drop_forks(t_ph *philo);
void	swap_f(int *x, int *y);
int		stop_sim(t_info *data);
int		ft_atoi(const char *str);
void	err_input(void);
void	err_mem(void);
void	err_mtx(void);

#endif