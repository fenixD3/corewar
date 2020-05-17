/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_fork_zjmp_live_aff.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 18:48:20 by ylila             #+#    #+#             */
/*   Updated: 2020/05/16 18:48:59 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			live(t_corewar *corewar, t_parse_args *arg_val,
													t_carriages **head)
{
	t_champion	*champ;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "live");
	++corewar->game_param.live_period_cnt;
	corewar->carriages->cycle_when_live = corewar->game_param.cycles_aft_start;
	champ = corewar->champs;
	while (champ)
	{
		if (champ->num == -arg_val->val[0])
		{
			corewar->game_param.who_lst_live = -arg_val->val[0];
			if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 1)
				call_printf_v_1(corewar, champ);
			break ;
		}
		champ = champ->next;
	}
}

void			zjump(t_corewar *corewar, t_parse_args *arg_val,
														t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "zjmp");
	if (!corewar->carriages->carry || !*head)
	{
		if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		{
			ft_printf("FAILED\n");
			fprintf(file, "FAILED\n");
		}
		return ;
	}
	corewar->carriages->op_pos = do_steps(corewar->carriages->op_pos,
		(int16_t)arg_val->val[0] % IDX_MOD, corewar->arena);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
	{
		ft_printf("OK\n");
		fprintf(file, "OK\n");
	}
}

void			nfork(t_corewar *corewar, t_parse_args *arg_val,
													t_carriages **head)
{
	push_front_carriage(head, &corewar->flgs);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
			sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
		(int16_t)arg_val->val[0] % IDX_MOD, corewar->arena);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "fork");
}

void			lfork(t_corewar *corewar, t_parse_args *arg_val,
													t_carriages **head)
{
	push_front_carriage(head, &corewar->flgs);
	(*head)->carry = corewar->carriages->carry;
	(*head)->cycle_when_live = corewar->carriages->cycle_when_live;
	ft_memcpy((*head)->reg, corewar->carriages->reg,
				sizeof(corewar->carriages->reg));
	(*head)->op_pos = do_steps(corewar->carriages->op_pos,
		(int16_t)arg_val->val[0], corewar->arena);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "lfork");
}

void			aff(t_corewar *corewar, t_parse_args *arg_val,
													t_carriages **head)
{
	if (!*head || !(corewar->flgs.set_flg & A_FLG))
		return ;
	ft_printf("%s %c\n",
			  "Aff: ", (char)corewar->carriages->reg[arg_val->val[0] - 1]);
	fprintf(file, "%s %c\n",
			"Aff: ", (char)corewar->carriages->reg[arg_val->val[0] - 1]);
	ft_printf("%c\n",
				(char)corewar->carriages->reg[arg_val->val[0] - 1]);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4)
		call_printf_v_4(corewar, arg_val, "Aff:");
}
