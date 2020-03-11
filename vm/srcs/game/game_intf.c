#include "vm.h"
#include "options.h"

void	carriages_actions(t_carriages *carriage)
{
	while (carriage)
	{
		if (!carriage->cycle_to_op)
		{
			carriage->op_code = *carriage->curr_pos;
			while (!valid_op_set_cycle(carriage->curr_pos, &carriage->cycle_to_op))
			{
				++carriage->curr_pos;
				carriage->op_code = *carriage->curr_pos;
			}
		}
		if (carriage->cycle_to_op == 1)
		{
			make_operation(carriage);
			carriage->cnt_bytes_to_op = get_bytes_for_step(); /// write !!!
			carriage->curr_pos += carriage->cnt_bytes_to_op;
		}
		--carriage->cycle_to_op;
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

static _Bool	check_arguments(unsigned char *args_code, t_op op)
{
	;
}

void	make_operation(t_carriages *carriage)
{
	unsigned char	idx_op;
	t_arg_type		args;

	idx_op = *carriage->curr_pos - 1;
	if (g_op[idx_op].argument_type_code)
		//check_arguments(++*start_op, g_op[idx_op]);
	else
		;
}
