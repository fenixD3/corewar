#include "vm.h"

void	st(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val;
	unsigned char	*ind_pos;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s r%d %d\n",
			   corewar->carriages->id,
			   "st",
			   arg_val->val[0],
			   arg_val->val[1]);
		fprintf(file, "P%5d | %s r%d %d\n",
				corewar->carriages->id,
				"st",
				arg_val->val[0],
				arg_val->val[1]);
	}
	val = corewar->carriages->reg[arg_val->code_args[0] - 1];
	if (arg_val->code_args[1] == REG_CODE)
		corewar->carriages->reg[arg_val->val[1] - 1] = val;
	else if (arg_val->code_args[1] == IND_CODE)
	{
		ind_pos = do_steps(corewar->carriages->op_pos,
						   arg_val->val[1] % IDX_MOD, corewar->arena);
		i = 4;
		val_ptr = (unsigned char *)&val;
		while (--i >= 0)
		{
			*ind_pos = *(val_ptr + i);
			ind_pos = do_steps(ind_pos, 1, corewar->arena);
		}
	}
}

void	sti(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	unsigned char	*ind_pos;
	int				val_addr_1;
	int				val_addr_2;
	int				i;
	unsigned char	*val_ptr;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 1, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 2, corewar, 1);
	ind_pos = do_steps(corewar->carriages->op_pos,
					   (val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %ld)\n",
			   corewar->carriages->id,
			   "sti",
			   arg_val->val[0],
			   val_addr_1,
			   val_addr_2,
			   val_addr_1,
			   val_addr_2,
			   val_addr_1 + val_addr_2,
			   ind_pos - corewar->arena);
		fprintf(file,
				"P%5d | %s r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %ld)\n",
				corewar->carriages->id,
				"sti",
				arg_val->val[0],
				val_addr_1,
				val_addr_2,
				val_addr_1,
				val_addr_2,
				val_addr_1 + val_addr_2,
				ind_pos - corewar->arena);
	}
	i = 4;
	val_ptr = (unsigned char *)&corewar->carriages->reg[arg_val->val[0] - 1];
	while (--i >= 0)
	{
		*ind_pos = *(val_ptr + i);
		ind_pos = do_steps(ind_pos, 1, corewar->arena);
	}
}
