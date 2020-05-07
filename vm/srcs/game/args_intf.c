#include "vis.h"
#include "options.h"

unsigned char *get_arguments_frm_code(unsigned char *arg_type_code,
							t_arg_type *args, t_op oper, unsigned char *arena)
{
	int 			idx;

	arg_type_code = do_steps(arg_type_code, 1, arena);
	idx = 0;
	if (!oper.argument_type_code)
		args[idx] = DIR_CODE;
	else
		while (idx != oper.num_args)
		{
			args[idx] = *arg_type_code >> (8 - (idx + 1) * 2) & 0x3u;
			++idx;
		}
	return (oper.argument_type_code ? do_steps(arg_type_code, 1, arena) : arg_type_code);
}

_Bool		is_args_valid(t_parse_args *args_val, unsigned char *arg_start,
					   const t_op *oper, unsigned char *arena)
{
	_Bool	good;
	int 	idx;

	good = 1;
	idx = -1;
	get_arguments_values(args_val, arg_start, oper, arena);
	while (++idx != oper->num_args && good)
	{
		if (args_val->code_args[idx] == REG_CODE)
			good = (good && oper->args_type[idx] & T_REG &&
				args_val->val[idx] >= 1 && args_val->val[idx] <= 16) ? 1 : 0;
		else if (args_val->code_args[idx] == DIR_CODE)
			good = (good && oper->args_type[idx] & T_DIR) ? 1 : 0;
		else if (args_val->code_args[idx] == IND_CODE)
			good = (good && oper->args_type[idx] & T_IND) ? 1 : 0;
		else
			good = 0;
	}
	return (good);
}

void	get_arguments_values(t_parse_args *args_val, unsigned char *arg_start,
						  const t_op *oper, unsigned char *arena)
{
	unsigned char	*get_arg;
	int 			idx;

	idx = -1;
	while (++idx != oper->num_args)
	{
		get_arg = arg_start;
		if (args_val->code_args[idx] == REG_CODE)
		{
			args_val->val[idx] = *get_arg;
			arg_start = do_steps(arg_start, 1, arena);
		}
		else if (args_val->code_args[idx] == DIR_CODE)
		{
			args_val->val[idx] = reverse_vm_bytes(get_arg, (oper->size_t_dir == 2) ? 2 : 4, arena);
			arg_start = do_steps(arg_start, (char)oper->size_t_dir, arena);
		}
		else if (args_val->code_args[idx] == IND_CODE)
		{
			args_val->val[idx] = reverse_vm_bytes(get_arg, 2, arena);
			arg_start = do_steps(arg_start, 2, arena);
		}
	}
}

unsigned char	*skip_op(unsigned char *start_op, t_arg_type *args, t_op oper,
						  unsigned char *arena)
{
	int		idx;

	idx = -1;
	while (++idx != oper.num_args)
	{
		if (args[idx] == REG_CODE)
			start_op = do_steps(start_op, 1, arena);
		else if (args[idx] == DIR_CODE)
			start_op = do_steps(start_op, (char)oper.size_t_dir, arena);
		else if (args[idx] == IND_CODE)
			start_op = do_steps(start_op, 2, arena);
	}
	return (start_op);
}
