#include "vm.h"

void	print_v_4_st(t_corewar *corewar, t_parse_args *arg_val,
					 const char *cmd)
{
	printf("P%5d | %s r%d %d\n",
		   corewar->carriages->id,
		   cmd,
		   arg_val->val[0],
		   (arg_val->code_args[1] == IND_CODE) ?
		   (int16_t)arg_val->val[1] : arg_val->val[1]);
	fprintf(file, "P%5d | %s r%d %d\n",
			corewar->carriages->id,
			cmd,
			arg_val->val[0],
			(arg_val->code_args[1] == IND_CODE) ?
			(int16_t)arg_val->val[1] : arg_val->val[1]);
}

void	print_v_4_sti(t_corewar *corewar, t_parse_args *arg_val,
					 const char *cmd)
{
	unsigned char	*ind_pos;
	int				val_addr_1;
	int				val_addr_2;

	if (arg_val->code_args[1] == DIR_CODE)
		val_addr_1 = (int16_t)get_value_frm_arg(arg_val, 1, corewar, 1);
	else
		val_addr_1 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (arg_val->code_args[2] == DIR_CODE)
		val_addr_2 = (int16_t)get_value_frm_arg(arg_val, 2, corewar, 1);
	else
		val_addr_2 = get_value_frm_arg(arg_val, 2, corewar, 1);
	ind_pos = do_steps(corewar->carriages->op_pos,
					   (val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena);
	printf("P%5d | %s r%d %d %d\n"
		"       | -> store to %d + %d = %d (with pc and mod %ld)\n",
		corewar->carriages->id, cmd, arg_val->val[0], val_addr_1, val_addr_2,
		val_addr_1, val_addr_2, val_addr_1 + val_addr_2,
		((val_addr_1 + val_addr_2) % IDX_MOD < 0 && corewar->carriages->op_pos +
			(val_addr_1 + val_addr_2) % IDX_MOD < corewar->arena)
		? ind_pos - corewar->arena - MEM_SIZE : ind_pos - corewar->arena);
	fprintf(file,
			"P%5d | %s r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %ld)\n",
			corewar->carriages->id,
			cmd,
			arg_val->val[0],
			val_addr_1,
			val_addr_2,
			val_addr_1,
			val_addr_2,
			val_addr_1 + val_addr_2,
			((val_addr_1 + val_addr_2) % IDX_MOD < 0 && corewar->carriages->op_pos + (val_addr_1 + val_addr_2) % IDX_MOD < corewar->arena)
			? ind_pos - corewar->arena - MEM_SIZE
			: ind_pos - corewar->arena);
}
