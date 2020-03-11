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
			weight += command_length(token);
		token = token->next;
	}
	token = cp_tok;
	return (weight);
}

void				init_headers(header_t *header, t_token *token, t_token_sec *info)
{
	int	com_len;

	com_len = ft_strlen(info->chmp_comment);
	ft_bzero(header->comment, COMMENT_LENGTH);
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	(header)->magic = COREWAR_EXEC_MAGIC;
	ft_strncpy((header)->comment, info->chmp_comment, com_len);
	ft_strncpy((header)->prog_name, info->chmp_name, ft_strlen(info->chmp_name));
	(header)->prog_size = calc_progsize(token);
}