
#include "asm_dasha.h"

int	token_exit(char *error, t_token *token)
{
	if (error)
		printf("[%03d:%03d] %s\n", token->row, token->column, error);
	exit(1);
	return (0);
}
