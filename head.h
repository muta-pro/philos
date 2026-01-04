/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:50:12 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/04 22:46:59 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

#include <unistd.h>
#include <stdlib.h>

typedef struct ph
{
	int id;
	int died;
	int ate;
	int life;
}	t_ph;


typedef struct die
{

}	t_die;

typedef struct eat
{

}	t_eat;

typedef struct sleep
{

}	t_sleep;

typedef struct time
{
	t_die	death;
	t_eat	eat;
	t_sleep snore;
}	t_time;

#endif