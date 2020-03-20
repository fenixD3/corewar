#include "vm.h"

void	start_game(t_corewar *corewar)
{
	init_arena(corewar->arena, corewar->champs, &corewar->carriages);
	introducing_fighter(corewar->champs);
	while (1)
	{
		carriages_actions(corewar);
		if (!(++corewar->game_param.cycles_aft_start %
				corewar->game_param.cycles_to_die) ||
				corewar->game_param.cycles_to_die <= 0)
			lets_check(corewar->carriages, &corewar->game_param);
		if (corewar->flgs.flgs & DUMP_FLG &&
		corewar->game_param.cycles_aft_start == corewar->flgs.nbr_cycles_dump)
			print_map(corewar);
		if (carriage_amount_live(corewar->carriages) == 1)
			introducing_winner(corewar, 0);
		else if (!carriage_amount_live(corewar->carriages))
			introducing_winner(corewar, 1);
	}
}

void	init_arena(unsigned char arena[], t_champion *champs,
					t_carriages **carriages)
{
	unsigned int		code_shift;
	int					i;

	code_shift = MEM_SIZE / champions_cnt(champs);
	i = 0;
	while (champs)
	{
		ft_memcpy(arena + i++ * code_shift, champs->file.exec_code,
				sizeof(champs->file.exec_code));
		push_front_carriage(carriages);
		(*carriages)->reg[0] = -champs->num;
		(*carriages)->op_pos = arena + (i - 1) * code_shift;
		champs = champs->next;
	}
}

void	introducing_fighter(t_champion *champs)
{
	int		player;

	ft_printf("Introducing contestants...\n");
	player = 0;
	while (champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			++player, champs->file.header.prog_size,
			champs->file.header.prog_name, champs->file.header.comment);
		champs = champs->next;
	}
}

void introducing_winner(t_corewar *corewar, _Bool who_lst_live)
{
	int		winner;

	while (!who_lst_live && corewar->carriages)
	{
		if (corewar->carriages->is_live)
		{
			winner = -corewar->carriages->reg[0];
			break ;
		}
		corewar->carriages = corewar->carriages->next;
	}
	if (who_lst_live)
		winner = corewar->game_param.who_lst_live;
	while (corewar->champs->num != winner)
		corewar->champs = corewar->champs->next;
	ft_printf("Winner is player with number %d\n", corewar->champs->num);
	exit(0);
}

void    print_map(t_corewar *corewar)
{
	int i;
	int j;

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
}