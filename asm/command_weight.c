
#include "asm_dasha.h"

u_int32_t		count_dir_weight(int command_code)
{
	if ((command_code >=1 && command_code < 9) || (command_code == 13)
											|| (command_code == 16))
		return (4);
	else
		return (2);
}

u_int32_t			weight_arg(t_token *token)
{
	t_arg	*arg;

	arg = (t_arg*)token->content;
	if (arg->type & T_REG)
		return (1);
	if (arg->type & T_DIR)
		return (count_dir_weight(*(u_int8_t *)token->content));
	if (arg->type & T_IND)
		return (2);
}

u_int32_t		weight_command(t_token *nxt_tok)
{
	u_int32_t		weight;

	weight = 0;
	weight += weight_arg(nxt_tok);
	if (nxt_tok->next->type == SEPARATOR)
	{
		nxt_tok = nxt_tok->next->next;
		weight += weight_arg(nxt_tok);
		if (nxt_tok->next->type == SEPARATOR)
		{
			nxt_tok = nxt_tok->next->next;
			weight += weight_arg(nxt_tok);
		}
	}
	return (weight);
}

u_int32_t	calc_command_weight(t_token *token)
{
	u_int32_t		weight;
	t_token			*nxt_tok;

	weight = 0;
	if (!(token->type == COMMAND))
		return (0);
	else
	{
		if (token->next != NULL)
			nxt_tok = token->next;
		else
			return (0);
		if (nxt_tok->type == ARGUMENT)
		{
			weight = weight_command(nxt_tok);
			weight++;
			if (g_op[(*(int *)token->next->content) - 1].argument_type_code)
				weight++;
		}
		else
			return (0);
	}
	return (weight);
}
