/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:41:50 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/10 23:03:39 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	time_over(t_info *data)
{
	long	cur_time_ms;

	cur_time_ms = get_useconds();
	if ((cur_time_ms - data->philos->last_meal_ms) > data->time_to_die)
	{
		pthread_mutex_lock(&data->write_lock);
		print_display(data->philos, "died");
		pthread_mutex_unlock(&data->write_lock);
		data->stop = 0;
		return (0);
	}
	return (0);
}

int	destroy_mtx_f(t_info *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}

void	cleanup_table(pthread_t *th, t_info *data, t_ph *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	destroy_mtx_f(data);
	free(data->forks);
	free(th);
	free(philo);
}

int	terminate_all(t_info *data)
{
	destroy_mtx_f(data);
	cleanup_table(&data->philos->thread_id, data, data->philos);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		i;

	memset(&data, 0, sizeof(data));
	if (parse(argc, argv, &data) == 1)
		return (1);
	if (init_mtx_f(& data) != 0)
		return (1);
	if (pthread_mutex_init(&data.write_lock, NULL) != 0)
		return (err_mtx(), 1);
	if (pthread_mutex_init(&data.plate_lock, NULL) != 0)
		return (err_mtx(), 1);
	data.start_time = get_useconds();
	i = 0;
	while (i < data.num_of_philos)
	{	
		pthread_create(&data.philos[i].thread_id,
			NULL, loop_life_th, &data.philos[i]);
		usleep (50);
		i++;
	}
	loop_death_th(&data);
	terminate_all(&data);
	return (0);
}
