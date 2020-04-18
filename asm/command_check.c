
#include "asm_dasha.h"
#include "asm.h"


void	check_args(t_token *token, int *i, int com_code)
{
	t_token	*token_arg;
	t_arg	*arg;

	token_arg = token->next;
	while (token_arg && token_arg->type != NEW_LINE)
	{
		if (token_arg->type == ARGUMENT || token_arg->type == ARGUMENT_LABEL)
		{
			arg = (t_arg*)token_arg->content;
			if (!(arg->type & ((g_op[com_code]).args_type[*i])))
				token_exception(ASM_ERR_ARGS, token_arg, 0);
			(*i)++;
		}
		else if (token_arg->type == COMMENT && token_arg->next &&
				token_arg->next->type == NEW_LINE)
			return ;
		else if (token_arg->type != SEPARATOR)
			token_exception(ASM_ERR_ARGS, token_arg, 0);
		token_arg = token_arg->next;
	}
}

void	command_check(t_token *token)
{
	int		i;
	u_int8_t		com_code;


	i = 0;
	if (!(token->type == COMMAND))
		return ;
	com_code = *(u_int8_t *)token->content - 1;
	check_args(token, &i, com_code);
	if ((i < 2 && ((g_op[com_code]).args_type[1] != 0))
		|| (i < 3 && ((g_op[com_code]).args_type[2] != 0)))
		token_exception(ASM_ERR_ARGS, token, 0);
}
