#include "asm_dasha.h"

unsigned int		calc_progsize(t_token *token)
{
	t_token			*cp_tok;
	unsigned int	weight;

	weight = 0;
	cp_tok = token;
	while (token->next != NULL)
	{
		if (token->type == COMMAND)
			weight += calc_command_weight(token);
		token = token->next;
	}
	token = cp_tok;
	return (weight);
}

void				init_headers(header_t *header, t_token *token)//name, comment
{
	header->magic = COREWAR_EXEC_MAGIC;
//	header->comment = (char *)comment->content;
//	header->prog_name = (char *)name->content;
	header->prog_size = calc_progsize(token);
}