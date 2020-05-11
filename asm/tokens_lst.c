/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:04:17 by mdeanne           #+#    #+#             */
/*   Updated: 2020/04/02 10:33:46 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "libword.h"

t_arg		*add_arg(char *str, t_arg_type type)
{
	t_arg *new;

	new = (t_arg*)ml_malloc(sizeof(t_arg), ML_ARGUMENT);
	new->type = type;
	new->content = NULL;
	if (type & T_LAB)
		return (new);
	if (type & T_REG || type & T_DIR)
		new->num = ft_atoi(str + 1);
	else if (type & T_IND)
		new->num = ft_atoi(str);
	return (new);
}

void		add_label(char *str, t_token *token,
											t_label **tail, t_arg_type arg_type)
{
	t_label	*new;

	new = (t_label*)ml_malloc(sizeof(t_label), ML_LABEL);
	new->token = token;
	new->name = ml_strndup(str, ft_skipword(str, DELIMITERS) - str, ML_L_NAME);
	new->next = NULL;
	if (arg_type)
	{
		token->content = (void*)add_arg(NULL, arg_type);
		((t_arg*)token->content)->content = (void*)new;
	}
	else
		token->content = (void*)new;
	if (!*tail)
		new->prev = NULL;
	else
	{
		new->prev = *tail;
		(*tail)->next = new;
	}
	*tail = new;
}

char		*add_string(char *str, t_token *token)
{
	char *tmp;

	token->type = STRING;
	tmp = str + ((*str == '"') ? 1 : 0);
	if (*tmp == '"')
	{
		token->content = (char*)ml_memalloc(sizeof(char) * 3, ML_S_CONTENT);
		ft_memset((char*)token->content, '"', 2);
		return (tmp + 1);
	}
	while (*tmp && *tmp != '"')
		tmp++;
	if (*tmp == '"')
		tmp++;
	token->content = (void*)ml_strndup(str, tmp - str, ML_S_CONTENT);
	return (tmp);
}

u_int8_t	check_prev_str(t_token *token, u_int8_t flag)
{
	char *str;
	char *str_end;

	if (!token || token->type != NEW_LINE || !token->prev ||
		token->prev->type != STRING)
		return (flag);
	str = (char*)token->prev->content;
	if (token->prev->prev && token->prev->prev->type == NEW_LINE &&
		token->prev->prev->prev && token->prev->prev->prev->type == STRING)
		;
	else if (*str == '"')
		str++;
	if ((str_end = ft_strchr(str, '"')) && !*(str_end + 1))
		return (flag);
	return (NOTENDSTR);
}

t_token		*add_token(t_pc *pc, t_token **token_tail,
											t_label **label_tail, u_int8_t flag)
{
	t_token *new;

	new = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	token_fill(pc->line, new, label_tail, check_prev_str(*token_tail, flag));
	new->row = pc->row;
	new->column = pc->column;
	new->next = NULL;
	if (!*token_tail)
		new->prev = NULL;
	else
	{
		new->prev = *token_tail;
		(*token_tail)->next = new;
	}
	*token_tail = new;
	return (new);
}
