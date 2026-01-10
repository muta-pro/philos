/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:51:37 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/09 15:38:55 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char *list_names(char *name)
{
	name[] = {10};

	name[0] = Aristotle;
	name[1] = Platone;
	name[2] = Schopehauer;
	name[3] = Kant;
	name[4] = Epicurus;
	name[5] = Locke;
	name[6] = Marx;
	name[7] = Confucius;
	name[8] = Socrates;
	name[9] = Nietzsche;
}
void assign_name(char *name, t_ph *philo)
{
	int i;

	i = 0;
	while (philo->id[i])
	{
		philo->name[i] = paste_name(name[i]);
		return (philo.name);
	}
}