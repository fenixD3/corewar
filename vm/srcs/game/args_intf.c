#include "vm.h"
#include "options.h"

unsigned char	*get_arguments_frm_code(unsigned char *arg_type_code,
								t_arg_type *args, t_op oper)
{
	int 			idx;

	idx = -1;
	while (++idx != oper.num_args)
		args[idx] = *arg_type_code >> (8 - (idx + 1) * 2) & 0x3u;
	if (!oper.num_args)
		args[idx] = DIR_CODE;
	return (oper.num_args ? ++arg_type_code : arg_type_code);
}

_Bool			is_args_valid(t_arg_type *args, unsigned char *arg_start,
								t_op oper, int *args_val)
{
	_Bool	good;
	int 	idx;

	good = 1;
	idx = -1;
	while(++idx != oper.num_args)
	{
		args_val[idx] = *arg_start;
		if (args[idx] == REG_CODE)
		{
			++arg_start;
			good = (good && oper.args_type[idx] & T_REG) ? 1 : 0;
		}
		else if (args[idx] == DIR_CODE)
		{
			arg_start += oper.size_t_dir;
			good = (good && oper.args_type[idx] & T_DIR) ? 1 : 0;
		}
		else if (args[idx] == IND_CODE)
		{
			arg_start += 2;
			good = (good && oper.args_type[idx] & T_IND) ? 1 : 0;
		}
	}
	return (good);
}

unsigned char	*skip_op(unsigned char *start_op, t_arg_type  *args, t_op oper)
{
	int		idx;

	idx = -1;
	while (++idx != oper.num_args)
	{
		if (args[idx] == REG_CODE)
			++start_op;
		else if (args[idx] == DIR_CODE)
			start_op += oper.size_t_dir;
		else if (args[idx] == IND_CODE)
			start_op += 2;
	}
	return (start_op);
}
