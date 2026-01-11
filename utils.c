/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:17:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/12 00:27:31 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

long	get_useconds(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long ms, t_ph *philo)
{
	long	start_time;

	start_time = get_useconds();
	while (get_useconds() - start_time < ms)
	{
		pthread_mutex_lock(&philo->data->plate_lock);
		if (philo->data->stop == STOP_SIM)
		{
			pthread_mutex_unlock(&philo->data->plate_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->plate_lock);
		usleep(500);
	}
}

void	print_display(t_ph *philo, char *status)
{
	long	cur_time_ms;

	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->plate_lock);
	if (philo->data->stop == STOP_SIM)
	{
		pthread_mutex_unlock(&philo->data->plate_lock);
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	cur_time_ms = get_useconds() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->plate_lock);
	printf("%ld %d %s\n", cur_time_ms, philo->id, status);
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_display_rip(t_ph *philo)
{
	long	cur_time_ms;

	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->plate_lock);
	if (philo->data->stop == STOP_SIM)
	{
		pthread_mutex_unlock(&philo->data->plate_lock);
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	philo->data->stop = STOP_SIM;
	cur_time_ms = get_useconds();
	pthread_mutex_unlock(&philo->data->plate_lock);
	printf("%ld %d died\n", cur_time_ms, philo->id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (-1);
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > 2147483647)
			return (-1);
	}
	return (result * sign);
}
