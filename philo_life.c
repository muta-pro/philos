/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:51:37 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/11 02:40:29 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int loop_death_th(t_info *data)
{
	int	i;
	int are_full;

	while (1)
	{
		i = -1;
		are_full = 1;
		while (++i < data->num_of_philos)
		{
			if (check_death(data, &data->philos[i]))
				return (0);
			if (check_if_full(data, &data->philos[i]))
				are_full = 0;
		}
		if (data->count_must_eat != -1 && are_full)
		{
			pthread_mutex_lock(&data->plate_lock);
			data->stop = STOP_SIM;
			pthread_mutex_unlock(&data->plate_lock);
			return (0);
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
	print_display(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	eating(t_ph *philo)
{
	if (philo->id % 2 != 0)
		uneven_fork(philo);
	else
		even_fork(philo);
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
	t_ph	*philo;

	philo = (t_ph *)arg;
	if (philo->data->num_of_philos == 1)
		return (one_ph_died(philo), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(500, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->data->plate_lock);
		if (philo->data->stop == STOP_SIM)
		{
			pthread_mutex_unlock(&philo->data->plate_lock);
			break ;
		}
		eating(philo);
		snoring(philo);
		thinking(philo);
	}
	return (NULL);
}
