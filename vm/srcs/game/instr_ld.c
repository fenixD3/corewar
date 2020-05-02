#include "vm.h"

void    ld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int		val;

	if (!*head)
		return ;
	val = get_value_frm_arg(arg_val, 0, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d r%d\n",
			   corewar->carriages->id,
			   "ld",
			   val,
			   arg_val->val[1]);
		fprintf(file,
				"P%5d | %s %d r%d\n",
				corewar->carriages->id,
				"ld",
				val,
				arg_val->val[1]);
	}
	corewar->carriages->reg[arg_val->val[1] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void    ldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val_addr_1;
	int					val_addr_2;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 1);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %ld)\n",
			   corewar->carriages->id,
			   "ldi",
			   val_addr_1,
			   val_addr_2,
			   arg_val->val[2],
			   val_addr_1,
			   val_addr_2,
			   val_addr_1 + val_addr_2,
			   do_steps(corewar->carriages->op_pos,
			   	(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena) - corewar->arena);
		fprintf(file,
				"P%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %ld)\n",
				corewar->carriages->id,
				"ldi",
				val_addr_1,
				val_addr_2,
				arg_val->val[2],
				val_addr_1,
				val_addr_2,
				val_addr_1 + val_addr_2,
				do_steps(corewar->carriages->op_pos,
					(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena) - corewar->arena);
	}
	corewar->carriages->reg[arg_val->val[2] - 1] =
		reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
			(val_addr_1 + val_addr_2) % IDX_MOD, corewar->arena), 4, corewar->arena);
}

void    lld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val;

	if (!*head)
		return ;
	val = get_value_frm_arg(arg_val, 0, corewar, 0);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d r%d\n",
			   corewar->carriages->id,
			   "lld",
			   val,
			   arg_val->val[1]);
		fprintf(file, "P%5d | %s %d r%d\n",
				corewar->carriages->id,
				"lld",
				val,
				arg_val->val[1]);
	}
	corewar->carriages->reg[arg_val->val[1] - 1] = val;
	if (!val)
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}

void    lldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head)
{
	int					val_addr_1;
	int					val_addr_2;

	if (!*head)
		return ;
	val_addr_1 = get_value_frm_arg(arg_val, 0, corewar, 1);
	val_addr_2 = get_value_frm_arg(arg_val, 1, corewar, 0);
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 4) {
		printf("P%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc %ld)\n",
			   corewar->carriages->id,
			   "lldi",
			   val_addr_1,
			   val_addr_2,
			   arg_val->val[2],
			   val_addr_1,
			   val_addr_2,
			   val_addr_1 + val_addr_2,
			   do_steps(corewar->carriages->op_pos,
						(val_addr_1 + val_addr_2), corewar->arena) - corewar->arena);
		fprintf(file, "P%5d | %s %d %d r%d\n       | -> load from %d + %d = %d (with pc %ld)\n",
				corewar->carriages->id,
				"lldi",
				val_addr_1,
				val_addr_2,
				arg_val->val[2],
				val_addr_1,
				val_addr_2,
				val_addr_1 + val_addr_2,
				do_steps(corewar->carriages->op_pos,
						 (val_addr_1 + val_addr_2), corewar->arena) - corewar->arena);
	}
	corewar->carriages->reg[arg_val->val[2] - 1] =
		reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
			(val_addr_1 + val_addr_2), corewar->arena), 4, corewar->arena);
	if (!corewar->carriages->reg[arg_val->val[2] - 1])
		corewar->carriages->carry = 1;
	else
		corewar->carriages->carry = 0;
}