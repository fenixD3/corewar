#include "vm.h"

void	live(t_carriages *carriage, const t_parse_args *arg_val,
				t_game_param *game_param)
{
	if (arg_val->val[0] != carriage->reg[0])
		return ;
	game_param->who_lst_live = -carriage->reg[0];
	carriage->cycle_when_live = game_param->cycles_aft_start;
}
