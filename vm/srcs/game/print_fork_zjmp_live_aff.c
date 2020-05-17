/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fork_zjmp_live_aff.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:04:37 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:05:08 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_v_4_live(t_corewar *corewar, t_parse_args *arg_val,
					const char *cmd)
{
	ft_printf("P %4d | %s %d\n",
		corewar->carriages->id, cmd, arg_val->val[0]);
}

void	print_v_4_nfork(t_corewar *corewar, t_parse_args *arg_val,
					const char *cmd)
{
	ft_printf("P %4d | %s %d (%ld)\n",
		corewar->carriages->id,
		cmd,
		(int16_t)arg_val->val[0],
		corewar->carriages->op_pos + (int16_t)arg_val->val[0] %
		IDX_MOD - corewar->arena);
}

void	print_v_4_lfork(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd)
{
	ft_printf("P %4d | %s %d (%ld)\n",
		corewar->carriages->id,
		cmd,
		(int16_t)arg_val->val[0],
		corewar->carriages->op_pos + (int16_t)arg_val->val[0] - corewar->arena);
}

void	print_v_4_zjmp(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd)
{
	ft_printf("P %4d | %s %d ",
		corewar->carriages->id,
		cmd,
		(int16_t)arg_val->val[0]);
}
