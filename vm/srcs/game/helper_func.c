#include "vm.h"

unsigned char	*do_steps(unsigned char *start, int step,
							unsigned char *arena)
{

	if (start + step > arena + MEM_SIZE - 1)
		start = arena + ((start + step - arena) % MEM_SIZE);
	else if (start + step < arena)
		start = arena + MEM_SIZE - 1 + step;
	else
		start += step;
	return (start);
}

int		reverse_vm_bytes(unsigned char *num_to_rev, int bytes,
				unsigned char *arena)
{
	int				res;

	res = 0;
	while (bytes--)
	{
		res |= *num_to_rev << (bytes * 8);
		num_to_rev = do_steps(num_to_rev, 1, arena);
	}
	return (res);
}

int		get_value_frm_arg(t_parse_args *arg_val, int arg_idx,
						t_corewar *corewar, _Bool is_idx_mod)
{
	int				val;

	if (arg_val->code_args[arg_idx] == REG_CODE)
		val = corewar->carriages->reg[arg_val->val[arg_idx] - 1];
	else if (arg_val->code_args[arg_idx] == DIR_CODE)
		val = arg_val->val[arg_idx];
	else if (arg_val->code_args[arg_idx] == IND_CODE)
	{
		if (is_idx_mod)
			val = reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
				arg_val->val[arg_idx] % IDX_MOD, corewar->arena), 4, corewar->arena);
		else
			val = reverse_vm_bytes(do_steps(corewar->carriages->op_pos,
				arg_val->val[arg_idx], corewar->arena), 4, corewar->arena);
	}
	return (val);
}

/// For -v
int		cnt_bytes_for_op(const t_op *op, const t_arg_type *code_args)
{
	int		cnt_bytes;
	int		idx;

	cnt_bytes = 1;
	idx = -1;
	if (op->argument_type_code)
		++cnt_bytes;
	while (++idx != op->num_args)
	{
		if (code_args[idx] == REG_CODE)
			++cnt_bytes;
		else if (code_args[idx] == DIR_CODE)
			cnt_bytes += op->size_t_dir;
		else if (code_args[idx] == IND_CODE)
			cnt_bytes += 2;
	}
	return (cnt_bytes);
}

void print_command_bytes(unsigned char *start_op,
						 int bytes_to_nxt,
						 unsigned char *arena)
{
	while (bytes_to_nxt--)
	{
		printf("%02x ", *start_op);
		fprintf(file, "%02x ", *start_op);
		start_op = do_steps(start_op, 1, arena);
	}
	printf("\n");
	fprintf(file, "\n");
}
