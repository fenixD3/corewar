#include "vm.h"

void	print_v_4_add(t_corewar *corewar, t_parse_args *arg_val,
					  const char *cmd)
{
	printf("P%5d | %s r%d r%d r%d\n",
		   corewar->carriages->id,
		   cmd,
		   arg_val->val[0],
		   arg_val->val[1],
		   arg_val->val[2]);
	fprintf(file, "P%5d | %s r%d r%d r%d\n",
			corewar->carriages->id,
			cmd,
			arg_val->val[0],
			arg_val->val[1],
			arg_val->val[2]);
}

void	print_v_4_sub(t_corewar *corewar, t_parse_args *arg_val,
					  const char *cmd)
{
	printf("P%5d | %s r%d r%d r%d\n",
		   corewar->carriages->id,
		   cmd,
		   arg_val->val[0],
		   arg_val->val[1],
		   arg_val->val[2]);
	fprintf(file, "P%5d | %s r%d r%d r%d\n",
			corewar->carriages->id,
			cmd,
			arg_val->val[0],
			arg_val->val[1],
			arg_val->val[2]);
}

void	print_v_4_and(t_corewar *corewar, t_parse_args *arg_val,
					  const char *cmd)
{
	int				val_1;
	int				val_2;

	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	printf("P%5d | %s %d %d r%d\n",
		   corewar->carriages->id,
		   cmd,
		   val_1,
		   val_2,
		   arg_val->val[2]);
	fprintf(file, "P%5d | %s %d %d r%d\n",
			corewar->carriages->id,
			cmd,
			val_1,
			val_2,
			arg_val->val[2]);
}

void	print_v_4_or(t_corewar *corewar, t_parse_args *arg_val,
					  const char *cmd)
{
	int				val_1;
	int				val_2;

	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	printf("P%5d | %s %d %d r%d\n",
		   corewar->carriages->id,
		   cmd,
		   val_1,
		   val_2,
		   arg_val->val[2]);
	fprintf(file, "P%5d | %s %d %d r%d\n",
			corewar->carriages->id,
			cmd,
			val_1,
			val_2,
			arg_val->val[2]);
}

void	print_v_4_xor(t_corewar *corewar, t_parse_args *arg_val,
					 const char *cmd)
{
	int				val_1;
	int				val_2;

	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	printf("P%5d | %s %d %d r%d\n",
		   corewar->carriages->id,
		   cmd,
		   val_1,
		   val_2,
		   arg_val->val[2]);
	fprintf(file, "P%5d | %s %d %d r%d\n",
			corewar->carriages->id,
			cmd,
			val_1,
			val_2,
			arg_val->val[2]);
}