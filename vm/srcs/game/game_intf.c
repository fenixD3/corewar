#include "vm.h"
#include "options.h"

void	carriages_actions(t_corewar *corewar)
{
	t_carriages *carriage_head;

	carriage_head = corewar->carriages;
	while (corewar->carriages)
	{
		if (corewar->carriages->is_live && !corewar->carriages->cycle_op)
		{
			corewar->carriages->op_code = *corewar->carriages->op_pos;
			while (!valid_op_set_cycle(corewar->carriages->op_pos,
					&corewar->carriages->cycle_op))
			{
				corewar->carriages->op_pos = do_steps
						(corewar->carriages->op_pos, 1, corewar->arena);
				corewar->carriages->op_code = *corewar->carriages->op_pos;
			}
		}
		if (corewar->carriages->is_live && corewar->carriages->cycle_op == 1)
			make_operation_and_go_next(corewar, &carriage_head);
		--corewar->carriages->cycle_op;
		corewar->carriages = corewar->carriages->next;
	}
	corewar->carriages = carriage_head;
}

void	lets_check(t_carriages *carriage, t_game_param *game_param)
{
	while (carriage)
	{
		if (carriage->is_live &&
				game_param->cycles_aft_start - carriage->cycle_when_live
				>= game_param->cycles_to_die)
			carriage->is_live = 0;
		carriage = carriage->next;
	}
	if (game_param->live_period_cnt >= NBR_LIVE)
	{
		game_param->cycles_to_die -= CYCLE_DELTA;
		game_param->check_cnt = 0;
	}
	else
		++game_param->check_cnt;
	if (game_param->check_cnt == MAX_CHECKS)
	{
		game_param->cycles_to_die -= CYCLE_DELTA;
		game_param->check_cnt = 0;
	}
	game_param->live_period_cnt = 0;
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


	//TODO add global variable to call visualisation!
	g_change = 1;
	start_op = corewar->carriages->op_pos;
	idx_op = *corewar->carriages->op_pos - 1;
	start_op = get_arguments_frm_code(start_op, args_val.code_args,
			g_op[idx_op], corewar->arena);
	if (is_args_valid(&args_val, start_op, &g_op[idx_op], corewar->arena) &&
			!(*(start_op - 1) & 0x3u))
		(*instrs_ptr[idx_op])(corewar, &args_val, carriage_head);
	else
		corewar->carriages->op_pos = skip_op(start_op, args_val.code_args,
				g_op[idx_op], corewar->arena);
}

