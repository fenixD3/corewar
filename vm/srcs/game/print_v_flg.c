#include "vm.h"

void	call_printf_v_2_16(t_corewar *corewar, _Bool printf_cycle_die)
{
	if (corewar->flgs.verb_num & 2)
	{
		printf("It is now cycle %ld\n", corewar->game_param.cycles_aft_start);
		fprintf(file, "It is now cycle %ld\n", corewar->game_param.cycles_aft_start);
		if (printf_cycle_die)
		{
			printf("Cycle to die is now %ld\n",
				corewar->game_param.cycles_to_die);
			fprintf(file, "Cycle to die is now %ld\n", corewar->game_param.cycles_to_die);
		}
	}
	else if (corewar->flgs.verb_num & 16)
	{
		printf("ADV %d (%s%04lx -> %s%04lx) ",
			corewar->carriages->cnt_bytes_to_op,
			"0x",
			(corewar->carriages->op_pos - corewar->arena),
			"0x",
			(corewar->carriages->op_pos + corewar->carriages->cnt_bytes_to_op - corewar->arena));
		fprintf(file,
				"ADV %d (%s%04lx -> %s%04lx) ",
				corewar->carriages->cnt_bytes_to_op,
				"0x",
				(corewar->carriages->op_pos - corewar->arena),
				"0x",
				(corewar->carriages->op_pos + corewar->carriages->cnt_bytes_to_op - corewar->arena));
		print_command_bytes(corewar->carriages->op_pos,
			corewar->carriages->cnt_bytes_to_op, corewar->arena);
	}
}

void	call_printf_v_1_8(const t_corewar *corewar, const t_champion *champ,
						  const t_carriages *carriage, int search_id)
{
	if (corewar->flgs.verb_num & 1)
	{
		printf("Player %d (%s) is said to be alive\n",
			   corewar->game_param.who_lst_live, champ->file.header.prog_name);
		fprintf(file, "Player %d (%s) is said to be alive\n",
				corewar->game_param.who_lst_live, champ->file.header.prog_name);
	}
	else if (corewar->flgs.verb_num & 8)
	{
		printf("Process %d hasn't lived for %ld cycles (CTD %ld)\n",
			search_id,
			corewar->game_param.cycles_aft_start - carriage->cycle_when_live,
			corewar->game_param.cycles_to_die);
		fprintf(file, "Process %d hasn't lived for %ld cycles (CTD %ld)\n",
			search_id,
			corewar->game_param.cycles_aft_start - carriage->cycle_when_live,
			corewar->game_param.cycles_to_die);
	}
}

static void	call_printf_v_4_another(t_corewar *corewar, t_parse_args *arg_val,
								const char *cmd)
{
	if (ft_strequ(cmd, "st"))
		print_v_4_st(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "sti"))
		print_v_4_sti(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "add"))
		print_v_4_add(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "sub"))
		print_v_4_sub(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "and"))
		print_v_4_and(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "or"))
		print_v_4_or(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "xor"))
		print_v_4_xor(corewar, arg_val, cmd);
}

void		call_printf_v_4(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd)
{
	if (ft_strequ(cmd, "live"))
		print_v_4_live(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "fork"))
		print_v_4_nfork(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "lfork"))
		print_v_4_lfork(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "zjmp"))
		print_v_4_zjmp(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "Aff:"))
		print_v_4_aff(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "ld"))
		print_v_4_ld(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "ldi"))
		print_v_4_ldi(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "lld"))
		print_v_4_lld(corewar, arg_val, cmd);
	else if (ft_strequ(cmd, "lldi"))
		print_v_4_lldi(corewar, arg_val, cmd);
	else
		call_printf_v_4_another(corewar, arg_val, cmd);
}
