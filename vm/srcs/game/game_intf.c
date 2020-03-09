#include "vm.h"
#include "options.h"

void	carriages_actions(t_carriages *carriage, t_game_param game_param)
{
	while (carriage)
	{
		if (!carriage->cycle_to_op)
		{
			carriage->op_code = *carriage->curr_pos;
			validate_operation(carriage->curr_pos);
			/// if validation is false then make one byte step
			/// if validation OK - update operation cycle
		}
		else if (carriage->cycle_to_op == 1)
		{
			/// do operation
			carriage->cnt_bytes_to_op = get_bytes_for_step();
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

_Bool	validate_operation(unsigned char *start_oper)
{
	t_op	*curr_op;

	if (*start_oper - 1 < 0 || *start_oper - 1 > 16)
		return (0);
	curr_op = &g_op[*start_oper - 1];
	if (curr_op->argument_type_code)
		++start_oper;
	++start_oper;
}
