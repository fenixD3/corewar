/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_st.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:05:19 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:05:51 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		st(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val;
	unsigned char	*ind_pos;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "st");
	val = corewar->carriages->reg[arg_val->val[0] - 1];
	if (arg_val->code_args[1] == REG_CODE)
		corewar->carriages->reg[arg_val->val[1] - 1] = val;
	else if (arg_val->code_args[1] == IND_CODE)
	{
		ind_pos = do_steps(corewar->carriages->op_pos,
			(int16_t)arg_val->val[1] % IDX_MOD, corewar->arena);
		i = 4;
		val_ptr = (unsigned char *)&val;
		while (--i >= 0)
		{
			*ind_pos = *(val_ptr + i);
			ind_pos = do_steps(ind_pos, 1, corewar->arena);
		}
	}
}

static void	help_sti(t_corewar *corewar, t_parse_args *arg_val, int *val_addr_1,
						int *val_addr_2)
{
	if (arg_val->code_args[1] == DIR_CODE)
		*val_addr_1 = (int16_t)get_value_frm_arg(arg_val, 1, corewar, 1);
	else
		*val_addr_1 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (arg_val->code_args[2] == DIR_CODE)
		*val_addr_2 = (int16_t)get_value_frm_arg(arg_val, 2, corewar, 1);
	else
		*val_addr_2 = get_value_frm_arg(arg_val, 2, corewar, 1);
}

void		sti(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	unsigned char	*ind_pos;
	int				val_addr_1;
	int				val_addr_2;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	help_sti(corewar, arg_val, &val_addr_1, &val_addr_2);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "sti");
	ind_pos = do_steps(corewar->carriages->op_pos,
		(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena);
	i = 4;
	val_ptr = (unsigned char *)&corewar->carriages->reg[arg_val->val[0] - 1];
	while (--i >= 0)
	{
		*ind_pos = *(val_ptr + i);
		ind_pos = do_steps(ind_pos, 1, corewar->arena);
	}
}
