/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:17:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/09 15:38:56 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_disp(t_time *time, t_ph *id, t_ph *name, char *status)
{
	printf("%d, %d, %s, %s.\n", time, id, name->name, print_status(status));
}

void	print_status(t_ph *philo, t_ph *state)
{
	if (state->died == 1)
		printf("died\n");
	if (state->ate == 1)
		printf("is eating\n");
	if (state->sleep == 1)
		printf("is sleeping\n");
	if (state->think == 1)
		printf("is thinking\n");
	if (state->fork == 1)
		printf("has taken a fork\n");
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
