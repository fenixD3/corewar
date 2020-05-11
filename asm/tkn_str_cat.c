/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_str_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 19:31:03 by mdeanne           #+#    #+#             */
/*   Updated: 2020/05/12 00:27:15 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"
#include "asm.h"

t_token		*find_token(t_token *head, t_token_type type)
{
	while (head && head->type != type)
		head = head->next;
	if (!head)
	{
		ft_printf("ERROR: can't find token %s\n", g_type[type]);
		exit(1);
	}
	return (head);
}

u_int8_t	count_double_quotes(char *str)
{
	u_int8_t dq;

	dq = 0;
	while ((str = ft_strchr(str, '"')))
	{
		str++;
		dq++;
	}
	return (dq);
}

u_int16_t	tkn_str_len(t_token *tkn, u_int16_t *tkn_num)
{
	int			len;
	u_int8_t	dq;

	if (tkn->type != STRING)
		token_exception(INVALID_STR_PLACE, tkn, 0);
	len = -2;
	dq = 0;
	*tkn_num = 0;
	while (tkn && (tkn->type == STRING || tkn->type == NEW_LINE) && dq < 2)
	{
		if (tkn->type == STRING)
		{
			len += ft_strlen((char*)tkn->content);
			dq += count_double_quotes((char*)tkn->content);
			(*tkn_num)++;
		}
		tkn = tkn->next;
	}
	if (!tkn)
		go_exit(NOCODE);
	if (len < 0)
		go_exit(INVALID_STR);
	return (len);
}

t_token		*jump_next_string(t_token *token)
{
	if (!token->next || token->next->type != NEW_LINE || !token->next->next ||
		token->next->next->type != STRING)
		go_exit(INVALID_STR);
	return (token->next->next);
}

char		*tkn_str_cat(char *dst, t_token *token, u_int32_t max_len)
{
	u_int16_t	len;
	u_int16_t	tkn_num;

	if (token->type != STRING)
		token_exception(INVALID_STR_PLACE, token, 0);
	if ((len = tkn_str_len(token, &tkn_num)) > max_len)
		go_exit((max_len == PROG_NAME_LENGTH) ? LONG_NAME : LONG_CMNT);
	if (tkn_num == 1)
		return (ft_strncat(dst, (char*)token->content + 1, len));
	ft_strcat(ft_strcat(dst, (char*)token->content + 1), "\n");
	token = jump_next_string(token);
	tkn_num -= 2;
	while (tkn_num--)
	{
		ft_strcat(ft_strcat(dst, (char*)token->content), "\n");
		token = jump_next_string(token);
	}
	return (ft_strncat(dst, (char*)token->content,
										ft_strlen((char*)token->content) - 1));
}
