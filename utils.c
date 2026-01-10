/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:17:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/10 23:50:14 by imutavdz         ###   ########.fr       */
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

	cur_time_ms = get_useconds() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%zu, %d, %s.\n", cur_time_ms, philo->id, status);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int init_mtx_f(t_info *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if(!pthread_mutex_init(&data->forks[i], NULL))
			return (err_mtx(), 1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * sign);
}
