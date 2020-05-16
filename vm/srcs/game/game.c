/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 18:48:20 by ylila             #+#    #+#             */
/*   Updated: 2020/05/16 18:48:59 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vis_tools *g_vs;

void				start_game(t_corewar *corewar)
{
	bool			quit;

	prepare_battle(corewar, &quit);
	while (!quit)
	{
		if (g_mode == -100 && corewar->flgs.set_flg & VIS_FLG)
			visualise_arena(corewar, &quit, NULL, 0);
		else
		{
			if (corewar->game_param.cycles_aft_start++ ==
			corewar->flgs.nbr_cycles_dump && corewar->flgs.set_flg & DUMP_FLG)
				print_map(corewar);
			++corewar->game_param.cycles_bfr_check;
			carriages_actions(corewar, &quit);
			if (!(corewar->game_param.cycles_bfr_check -
					corewar->game_param.cycles_to_die) ||
					corewar->game_param.cycles_to_die <= 0)
				lets_check(corewar);
			if ((corewar->flgs.set_flg & VIS_FLG) && g_change)
				visualise_arena(corewar, &quit, corewar->carriages, 0);
			if (!corewar->carriages)
				introducing_winner(corewar);
		}
	}
}

void				init_arena(unsigned char arena[], t_champion *champs,
						t_carriages **carriages, const t_flgs *flg)
{
	unsigned int	code_shift;
	int				i;

	code_shift = MEM_SIZE / champions_cnt(champs);
	i = 0;
	while (champs)
	{
		ft_memcpy(arena + i++ * code_shift, champs->file.exec_code,
				sizeof(champs->file.exec_code));
		push_front_carriage(carriages, flg);
		(*carriages)->reg[0] = -champs->num;
		(*carriages)->op_pos = arena + (i - 1) * code_shift;
		champs = champs->next;
	}
}

void				introducing_fighter(t_champion *champs)
{
	int				player;

	ft_printf("Introducing contestants...\n");
	fprintf(file, "Introducing contestants...\n");
	player = 0;
	while (champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				++player, champs->file.header.prog_size,
				champs->file.header.prog_name, champs->file.header.comment);
		fprintf(file, "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				player, champs->file.header.prog_size,
				champs->file.header.prog_name, champs->file.header.comment);
		champs = champs->next;
	}
}

void				introducing_winner(t_corewar *corewar)
{
	int				winner;

	winner = corewar->game_param.who_lst_live;
	while (corewar->champs && corewar->champs->num != winner)
		corewar->champs = corewar->champs->next;
	ft_printf("Contestant %d, \"%s\", has won !\n", corewar->champs->num,
			corewar->champs->file.header.prog_name);
	fprintf(file, "Contestant %d, \"%s\", has won !\n", corewar->champs->num,
			corewar->champs->file.header.prog_name);
	fclose(file);
	g_mode = -100;
	g_change = 1;
	if (!(corewar->flgs.set_flg & VIS_FLG))
		exit(0);
}

void				print_map(t_corewar *corewar)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (i < MEM_SIZE)
	{
		if (!j)
			ft_printf("0x%04x : ", i);
		ft_printf("%.2x", corewar->arena[i]);
		if (j < 31)
			ft_printf(" ");
		else
		{
			ft_printf("\n");
			j = -1;
		}
		i++;
		j++;
	}
	exit(5);
}
