#include "vm.h"

void	start_game(t_corewar *corewar)
{
	init_arena(corewar->arena, corewar->champs, &corewar->carriages);
	introducing_fighter(corewar->champs);
	while (corewar->game_param.cycles_to_die)
	{
		carriages_actions(corewar);
		if (!(++corewar->game_param.cycles_aft_start %
				corewar->game_param.cycles_to_die) ||
				corewar->game_param.cycles_to_die <= 0)
			lets_check(corewar->carriages, &corewar->game_param);
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
