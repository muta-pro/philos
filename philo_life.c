/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:51:37 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/11 00:01:24 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int loop_death_th(t_info *data)
{
	int	i;
	long	curr_time_ms;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->plate_lock);
			if (data->stop == STOP_SIM)
			{
				pthread_mutex_unlock(&data->plate_lock);
				return (0);
			}
			curr_time_ms = get_useconds();
			if ((curr_time_ms - data-> philos[i].last_meal_ms) >= data->time_to_die)
			{
				pthread_mutex_unlock(&data->plate_lock);
				print_display(&data->philos[i], "died.\n");
				pthread_mutex_lock(&data->plate_lock);
				data->stop = STOP_SIM;
				pthread_mutex_unlock(&data->plate_lock);
				return (0);
			}
			pthread_mutex_unlock(&data->plate_lock);
			i++;
		}
		usleep(1000);
	}
	return (0);
}
void	thinking(t_ph *philo)
{
	print_display(philo, "is thinking");
}

void	snoring(t_ph *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	print_display(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->write_lock);
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	eating(t_ph *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_display(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_display(philo, "has taken a fork");

	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_display(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_display(philo, "has taken a fork");
	}
	print_display(philo, "is eating");
	pthread_mutex_lock(&philo->data->plate_lock);
	philo->last_meal_ms = get_useconds();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->data->plate_lock);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*loop_life_th(void *arg)
{
	t_ph *philo;

	philo = (t_ph *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(500, philo);
	while (1)
	{
		eating(philo);
		snoring(philo);
		thinking(philo);
	}
	return (NULL);
}
