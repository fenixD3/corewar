/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewind.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:11:09 by mdeanne           #+#    #+#             */
/*   Updated: 2020/03/04 20:11:11 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libword.h"
#include "libft.h"

void		rewind_n(t_pc *pc, u_int16_t n)
{
	pc->line += n;
	pc->column += n;
}

u_int8_t 	string_rewind(t_pc *pc)
{
	if (*pc->line == '"')
		rewind_n(pc, 1);
	while (*pc->line && *pc->line != '"')
	{
		pc->line++;
		pc->column++;
	}
	if (*pc->line == '"')
		rewind_n(pc, 1);
	if (*(pc->line - 1) == '"')
		return (ENDSTR);
	else
		return (NOTENDSTR);
}

void		argument_rewind(t_pc *pc, t_token *token)
{
	t_arg *arg;
	char *tmp;

	arg = (t_arg*)token->content;
	if (arg->type & T_REG || arg->type & T_DIR)
		rewind_n(pc, 1);
	if (token->type == ARGUMENT_LABEL)
		rewind_n(pc, 1);
	tmp = ft_skipword(pc->line, DELIMITERS);
	rewind_n(pc, tmp - pc->line);
}

u_int8_t	token_rewind(t_pc *pc, t_token *token)
{
	char *tmp;

	if (token->type == NEW_LINE || token->type == COMMENT)
		return (ENDLINE);
	else if (token->type == ARGUMENT || token->type == ARGUMENT_LABEL)
		argument_rewind(pc , token);
	else if (token->type == COMMAND)
		rewind_n(pc, ft_skipword(pc->line, DELIMITERS) - pc->line);
	else if (token->type == SEPARATOR)
		rewind_n(pc, 1);
	else if (token->type == LABEL)
		rewind_n(pc, ft_skipword(pc->line, DELIMITERS) - pc->line + 1);
	else if (token->type == STRING)
		return (string_rewind(pc));
	else if (token->type == NAME)
		rewind_n(pc, ft_strlen(NAME_CMD_STRING));
	else if (token->type == COMMENT_PROG)
		rewind_n(pc, ft_strlen(COMMENT_CMD_STRING));
	else if (token->type == END)
		return (ENDFILE);
	rewind_n(pc, ft_skipdelims(pc->line, SPACES) - pc->line);
	return (NOTSTR);
}