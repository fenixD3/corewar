
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "asm.h"
#include "asm_dasha.h"

_Bool	check_live(t_token *token)
{
	t_arg	*arg;
	t_token	*tok_cp;

	tok_cp = token;
	while (token->type != NEW_LINE)
	{
		//сохранить аргументы
		token = token->next;
	}
	arg = (t_arg*)token->content;

}

void	command_check(t_token *token)
{
	if (!(token->type == COMMAND))
		return ;
	else
	{
		if (!ft_strcmp("live", token->content))
			check_live(token);
	}
}
