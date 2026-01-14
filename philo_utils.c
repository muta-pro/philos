/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:27:04 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/13 13:46:43 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	stop_sim(t_info *data)
{
	int	s;

	pthread_mutex_lock(&data->plate_lock);
	s = data->stop;
	pthread_mutex_unlock(&data->plate_lock);
	return (s == STOP_SIM);
}

void	swap_f(int *x, int *y)
{
	int	z;

	z = *x;
	*x = *y;
	*y = z;
}

int	take_forks(t_ph *philo, t_info *data)
{
	int	x;
	int	y;

	x = philo->left_f;
	y = philo->right_f;
	if (x > y)
		swap_f(&x, &y); //pervents circular wait- toal order imposed
	while (!stop_sim(data)) //re-try loop with stop condition -interruptible liveness
	{
		pthread_mutex_lock(&data->forks[x].mtx); //lock both fork-state mutexes - not holding a fork
		pthread_mutex_lock(&data->forks[y].mtx); //to update taken flags without data races
		if (data->forks[x].taken == 0 && data->forks[y].taken == 0)
		{ //atoimc reservation - cheeck both states
			data->forks[x].taken = 1;
			data->forks[y].taken = 1;
			pthread_mutex_unlock(&data->forks[y].mtx);
			pthread_mutex_unlock(&data->forks[x].mtx);
			return (print_display(philo, "has taken a fork"),
				print_display(philo, "has taken a fork"), 0);
		}
		pthread_mutex_unlock(&data->forks[y].mtx); //release locks immediately and backoff
		pthread_mutex_unlock(&data->forks[x].mtx);
		usleep (200);
	}
	return (1);
}

void	drop_forks(t_ph *philo)
{
	int	x;
	int	y;

	x = philo->left_f;
	y = philo->right_f;
	if (x > y)
		swap_f(&x, &y);
	pthread_mutex_lock(&philo->data->forks[x].mtx);
	pthread_mutex_lock(&philo->data->forks[y].mtx);
	philo->data->forks[x].taken = 0;
	philo->data->forks[y].taken = 0;
	pthread_mutex_unlock(&philo->data->forks[y].mtx);
	pthread_mutex_unlock(&philo->data->forks[x].mtx);
}

void	*one_ph_died(t_ph *philo)
{
	int	x;

	x = philo->left_f;
	pthread_mutex_lock(&philo->data->forks[x].mtx);
	if (philo->data->forks[x].taken == 0)
		philo->data->forks[x].taken = 1;
	pthread_mutex_unlock(&philo->data->forks[x].mtx);
	print_display(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo);
	return (NULL);
}
