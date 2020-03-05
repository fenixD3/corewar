
#include <stdbool.h>
#include "asm_dasha.h"

void 	init_check_list(t_token_sec **check_list)
{
	*check_list = (t_token_sec*)ml_malloc(sizeof(t_token_sec), ML_CHECK_LST);
	(*check_list)->arg = false;
	(*check_list)->command = false;
	(*check_list)->comment = false;
	(*check_list)->comment_prog = false;
	(*check_list)->separator = false;
	(*check_list)->str_comment = false;
	(*check_list)->str_name = false;
	(*check_list)->name = false;
	(*check_list)->new_line = true;
	(*check_list)->chmp_name = NULL;
	(*check_list)->chmp_comment = NULL;
	(*check_list)->label = false;
}

_Bool	is_length_within_limit(char *str, t_token_sec *check_list)
{
	int		limit;

	limit = (check_list->name && !check_list->comment_prog) ?
			PROG_NAME_LENGTH : COMMENT_LENGTH;
	if (ft_strlen(str) > limit)
		return (false);
	return (true);
}

void	if_str_check(t_token *token, t_token_sec *check_list)
{
	if (token->type == STRING)
	{
		if (!is_length_within_limit((char *)token->content, check_list))
			token_exit(((check_list->name && !check_list->comment_prog) ?
						ASM_TOLONG_NAME : ASM_TOLONG_COMMENT), token);
		if (check_list->name && !check_list->comment_prog)
		{
			check_list->str_name = true;
			check_list->new_line = false;
			check_list->chmp_name = (char *)token->content;
		}
		else if (check_list->comment_prog && !check_list->label)
		{
			check_list->str_comment = true;
			check_list->new_line = false;
			check_list->chmp_comment = (char *)token->content;
		}
		else
			token_exit(ASM_FILE_ERR, token);
	}
}

void	if_command(t_token *token, t_token_sec *check_list)
{
	char	*com_name;
	int 	i;

	i = 0;
	if (token->type == COMMAND)
	{
		if (!check_list->str_comment || !check_list->name)
			token_exit(ASM_C_N_MISSING, token);
		if (!check_list->new_line)
			token_exit(ASM_NL_MISSING, token);
		else
		{
			check_list->new_line = false;//?
			check_list->command = true;
			check_list->arg = false;
			com_name = (char *)(token->content);
			while (!ft_strequ(com_name, g_op[i].name))
				i++;
			token->content = (u_int8_t*)g_op[i].code;
			command_check(token);
		}
	}
}

_Bool			token_sequence(t_token *token)
{
	t_token_sec	*check_list;
	t_token		*token_arr;
	header_t	header;

	token_arr = token;
	init_check_list(&check_list);
	while (token != NULL)
	{
		if (token->type == COMMENT)
			;
		else if (token->type == SEPARATOR)
		{
			if (check_list->separator)
				token_exit(ASM_WRONG_SEPARATOR, token);
			check_list->separator = true;
		}
		if_nl(token, check_list);
		if_name(token, check_list);
		if_comment_prog(token, check_list);
		if_str_check(token, check_list);
		if_command(token, check_list);
		if_label(token, check_list);
		if_arg(token, check_list);
		token = token->next;
	}
	token = token_arr;
	init_headers(&header, token);
}
