/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_str_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 19:31:03 by mdeanne           #+#    #+#             */
/*   Updated: 2020/03/16 19:31:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar/libft/libft.h>
#include "errors.h"
#include "asm.h"
#include "asm_dasha.h"

t_token		*find_token(t_token *head, t_token_type type)
{
	while (head && head->type != type)
		head = head->next;
	if (!head)
	{
		printf("ERROR: can't find token %s\n", g_type[type]);
		exit(1);
	}
	return (head);
}

u_int16_t	tkn_str_len(t_token *token, u_int16_t *tkn_num)
{
	int	len;

	if (token->type != STRING)
		token_exit(ASM_INVALID_STR_PLACE, token);
	len = -2;
	*tkn_num = 0;
	while (token && (token->type == STRING || token->type == NEW_LINE))
	{
		if (token->type == STRING)
		{
			len += ft_strlen((char*)token->content);
			(*tkn_num)++;
		}
		else
			len++;
		token = token->next;
	}
	//len -= (*tkn_num == 1) ? 1 : 2;
	len--;
	if (len < 0)
		go_exit(ASM_INVALID_STR);
	return ((u_int16_t)len);
}

t_token		*jump_next_string(t_token *token)
{
	if (!token->next || token->next->type != NEW_LINE || !token->next->next ||
		token->next->next->type != STRING)
		go_exit(ASM_INVALID_STR);
	return (token->next->next);
}

char *tkn_str_cat(char *dst, t_token *token, u_int32_t max_len)
{
	u_int16_t	len;
	u_int16_t	tkn_num;
	//char		*str;

	if (token->type != STRING)
		token_exit(ASM_INVALID_STR_PLACE, token);
	if ((len = tkn_str_len(token, &tkn_num)) > max_len)
		go_exit((max_len == PROG_NAME_LENGTH) ? ASM_LONG_NAME : ASM_LONG_CMNT);
	if (tkn_num == 1)
		return (ft_strncat(dst, (char*)token->content + 1, len - 1));
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
