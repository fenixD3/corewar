/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 21:07:14 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 21:07:16 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include "libword.h"

_Bool	is_numarg(char *str)
{
	if (*str == '-')
		str++;
	return (ft_isdigitalword(str, DELIMITERS));
}

_Bool	arg_label_recognition(char *str, t_token *token, t_label **tail)
{
	if (*str == REGISTER_CHAR && is_numarg(str + 1))
		token->content = (void*)add_arg(str, T_REG);
	else if (*str == DIRECT_CHAR && is_numarg(str + 1))
		token->content = (void*)add_arg(str, T_DIR);
	else if (is_numarg(str))
		token->content = (void*)add_arg(str, T_IND);
	else if ((*str == DIRECT_CHAR && *(str + 1) == LABEL_CHAR) ||
															*str == LABEL_CHAR)
	{
		if (*str == LABEL_CHAR)
			add_label(str + 1, token, tail, T_IND | T_LAB);
		else
			add_label(str + 2, token, tail, T_DIR | T_LAB);
		token->type = ARGUMENT_LABEL;
		return (1);
	}
	else
		return (0);
	token->type = ARGUMENT;
	return (1);
}

_Bool	label_recognition(char *str, t_token *token, t_label **tail)
{
	char *tmp;

	tmp = str;
	while (*tmp && !ft_isspecial(*tmp, DELIMITERS))
	{
		if (!ft_isspecial(*tmp, LABEL_CHARS))
			return (0);
		tmp++;
	}
	if (*tmp != LABEL_CHAR)
		return (0);
	add_label(str, token, tail, 0);
	return (1);
}

void	token_fill(char *str, t_token *token, t_label **tail, u_int8_t flag)
{
	if (flag == ENDFILE)
		token->type = END;
	else if (*str == '"' || flag == NOTENDSTR)
		add_string(str, token);
	else if (!*str || flag == ENDLINE)
		token->type = NEW_LINE;
	else if (*str == SEPARATOR_CHAR)
		token->type = SEPARATOR;
	else if (*str == COMMENT_CHAR || *str == ALT_COMMENT_CHAR)
		token->type = COMMENT;
	else if (*str == '.' && ft_wordequ(NAME_CMD_STRING, str, DELIMITERS))
		token->type = NAME;
	else if (*str == '.' && ft_wordequ(COMMENT_CMD_STRING, str, DELIMITERS))
		token->type = COMMENT_PROG;
	else if (arg_label_recognition(str, token, tail))
		;
	else if (label_recognition(str, token, tail))
		token->type = LABEL;
	else
	{
		token->type = COMMAND;
		token->content = (void*)ml_strndup(str,
				ft_skipword(str, DELIMITERS) - str, ML_CMD_NAME);
	}
}
