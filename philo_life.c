/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:51:37 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/14 11:15:45 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	loop_death_th(t_info *data)
{
	int	i;
	int	are_full;

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
	long	ms_think;

	print_display(philo, "is thinking");
	if (philo->data->num_of_philos % 2 == 1)
	{
		ms_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
		if (ms_think < 0)
			ms_think = 0;
		if (ms_think > philo->data->time_to_eat)
			ms_think = philo->data->time_to_eat;
		ft_usleep(ms_think, philo);
	}
}

void	snoring(t_ph *philo)
{
	print_display(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	eating(t_ph *philo)
{
	if (take_forks(philo, philo->data) != 0)
		return ;
	pthread_mutex_lock(&philo->data->plate_lock);
	philo->last_meal_ms = get_useconds();
	pthread_mutex_unlock(&philo->data->plate_lock);
	print_display(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->data->plate_lock);
	philo->times_ate++;
	pthread_mutex_unlock(&philo->data->plate_lock);
	drop_forks(philo);
}

void	*loop_life_th(void *arg)
{
	t_ph	*philo;
	long	delay;

	philo = (t_ph *)arg;
	if (philo->data->num_of_philos == 1)
	{
		one_ph_died(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		delay = philo->data->time_to_eat / 2;
		if (delay > philo->data->time_to_die / 2)
			delay = philo->data->time_to_die / 2;
		if (delay > 0)
			ft_usleep(delay, philo);
	}
	while (!stop_sim(philo->data))
	{
		eating(philo);
		snoring(philo);
		thinking(philo);
	}
	return (NULL);
}
