/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:33 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 16:22:35 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "asm.h"

u_int8_t 	string_rewind(t_pc *pc)
{
	if (*pc->line == '"')
	{
		pc->line++;
		pc->column++;
	}
	while (*pc->line && *pc->line != '"')
	{
		pc->line++;
		pc->column++;
	}
	return ((*pc->line == '"') ? ENDSTR : NOTENDSTR);
}

void		rewind_n(t_pc *pc, u_int16_t n)
{
	pc->line += n;
	pc->column += n;
}

u_int8_t	token_rewind(t_pc *pc, t_token *token)
{
	if (token->type == STRING)
		return string_rewind(pc);
	else if (token->type == SEPARATOR)
		rewind_n(pc, 1);
	else if (token->type == NAME)
		rewind_n(pc, ft_strlen(NAME_CMD_STRING));
	else if (token->type == COMMENT_PROG)
		rewind_n(pc, ft_strlen(COMMENT_CMD_STRING));


}

void	tokenize(int fd, t_token **token, t_label **label)
{
	t_pc		pc;
/*	t_token	*token;
	t_label	*label;*/
	/*int		ret;*/
	u_int8_t	flag;
	char 		*str;

	pc.row = 0;
	token = NULL;
	while ((/*ret = */get_next_line(fd, &str)) > 0)
	{
		pc.line = str;
		pc.column = 0;
		while (*pc.line)
		{
			add_token(&pc, token, label, 0);
			/// здесь добавляем перемотку до конца добавленного токена
		}
		free(str);
		pc.row++;
	}
	if (!*token)
		go_exit("ERROR: File is empty");
	while ((*token)->prev)
		*token = (*token)->prev;
	while ((*label)->prev)
		*label = (*label)->prev;
}
