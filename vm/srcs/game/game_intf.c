#include "vm.h"
#include "options.h"

void	carriages_actions(t_corewar *corewar, bool *quit)
{
	t_carriages *carriage_head;

	carriage_head = corewar->carriages;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 2)
		call_printf_v_2_16(corewar, 0);
	while (corewar->carriages)
	{
		if (corewar->carriages->cycle_op <= 0)
		{
			corewar->carriages->op_code = *corewar->carriages->op_pos;
			if (!valid_op_set_cycle(corewar->carriages->op_pos,
					&corewar->carriages->cycle_op))
				corewar->carriages->op_pos = do_steps(
						corewar->carriages->op_pos, 1, corewar->arena);
			else if (corewar->flgs.set_flg & VIS_FLG)
				visualise_arena(corewar, quit, carriage_head);
		}
		if (corewar->carriages->cycle_op == 1)
			make_operation_and_go_next(corewar, &carriage_head);
		--corewar->carriages->cycle_op;
		corewar->carriages = corewar->carriages->next;
	}
	corewar->carriages = carriage_head;
}

void	lets_check(t_corewar *corewar)
{
	t_carriages	*carriage;

	carriage = corewar->carriages;
	while (carriage)
	{
		if (corewar->game_param.cycles_aft_start - carriage->cycle_when_live
				>= corewar->game_param.cycles_to_die)
			carriage = delete_carriage(corewar, carriage->id);
		carriage = (carriage) ? carriage->next : corewar->carriages;
	}
	decrease_cycles_to_die(corewar);
	corewar->game_param.live_period_cnt = 0;
	corewar->game_param.cycles_bfr_check = 0;
}

void	decrease_cycles_to_die(t_corewar *corewar)
{
	if (corewar->game_param.live_period_cnt >= NBR_LIVE)
	{
		corewar->game_param.cycles_to_die -= CYCLE_DELTA;
		if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 2)
			call_printf_v_2_16(corewar, 1);
		corewar->game_param.check_cnt = 0;
		g_change = 1;
	}
	else
		++corewar->game_param.check_cnt;
	if (corewar->game_param.check_cnt == MAX_CHECKS)
	{
		corewar->game_param.cycles_to_die -= CYCLE_DELTA;
		if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 2)
			call_printf_v_2_16(corewar, 1);
		corewar->game_param.check_cnt = 0;
		g_change = 1;
	}
}

_Bool	valid_op_set_cycle(unsigned char *start_oper, int *cycle_to_op)
{
	if (*start_oper - 1 < 0 || *start_oper - 1 > 16)
		return (0);
	*cycle_to_op = g_op[*start_oper - 1].cycle;
	return (1);
}

void	make_operation_and_go_next(t_corewar *corewar,
				t_carriages **carriage_head)
{
	unsigned char	idx_op;
	unsigned char	*start_op;
	t_parse_args	args_val;

	g_change = 1;
	start_op = corewar->carriages->op_pos;
	idx_op = corewar->carriages->op_code - 1;
	start_op = get_arguments_frm_code(start_op, args_val.code_args,
			g_op[idx_op], corewar->arena);
	if (is_args_valid(&args_val, start_op, &g_op[idx_op], corewar->arena))
		(*g_instrs_ptr[idx_op])(corewar, &args_val, carriage_head);
	if (corewar->carriages->op_code != 9 ||
	(corewar->carriages->op_code == 9 && !corewar->carriages->carry))
		start_op = skip_op(start_op, args_val.code_args,
				g_op[idx_op], corewar->arena);
	else
		start_op = corewar->carriages->op_pos;
	corewar->carriages->cnt_bytes_to_op = cnt_bytes_for_op(&g_op[idx_op],
														args_val.code_args);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 16 &&
	(corewar->carriages->op_code != 9 || (corewar->carriages->op_code == 9 &&
												!corewar->carriages->carry)))
		call_printf_v_2_16(corewar, 0);
	corewar->carriages->op_pos = start_op;
}
