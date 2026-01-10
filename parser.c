/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:08:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/10 23:56:10 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_ph	*assign_philos(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_ate = 0;
		data->philos[i].last_meal_ms = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_of_philos];
		i++;
	}
	return (data->philos);
}

int	alloc_philos(t_info *data)
{
	data->philos = malloc(sizeof(t_ph) * data->num_of_philos);
	if (!data->philos)
		return (err_mem(), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (err_mem(), 1);
	}
	data->stop = RUN_SIM;
	assign_philos(data);
	return (0);
}

int	save_time(int argc, char **argv, t_info *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("invalid args\n");
		return (0);
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->count_must_eat = ft_atoi(argv[5]);
	if (!argv[5])
		data->count_must_eat = -1;
	if (data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || data->num_of_philos < 1)
		return (err_input(), 1);
	return (0);
}

int	parse(int argc, char **argv, t_info *data)
{
	data->num_of_philos = ft_atoi(argv[1]);
	if (data->num_of_philos < 1)
		return (err_input(), 1);
	if(save_time(argc, argv, data))
		return (1);
	if(alloc_philos(data))
		return (1);
	return (0);
}