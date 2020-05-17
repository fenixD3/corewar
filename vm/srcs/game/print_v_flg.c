/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_v_flg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 13:56:04 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 13:58:52 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	call_printf_v_2(t_corewar *corewar, _Bool printf_cycle_die)
{
	if (printf_cycle_die)
	{
		ft_printf("Cycle to die is now %ld\n",
			corewar->game_param.cycles_to_die);
	}
	else
	{
		ft_printf("It is now cycle %ld\n",
			corewar->game_param.cycles_aft_start);
	}
}

void	call_printf_v_16(t_corewar *corewar)
{
	ft_printf("ADV %d (%s%04lx -> %s%04lx) ",
			corewar->carriages->cnt_bytes_to_op,
			"0x",
			(corewar->carriages->op_pos - corewar->arena),
			"0x",
			(corewar->carriages->op_pos + corewar->carriages->cnt_bytes_to_op
			- corewar->arena));
}

void	call_printf_v_1(const t_corewar *corewar, const t_champion *champ)
{
	ft_printf("Player %d (%s) is said to be alive\n",
			corewar->game_param.who_lst_live, champ->file.header.prog_name);
}

void	call_printf_v_8(const t_corewar *corewar, const t_carriages *carriage,
					int search_id)
{
	ft_printf("Process %d hasn't lived for %ld cycles (CTD %ld)\n",
			search_id,
			corewar->game_param.cycles_aft_start - carriage->cycle_when_live,
			corewar->game_param.cycles_to_die);
}
