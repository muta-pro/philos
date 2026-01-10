/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:41:50 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/10 05:55:30 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	time_over(t_info *data)
{
	long	cur_time_ms;

	cur_time_ms = get_useconds();
	if ((cur_time_ms - data->philos->last_meal_ms) > data->time_to_die)
	{
		print_display(data->philos, "died");
		data->stop = 0;
		return (0);
	}
	return (0);
}

void	thinking(t_ph *philo)
{
	print_display(philo, "thinking");
}

void	snoring(t_ph *philo)
{
	print_display(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_ph *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_display(philo, "taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_display(philo, "taken a fork");
	print_display(philo, "is eating");
	pthread_mutex_lock(&philo->data->plate_lock);
	philo->last_meal_ms = get_useconds();
	philo->times_ate++;
	pthread_mutex_unlock(&philo->data->plate_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	snoring(philo);
	thinking(philo);
}

void	cleanup_table(int num)
{
	t_table	table;

	free(table);
}

int	has_starved(t_ph *philo)
{
	
	return (1);
}

int	they_live(t_ph *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(500, philo);
	while (1)
	{
		eating((t_ph *)arg);
		snoring((t_ph *)arg);
		thinking((t_ph *)arg);
	}
	return (NULL);
}

int	main(int argc, char **argv[])
{
	t_info	*data;
	int		i;

	memset(&data, 0, sizeof(data));
	if (parse(&data) == 1)
		return (1);
	i = 0;
	while (i < data->num_of_philos)
	{
		data->start_time = get_useconds();
		pthread_create(&data->philos[i].thread_id,
			NULL, they_live(data->philos), &data->philos[i]);
		i++;
	}
	check_life(&data);
	terminate_all(&d);
	return (0);
}
