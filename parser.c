/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:08:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/10 03:10:01 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int parse(t_info *data)
{

}

int	welcome_philos(char **num_philos, t_info forks)
{
	t_ph	*philo;
	

	if (!data->num_of_philos < 1)
		return (1);
	forks = has_fork(forks.left_fork);
	if (num_philos != forks)
		return (1);
	if (num_philos == 1)
	{
		alfa->forks = has_fork(left_fork);
		time_to_die;
		has_starved();
	}

}

int	save_time(int argc, char **argv, t_info *data)
{
	if (argc < 5 && argc > 6)
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
	{
		err_input();
		return (1);
	}
	return (0);
}
