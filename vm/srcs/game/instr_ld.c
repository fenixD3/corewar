/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 18:48:20 by ylila             #+#    #+#             */
/*   Updated: 2020/05/16 18:48:59 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	val = get_value_frm_arg(arg_val, 0, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "ld");
	corewar->carriages->reg[arg_val->val[1] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void		ldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val_addr_1;
	int		val_addr_2;

	if (!*head)
		return ;
	if (arg_val->code_args[0] == DIR_CODE)
		val_addr_1 = (int16_t)get_value_frm_arg(arg_val, 0, corewar, 1);
	else
		val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	if (arg_val->code_args[1] == DIR_CODE)
		val_addr_2 = (int16_t)get_value_frm_arg(arg_val, 1, corewar, 1);
	else
		val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "ldi");
	corewar->carriages->reg[arg_val->val[2] - 1] =
		reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena), 4, corewar->arena);
}

void		lld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	val = get_value_frm_arg(arg_val, 0, corewar, 0);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "lld");
	corewar->carriages->reg[arg_val->val[1] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void		lldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val_addr_1;
	int		val_addr_2;

	if (!*head)
		return ;
	if (arg_val->code_args[0] == DIR_CODE)
		val_addr_1 = (int16_t)get_value_frm_arg(arg_val, 0, corewar, 1);
	else
		val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	if (arg_val->code_args[1] == DIR_CODE)
		val_addr_2 = (int16_t)get_value_frm_arg(arg_val, 1, corewar, 0);
	else
		val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 0);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "lldi");
	corewar->carriages->reg[arg_val->val[2] - 1] =
		reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
			(val_addr_1 + val_addr_2), corewar->arena), 4, corewar->arena);
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}
