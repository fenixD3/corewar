#include "vm.h"

void    live(t_corewar *corewar, t_parse_args *arg_val, t_carriages *head)
{
	if (arg_val->val[0] != corewar->carriages->reg[0])
		return ;
    corewar->game_param.who_lst_live = -corewar->carriages->reg[0];
    corewar->carriages->cycle_when_live = corewar->game_param.cycles_aft_start;
}
