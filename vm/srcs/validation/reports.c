/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:28:05 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:28:11 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_usage(void)
{
	ft_printf("Usage:\tfilename1.cor [, filename2.cor, ....]\n");
	ft_printf("\t\t[, -n <number of next player>\n");
	ft_printf("\t\t, -dump <number of cycles to dump a game>\n");
	ft_printf("\t\t, -a]\n");
	exit(5);
}

void	get_error(char *error)
{
	ft_printf("%s\n", error);
	exit(1);
}
