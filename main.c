/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:41:50 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/12 01:05:06 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	destroy_mtx_f(t_info *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mtx);
		i++;
	}
	return (0);
}

void	cleanup_table(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	destroy_mtx_f(data);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->plate_lock);
	free(data->forks);
	free(data->philos);
}

int init_mtx_f(t_info *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if(pthread_mutex_init(&data->forks[i].mtx, NULL) != 0)
		{
			err_mtx();
			return (1);
		}
		data->forks[i].taken = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		i;

	memset(&data, 0, sizeof(data));
	if (parse(argc, argv, &data) == 1)
		return (1);
	if (init_mtx_f(&data) != 0)
		return (1);
	if (pthread_mutex_init(&data.write_lock, NULL) != 0)
		return (err_mtx(), 1);
	if (pthread_mutex_init(&data.plate_lock, NULL) != 0)
		return (err_mtx(), 1);
	data.start_time = get_useconds();
	i = 0;
	while (i < data.num_of_philos)
	{	
		data.philos[i].last_meal_ms = data.start_time;
		pthread_create(&data.philos[i].thread_id,
			NULL, loop_life_th, &data.philos[i]);
		usleep (50);
		i++;
	}
	loop_death_th(&data);
	cleanup_table(&data);
	return (0);
}
