#include "vm.h"

unsigned char	*do_steps(unsigned char *start, int step,
							unsigned char *arena)
{

	if (start + step > arena + MEM_SIZE - 1)
		start = arena + ((start + step - arena) % MEM_SIZE);
	else
		start += step;
	return (start);
}

short	reverse_vm_short_bytes(unsigned short *num_to_rev)
{
	unsigned short	rev;
	unsigned short	byte;
	unsigned short	i;

	rev = 0;
	i = 0;
	while (i < 16)
	{
		byte = *num_to_rev >> i & 0xFFu;
		rev |= byte << (16u - 8u - i);
		i += 8;
	}
	return ((short)rev);
}

int		reverse_vm_int_bytes(unsigned int *num_to_rev)
{
	unsigned int	rev;
	unsigned int	byte;
	unsigned int	i;

	rev = 0;
	i = 0;
	while (i < 32)
	{
		byte = *num_to_rev >> i & 0xFFu;
		rev |= byte << (32u - 8u - i);
		i += 8;
	}
	return ((int)rev);
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
	unsigned int	*ind_pos;

	if (arg_val->code_args[arg_idx] == REG_CODE)
		val = corewar->carriages->reg[arg_val->val[arg_idx] - 1];
	else if (arg_val->code_args[arg_idx] == DIR_CODE)
		val = arg_val->val[arg_idx];
	else if (arg_val->code_args[arg_idx] == IND_CODE)
	{
		if (is_idx_mod)
			ind_pos = (unsigned int *)do_steps(corewar->carriages->op_pos,
				arg_val->val[arg_idx] % IDX_MOD, corewar->arena);
		else
			ind_pos = (unsigned int *)do_steps(corewar->carriages->op_pos,
					arg_val->val[arg_idx], corewar->arena);
		val = reverse_vm_int_bytes(ind_pos);
	}
	return (val);
}
