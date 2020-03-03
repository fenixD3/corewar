

#include <stdbool.h>
#include "asm.h"
#include "asm_dasha.h"


int			weight_arg(t_token *token)
{
	t_arg	*arg;

	arg = (t_arg*)token->content;
	if (arg->type & T_REG)
		return (1);
	if (arg->type & T_DIR)
		return ();
	if (arg->type & T_IND)
		return ();
}

int			command_weight(t_token *token)
{
	int		weight;
	t_arg	*fr_arg;
	t_arg	*sc_arg;
	t_arg	*trd_arg;
	t_token	*nxt_tok;

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
		}
		else
			return (0);
	}
	return (weight);
}
