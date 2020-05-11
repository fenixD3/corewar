#include "asm.h"

unsigned int	calc_progsize(t_token *token)
{
	t_token			*cp_tok;
	unsigned int	weight;

	weight = 0;
	cp_tok = token;
	while (token->next != NULL)
	{
		if (token->type == COMMAND)
			weight += command_length(token);
		token = token->next;
	}
	token = cp_tok;
	return (weight);
}

void			init_headers(header_t *header, t_token *token)
{
	ft_bzero(header->comment, COMMENT_LENGTH);
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	(header)->magic = COREWAR_EXEC_MAGIC;
	tkn_str_cat(header->prog_name, find_token(token, NAME)->next,
			PROG_NAME_LENGTH);
	tkn_str_cat(header->comment, find_token(token, COMMENT_PROG)->next,
				COMMENT_LENGTH);
	(header)->prog_size = calc_progsize(token);
}
