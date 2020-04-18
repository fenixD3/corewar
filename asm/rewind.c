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

#include "ft_ptintf.h"
#include "asm.h"
#include "libword.h"
#include "libft.h"
#include "asm_dasha.h"

void		rewind_n(t_pc *pc, u_int16_t n)
{
	pc->line += n;
	pc->column += n;
}

u_int8_t 	string_rewind(t_pc *pc)
{
	char *str_end;

	if (*pc->line == '"')
		rewind_n(pc, 1);
	if (!(str_end = ft_strchr(pc->line, '"')))
		return (TKNZE_BREAK);
	rewind_n(pc, str_end - pc->line + 1);
	rewind_n(pc, ft_skipdelims(pc->line, SPACES) - pc->line);
	return (TKNZE_CONT);
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
	if (*pc->line == '-')
		rewind_n(pc, 1);
	tmp = ft_skipword(pc->line, DELIMITERS);
	rewind_n(pc, tmp - pc->line);
}

void		command_rewind(t_pc *pc, t_token *token)
{
	if (!token->content || !*(char*)token->content ||
							ft_isspecial(*(char*)token->content, DELIMITERS))
		token_exception(ASM_INVALID_CMD, token, 0);
	rewind_n(pc, ft_skipword(pc->line, DELIMITERS) - pc->line);
}

u_int8_t token_rewind(t_pc *pc, t_token *token)
{
	if (token->type == COMMENT)
		return (TKNZE_BREAK);
	else if (token->type == ARGUMENT || token->type == ARGUMENT_LABEL)
		argument_rewind(pc , token);
	else if (token->type == COMMAND)
		command_rewind(pc, token);
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
	rewind_n(pc, ft_skipdelims(pc->line, SPACES) - pc->line);
	return (TKNZE_CONT);
}