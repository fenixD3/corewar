
#include "asm_dasha.h"


void	check_args(t_token *token, int *i, int com_code)
{
	t_token	*cp_tok;
	t_arg	*arg;

	cp_tok = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->next->type == ARGUMENT || token->next->type == ARGUMENT_LABEL)
		{
			arg = (t_arg*)token->next->content;
			if (!(arg->type & ((g_op[com_code]).args_type[*i])))
				token_exit(ASM_ERR_ARGS, token);
			(*i)++;
		}
		token = token->next;
	}
	token = cp_tok;
}

void	command_check(t_token *token)
{
	int		i;
	u_int8_t		com_code;

	com_code = 0;
	i = 0;
	if (!(token->type == COMMAND))
		return ;
	else
	{
		com_code = *(u_int8_t *)token->content - 1;
		check_args(token, &i, com_code);
		if ((i < 2 && ((g_op[com_code]).args_type[1] != 0))
			|| (i < 3 && ((g_op[com_code]).args_type[2] != 0)))
			token_exit(ASM_ERR_ARGS, token);
	}
}
