#include "vm.h"
#include "options.h"

void	carriages_actions(t_carriages *carriage)
{
	while (carriage)
	{
		if (!carriage->cycle_op)
		{
			carriage->op_code = *carriage->op_pos;
			while (!valid_op_set_cycle(carriage->op_pos, &carriage->cycle_op))
			{
				++carriage->op_pos;
				carriage->op_code = *carriage->op_pos;
			}
		}
		if (carriage->cycle_op == 1)
			make_operation_and_go_next(carriage);
		--carriage->cycle_op;
		carriage = carriage->next;
	}
}

void	lets_check(t_carriages *carriage, t_game_param *game_param)
{
	while (carriage)
	{
		if (game_param->cycles_aft_start - carriage->cycle_when_live
				>= game_param->cycles_to_die)
			; /// kill carriage
		carriage = carriage->next;
	}
	if (game_param->live_period_cnt >= NBR_LIVE)
	{
		game_param->cycles_to_die -= CYCLE_DELTA;
		game_param->check_cnt = 0;
	}
	else
		++game_param->check_cnt;
	if (game_param->check_cnt == 10)
	{
		game_param->cycles_to_die -= CYCLE_DELTA;
		game_param->check_cnt = 0;
	}
}

_Bool	valid_op_set_cycle(unsigned char *start_oper, int *cycle_to_op)
{
	if (*start_oper - 1 < 0 || *start_oper - 1 > 16)
		return (0);
	*cycle_to_op = g_op[*start_oper - 1].cycle;
	return (1);
}

void	make_operation_and_go_next(t_carriages *carriage)
{
	unsigned char	idx_op;
	unsigned char	*start_op;
	t_arg_type		args[g_op[*carriage->op_pos - 1].num_args];
	int 			args_val[g_op[*carriage->op_pos - 1].num_args];

	start_op = carriage->op_pos;
	idx_op = *carriage->op_pos - 1;
	start_op = get_arguments_frm_code(++start_op, args, g_op[idx_op]);
	if (is_args_valid(args, start_op, g_op[idx_op], args_val) &&
			!(*(start_op - 1) & 0x3u))
		execute_operation(carriage, args, args_val);
	else
		carriage->op_pos = skip_op(start_op, args, g_op[idx_op]);
}

void	execute_operation(t_carriages *carriage, t_arg_type *args,
			int *args_val)
{
	;
}
