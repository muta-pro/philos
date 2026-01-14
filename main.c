/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:41:50 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/14 11:33:00 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	cleanup_table(t_info *data)
{
	int	i;

	if (data->pl_lock_count)
	{
		pthread_mutex_lock(&data->plate_lock);
		data->stop = STOP_SIM;
		pthread_mutex_unlock(&data->plate_lock);
	}
	i = 0;
	while (i < data->th_init_count)
		pthread_join(data->philos[i++].thread_id, NULL);
	i = 0;
	while (i < data->f_init_count)
		pthread_mutex_destroy(&data->forks[i++].mtx);
	if (data->wr_lock_count)
		pthread_mutex_destroy(&data->write_lock);
	if (data->pl_lock_count)
		pthread_mutex_destroy(&data->plate_lock);
	free(data->forks);
	data->forks = NULL;
	free(data->philos);
	data->forks = NULL;
}

int	init_mtx_f(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i].mtx, NULL) != 0)
		{
			err_mtx();
			return (1);
		}
		data->forks[i].taken = 0;
		data->f_init_count++;
		i++;
	}
	return (0);
}

int	init_thread(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal_ms = data->start_time;
		if (pthread_create(&data->philos[i].thread_id,
				NULL, loop_life_th, &data->philos[i]) != 0)
			return (1);
		data->th_init_count++;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	data;

	memset(&data, 0, sizeof(data));
	if (parse(argc, argv, &data) == 1)
		return (1);
	if (init_mtx_f(&data) != 0)
		return (cleanup_table(&data), 1);
	if (pthread_mutex_init(&data.write_lock, NULL) != 0)
		return (err_mtx(), cleanup_table(&data), 1);
	data.wr_lock_count++;
	if (pthread_mutex_init(&data.plate_lock, NULL) != 0)
		return (err_mtx(), cleanup_table(&data), 1);
	data.pl_lock_count++;
	data.start_time = get_useconds();
	if (init_thread(&data))
		return (cleanup_table(&data), 1);
	loop_death_th(&data);
	cleanup_table(&data);
	return (0);
}
