#include "vm.h"
#include "options.h"

unsigned char *get_arguments_frm_code(unsigned char *arg_type_code,
							t_arg_type *args, t_op oper, unsigned char *arena)
{
	int 			idx;

	arg_type_code = do_steps(arg_type_code, 1, arena);
	idx = -1;
	while (++idx != oper.num_args)
		args[idx] = *arg_type_code >> (8 - (idx + 1) * 2) & 0x3u;
	if (!oper.num_args)
		args[idx] = DIR_CODE;
	return (oper.num_args ? do_steps(arg_type_code, 1, arena) : arg_type_code);
}

_Bool	is_args_valid(t_parse_args *args_val, unsigned char *arg_start, t_op oper,
					unsigned char *arena)
{
	_Bool	good;
	int 	idx;

	good = 1;
	idx = -1;
	while (++idx != oper.num_args)
	{
		get_arguments_value(args_val, idx, arg_start, oper);
		if (args_val->code_args[idx] == REG_CODE)
		{
			arg_start = do_steps(arg_start, 1, arena);
			good = (good && oper.args_type[idx] & T_REG) ? 1 : 0;
		}
		else if (args_val->code_args[idx] == DIR_CODE)
		{
			arg_start = do_steps(arg_start, (char)oper.size_t_dir, arena);
			good = (good && oper.args_type[idx] & T_DIR) ? 1 : 0;
		}
		else if (args_val->code_args[idx] == IND_CODE)
		{
			arg_start = do_steps(arg_start, 2, arena);
			good = (good && oper.args_type[idx] & T_IND) ? 1 : 0;
		}
	}
	return (good);
}

void	get_arguments_value(t_parse_args *args_val, const int idx,
							unsigned char *arg_start, t_op oper)
{
	char	*chr_val;
	short	*srt_val;
	int		*int_val;

	chr_val = (char *)arg_start;
	srt_val = (short *)arg_start;
	int_val = (int *)arg_start;
	if (args_val->code_args[idx] == REG_CODE)
		args_val->val[idx] = *chr_val;
	else if (args_val->code_args[idx] == DIR_CODE)
	{
		if (oper.size_t_dir == 2)
			args_val->val[idx] = *srt_val;
		else if (oper.size_t_dir == 4)
			args_val->val[idx] = *int_val;
	}
	else if (args_val->code_args[idx] == IND_CODE)
		args_val->val[idx] = *srt_val;
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
