/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:41:50 by imutavdz          #+#    #+#             */
/*   Updated: 2026/01/04 22:41:12 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char *Aristotele;

void	think();
void	eat();
void	snore();

void cleanup_table(int num)
{
	t_table	table;

	free(table);

}

void	err_input(char **philos, int num)
{
	write(STDOUT, "wrong input\n", 11);
	cleanup_table(num);
	break ;
}

int	welcome_philos(char **philos)
{
	t_ph	*alfa;

	alfa->id = NULL;
	alfa->ate = NULL;
	alfa->died = NULL;


	if (!philos || philos < 0)
		return (err_input(philos, 2));
}

int	main(int argc, char **argv[])
{
	welcome_philos(argv[1]);
	while (they_live(*life))
	{

	}
	return (curr_situation(status));
}
