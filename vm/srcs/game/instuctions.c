#include "vm.h"

void    live(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (!*head)
	    return ;
    /// проверка, что такой чемпион есть
    corewar->game_param.who_lst_live = arg_val->val[0];
    corewar->carriages->cycle_when_live = corewar->game_param.cycles_aft_start;
}

void    ld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
    int					val;
    unsigned int		ind_arg;

    if (!*head)
        return ;
    if (arg_val->code_args[0] == DIR_CODE)
        val = arg_val->val[0];
    else if (arg_val->code_args[0] == IND_CODE)
    {
        ind_arg = *(int *)do_steps(corewar->carriages->op_pos,
                arg_val->val[0] % IDX_MOD, corewar->arena);
        reverse_int_bytes(&ind_arg);
    }
    //corewar->carriages->reg[arg_val->val[1]] = val;
    if (!val)
        corewar->carriages->carry = 1;
    else
        corewar->carriages->carry = 0;
}
