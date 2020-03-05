/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 20:17:41 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/07 20:17:43 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

# include "op.h"

typedef struct	s_op
{
	char	*name;
	int		num_args;
	int		args_type[3];
	int		code;
	int		cycle;
	_Bool	argument_type_code;
	int		size_t_dir;

}				t_op;

t_op	g_op[17] = {
	{"live", 1, {T_DIR, 0, 0}, 1, 10, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 4},
	{
		"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 4
	},
	{
		"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 4
	},
	{
		"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 4
	},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 2},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 2},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, 0, 2},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, 1, 4},
	{0, 0, {0}, 0, 0, 0, 0}
};

#endif
