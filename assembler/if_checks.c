/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:28:05 by mdeanne           #+#    #+#             */
/*   Updated: 2020/05/17 14:28:11 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "asm.h"

void	if_label(t_token *token, t_token_sec *check_list)
{
	if (token->type == LABEL)
	{
		if (!(check_list)->new_line)
			token_exception(NL_MISSING, token, 0);
		else if (!(check_list)->str_comment)
			go_exit(CMNT_MISSING);
		else if (!check_list->str_name)
			go_exit(NAME_MISSING);
		if (!(check_list)->new_line)
			token_exception(NL_MISSING, token, 0);
		else
		{
			(check_list)->arg = false;
			(check_list)->command = false;
		}
	}
}

void	if_arg(t_token *token, t_token_sec *check_list)
{
	if (token->type == ARGUMENT || token->type == ARGUMENT_LABEL)
	{
		if (!(check_list)->command)
			token_exception(CMD_MISS, token, 0);
		if (!(check_list)->arg && (check_list)->separator)
			token_exception(EXTR_SPRTR, token, 0);
		if ((check_list)->arg && !(check_list)->separator)
			token_exception(SPRTR_MISS, token, 0);
		if (((t_arg*)token->content)->type & T_REG &&
				(((t_arg*)token->content)->num < 0 ||
				((t_arg*)token->content)->num > 99))
			token_exception(TREG_INVALID_NUM, token, 0);
		if (((t_arg*)token->content)->type & T_REG &&
					(((t_arg*)token->content)->num == 0 ||
					((t_arg*)token->content)->num > REG_NUMBER))
			token_exception(WRNNG_TREG_INVALID_NUM, token, 1);
		(check_list)->new_line = false;
		(check_list)->separator = false;
		(check_list)->arg = true;
	}
}

void	if_comment_prog(t_token *token, t_token_sec *check_list)
{
	if (token->type == COMMENT_PROG)
	{
		if (((check_list)->name && !(check_list)->str_name) ||
			((check_list)->name && (check_list)->str_name &&
													!(check_list)->new_line))
			token_exception(NAME_CMT, token, 0);
		if ((check_list)->comment_prog)
			token_exception(DOUBLE_COMMENT, token, 0);
		else
			(check_list)->comment_prog = true;
	}
}

void	if_name(t_token *token, t_token_sec *check_list)
{
	if (token->type == NAME)
	{
		if ((check_list->comment_prog && !check_list->str_comment) ||
			(check_list->comment_prog && check_list->str_comment &&
			!check_list->new_line) || check_list->name)
			token_exception(DOUBLE_NAME, token, 0);
		else
			check_list->name = true;
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
			token_exception(WRONG_SEPARATOR, token, 0);
		(check_list)->new_line = true;
		(check_list)->separator = false;
		(check_list)->arg = false;
	}
}
