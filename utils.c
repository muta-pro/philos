/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:17:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/10 05:43:32 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

size_t	get_useconds(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	ft_usleep(long ms, t_ph *philo)
{
	long	start_time;

	start_time = get_useconds();
	while (get_useconds() - start_time < ms)
	{
		if (!they_live(philo))
			break ;
		usleep(500);
	}
}

void	print_display(t_ph *philo, char *status)
{
	long	cur_time_ms;

	cur_time_ms = get_useconds() - philo->data->start_time;
	printf("%zu, %d, %s.\n", cur_time_ms, philo->id, status);
}

int	ft_atoi(const char *str)
{
	int	result;
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
