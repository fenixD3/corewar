
#include "asm_dasha.h"

u_int8_t    calc_arg_type_code(t_token *token)
{
	u_int8_t	num_args;
	int         i;
	unsigned int    res;
	t_op		*op;

//	00 00 00 00
//	00 00 00 01
//	01 00 00 00
//	00 00 01 10
//	01 10 00 00
//  00 01 10 10
//  01 10 10 00
	i = 0;
	res = 0;
	op = &g_op[*(u_int8_t*)token->content - 1];
	num_args = op->num_args;
	while (num_args--)
	{
		while ((token->type != ARGUMENT && token->type != ARGUMENT_LABEL))
			token = token->next;
		if (((t_arg*)token->content)->type & T_REG)
		{
			res >>= i + 6;
			res |= 1;
			res <<= i + 6;
		}
		else if (((t_arg*)token->content)->type & T_IND)
		{
			res >>= i + 6;
			res |= 3;
			res <<= i + 6;
		}
		else if (((t_arg*)token->content)->type & T_DIR)
		{
			res >>= i + 6;
			res |= 2;
			res <<= i + 6;
		}
		token = token->next;
		i -= 2;
	}
	return (res);
}

void    print_commands(int fd, t_token *token, t_label *label)
{
	unsigned char res;
	int             com_code;
	while (token->next != NULL)
	{
		if (token->type == COMMAND)
		{
			com_code = *(u_int8_t *)token->content - 1;
			write(fd, &g_op[com_code].code, 1);
			if (g_op[com_code].argument_type_code)
			{
				res = calc_arg_type_code(token);
				write(fd, &res, 1);
			}
		}
		token = token->next;
	}

}