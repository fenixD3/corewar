#include <stdbool.h>
#include "asm_dasha.h"

void	if_label(t_token *token, t_token_sec *check_list)
{
	if (token->type == LABEL)
	{
		if (!(check_list)->new_line)
			token_exit(ASM_NL_MISSING, token);
		else if (!(check_list)->str_comment)
			token_exit(ASM_ERR_CMP_COMMENT,	token);
		if (!(check_list)->new_line)
			token_exit(ASM_NL_MISSING, token);
		else
		{
			(check_list)->arg = false;
			(check_list)->command = false;
			(check_list)->label = true;
		}
	}
}

void	if_arg(t_token *token, t_token_sec *check_list)
{
	if (token->type == ARGUMENT || token->type == ARGUMENT_LABEL)
	{
		if (!(check_list)->command)
			token_exit(ASM_COMMAND_MISSING, token);
		else
		{
			if (!(check_list)->arg)
			{
				if ((check_list)->separator)
					token_exit(ASM_EXTRA_SEPARATOR, token);
			}
			else
				if (!(check_list)->separator)
					token_exit(ASM_SEPARATOR_MISSING, token);
			(check_list)->new_line = false;
			(check_list)->separator = false;
			(check_list)->arg = true;
		}
	}
}

void	if_comment_prog(t_token *token, t_token_sec *check_list)
{
	if (token->type == COMMENT_PROG)
	{
		if (((check_list)->name && !(check_list)->str_name) ||
			((check_list)->name && (check_list)->str_name && !(check_list)->new_line))
			token_exit(ASM_ERR_NAME_COMMENT, token);
		if ((check_list)->comment_prog)
			token_exit(ASM_DOUBLE_COMMENT, token);
		else
			(check_list)->comment_prog = true;
	}
}

void	if_name(t_token *token, t_token_sec *check_list)
{
	if (token->type == NAME)
	{
		if (((check_list)->comment_prog && !(check_list)->str_comment) ||
			((check_list)->comment_prog && (check_list)->str_comment &&
			 !(check_list)->new_line))
			token_exit(ASM_DOUBLE_NAME, token);
		else
			(check_list)->name = true;
	}
}

void	if_nl_or_comment(t_token *token, t_token_sec *check_list)
{
	if (token->type == COMMENT)
	{
		check_list->new_line = false;
		check_list->comment = true;
	}
	else if (token->type == NEW_LINE)
	{
		if ((check_list)->separator)
			token_exit(ASM_WRONG_SEPARATOR, token);
		(check_list)->new_line = true;
		(check_list)->separator = false;
		(check_list)->arg = false;
	}
}
