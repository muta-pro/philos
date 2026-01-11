/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:08:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/12 00:52:23 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	*assign_philos(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_ate = 0;
		data->philos[i].data = data;
		data->philos[i].left_f = i;
		data->philos[i].right_f = (i + 1) % data->num_of_philos;
		i++;
	}
	return (data->philos);
}

int	alloc_philos(t_info *data)
{
	data->philos = malloc(sizeof(t_ph) * data->num_of_philos);
	if (!data->philos)
		return (err_mem(), 1);
	data->forks = malloc(sizeof(t_f) * data->num_of_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (err_mem(), 1);
	}
	data->stop = RUN_SIM;
	assign_philos(data);
	return (0);
}

int is_num(char *argv)
{
	int i;

	i = 0;
	if (!argv  || !argv[i])
		return (1);
	if (argv[i] == '+')
		i++;
	if (!argv[i])
		return (1);
	while (argv[i])
	{
		if (argv[i] < 48 || argv[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	save_time(int argc, char **argv, t_info *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("invalid args\n");
		return (1);
	}
	if (is_num(argv[1]) || is_num(argv[2]) || is_num(argv[3]) || is_num(argv[4])
		||  (argc == 6 && is_num(argv[5])))
		return (err_input(), 1);
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->count_must_eat = ft_atoi(argv[5]);
	else
		data->count_must_eat = -1;
	if (data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || data->num_of_philos < 1)
		return (err_input(), 1);
	return (0);
}

int	parse(int argc, char **argv, t_info *data)
{
	if (argc == 1)
		return (err_input(), 1);
	if(save_time(argc, argv, data))
		return (1);
	if(alloc_philos(data))
		return (1);
	return (0);
}