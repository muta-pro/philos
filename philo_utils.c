/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 00:27:04 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/11 02:14:01 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	uneven_fork(t_ph *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_display(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_display(philo, "has taken a fork");
}
void	even_fork(t_ph *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_display(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_display(philo, "has taken a fork");
}

void	*one_ph_died(t_ph *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_display(philo, "has taken a fork.");
	ft_usleep(philo->data->time_to_die, philo);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
int	check_if_full(t_info *data, t_ph *philo)
{
	int hungry;

	hungry = 0;
	pthread_mutex_lock(&data->plate_lock);
	if (data->count_must_eat != -1)
		{
			if (philo->times_ate < data->count_must_eat)
				hungry = 1;
		}
	pthread_mutex_unlock(&data->plate_lock);
	return (hungry);
}

int	check_death(t_info *data, t_ph *philo)
{
	long	curr_time_ms;

	pthread_mutex_lock(&data->plate_lock);
	if (data->stop == STOP_SIM)
		return (pthread_mutex_unlock(&data->plate_lock), 1);
	curr_time_ms = get_useconds();
	if ((curr_time_ms - philo->last_meal_ms) >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->plate_lock);
		print_display(philo, "died.\n");
		pthread_mutex_lock(&data->plate_lock);
		data->stop = STOP_SIM;
		return (pthread_mutex_unlock(&data->plate_lock));
	}
	pthread_mutex_unlock(&data->plate_lock);
	return (0);
}
