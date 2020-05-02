#include "vm.h"

void	add(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s r%d r%d r%d\n",
			   corewar->carriages->id,
			   "add",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
		fprintf(file, "P%5d | %s r%d r%d r%d\n",
				corewar->carriages->id,
				"add",
				arg_val->val[0],
				arg_val->val[1],
				arg_val->val[2]);
	}
	val = corewar->carriages->reg[arg_val->val[0] - 1] +
		corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	sub(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s r%d r%d r%d\n",
			   corewar->carriages->id,
			   "sub",
			   arg_val->val[0],
			   arg_val->val[1],
			   arg_val->val[2]);
		fprintf(file, "P%5d | %s r%d r%d r%d\n",
				corewar->carriages->id,
				"sub",
				arg_val->val[0],
				arg_val->val[1],
				arg_val->val[2]);
	}
	val = corewar->carriages->reg[arg_val->val[0] - 1] -
		corewar->carriages->reg[arg_val->val[1] - 1];
	corewar->carriages->reg[arg_val->val[2] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	and(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "and",
			   val_1,
			   val_2,
			   arg_val->val[2]);
		fprintf(file, "P%5d | %s %d %d r%d\n",
				corewar->carriages->id,
				"and",
				val_1,
				val_2,
				arg_val->val[2]);
	}
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 & val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	or(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "or",
			   val_1,
			   val_2,
			   arg_val->val[2]);
		fprintf(file, "P%5d | %s %d %d r%d\n",
				corewar->carriages->id,
				"or",
				val_1,
				val_2,
				arg_val->val[2]);
	}
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 | val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	xor(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int				val_1;
	int				val_2;

	if (!*head)
		return ;
	val_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d %d r%d\n",
			   corewar->carriages->id,
			   "xor",
			   val_1,
			   val_2,
			   arg_val->val[2]);
		fprintf(file, "P%5d | %s %d %d r%d\n",
				corewar->carriages->id,
				"xor",
				val_1,
				val_2,
				arg_val->val[2]);
	}
	corewar->carriages->reg[arg_val->val[2] - 1] = val_1 ^ val_2;
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void	aff(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("%s %c\n",
			   "Aff:", (char)corewar->carriages->reg[arg_val->val[0] - 1]);
		fprintf(file, "%s %c\n",
				"Aff:", (char)corewar->carriages->reg[arg_val->val[0] - 1]);
	}
	if (!*head || !(corewar->flgs.set_flg & A_FLG))
		return ;
	ft_printf("%c\n",
			  (char)corewar->carriages->reg[arg_val->val[0] - 1]);
}

