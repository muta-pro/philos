/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:08:38 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/10 20:36:36 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	err_input(void)
{
	write(STDOUT_FILENO, "Wrong input\n", 12);
}

void	err_mem(void)
{
	write(STDOUT_FILENO, "Malloc failed\n", 14);
}
void	err_mtx(void)
{
	write(STDOUT_FILENO, "Init mutex failed\n", 18);
}
