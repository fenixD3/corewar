

#include <stdbool.h>
#include "asm.h"
#include "asm_dasha.h"

int		count_dir_weight(void *command_name)
{
	if ((!ft_strcmp("live", command_name)) || (!ft_strcmp("ld", command_name))
		|| (!ft_strcmp("st", command_name)) || (!ft_strcmp("add", command_name))
		|| (!ft_strcmp("sub", command_name)) || (!ft_strcmp("and", command_name))
		|| (!ft_strcmp("or", command_name)) || (!ft_strcmp("xor", command_name))
		|| (!ft_strcmp("lld", command_name)) || (!ft_strcmp("aff", command_name)))
		return (4);
	else
		return (2);
}

int			weight_arg(t_token *token)
{
	t_arg	*arg;

	arg = (t_arg*)token->content;
	if (arg->type & T_REG)
		return (1);
	if (arg->type & T_DIR)
		return (count_dir_weight((char *)token->content));
	if (arg->type & T_IND)
		return (2);
}

int			command_weight(t_token *token)
{
	int		weight;
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
