/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 18:48:20 by ylila             #+#    #+#             */
/*   Updated: 2020/05/16 18:48:59 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		add(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	val = corewar->carriages->reg[arg_val->val[0] - 1] +
		corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "add");
}

void		sub(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	val = corewar->carriages->reg[arg_val->val[0] - 1] -
		corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "sub");
}

void		and(t_corewar *corewar, t_parse_args *arg_val,
													t_carriages **head)
{
	int		val_1;
	int		val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "and");
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 & val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void		or(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val_1;
	int		val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "or");
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 | val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void		xor(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val_1;
	int		val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "xor");
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 ^ val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}
