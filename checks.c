/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:43:32 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/11 23:44:20 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

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
	{
		pthread_mutex_unlock(&data->plate_lock);
		return (0);
	}
	curr_time_ms = get_useconds();
	if ((curr_time_ms - philo->last_meal_ms) >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->plate_lock);
		print_display_rip(philo);
		return (1);
	}
	pthread_mutex_unlock(&data->plate_lock);
	return (0);
}
