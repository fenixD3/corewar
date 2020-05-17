/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:28:05 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:28:11 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int ac, char **av)
{
	t_corewar	corewar;

	if (ac == 1)
		get_usage();
	init_struct(&corewar);
	parse_arguments(ac, av, &corewar);
	start_game(&corewar);
	return (0);
}
