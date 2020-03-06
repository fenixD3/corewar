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

void				init_headers(header_t **header, t_token *token, t_token_sec *info)//name, comment
{
    (*header) = (header_t*)ml_malloc(sizeof(header_t), ML_HEADER);
	(*header)->magic = COREWAR_EXEC_MAGIC;
	ft_strncpy((*header)->comment, info->chmp_comment, ft_strlen(info->chmp_comment));
	ft_strncpy((*header)->prog_name, info->chmp_name, ft_strlen(info->chmp_name));
	(*header)->prog_size = calc_progsize(token);
}