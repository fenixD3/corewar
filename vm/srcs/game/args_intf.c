#include "vis.h"
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

_Bool		is_args_valid(t_parse_args *args_val, unsigned char *arg_start,
					   const t_op *oper, unsigned char *arena)
{
	_Bool	good;
	int 	idx;

	good = 1;
	idx = -1;
	get_arguments_values(args_val, arg_start, oper, arena);
/*printf("Fst arg type = %d", args_val->code_args[0]);
printf(", its val = %d\n", args_val->val[0]);*/
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
	union u_get_arg	get_arg;
	int 			idx;

	idx = -1;
	while (++idx != oper->num_args)
	{
		get_arg.chr_ptr = arg_start;
		if (args_val->code_args[idx] == REG_CODE)
		{
			args_val->val[idx] = *get_arg.chr_ptr;
			arg_start = do_steps(arg_start, 1, arena);
		}
		else if (args_val->code_args[idx] == DIR_CODE)
		{
			args_val->val[idx] = (oper->size_t_dir == 2) ?
				reverse_vm_short_bytes(get_arg.srt_ptr) :
				reverse_vm_int_bytes(get_arg.int_ptr);
			arg_start = do_steps(arg_start, (char)oper->size_t_dir, arena);
		}
		else if (args_val->code_args[idx] == IND_CODE)
		{
			args_val->val[idx] = reverse_vm_short_bytes(get_arg.srt_ptr);
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
