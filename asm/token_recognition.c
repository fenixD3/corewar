/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 21:07:14 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 21:07:16 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

_Bool	argument_recognition(char *str, t_token *token)
{

	return (0);
}

/*
void	token_recognition(char *str, t_token *token, _Bool end)
{
	if (!*str && end)
		token->type = END;
	else if (!*str)
		token->type = NEW_LINE;
	else if (*str == SEPARATOR_CHAR)
		token->type = SEPARATOR;
	else if (*str == COMMENT_CHAR || *str == ALT_COMMENT_CHAR)
		token->type = COMMENT;
	else if (*str == '.' && ft_wordequ(NAME_CMD_STRING, str, DELIMITERS))
		token->type = NAME;
	else if (*str == '.' && ft_wordequ(COMMENT_CMD_STRING, str, DELIMITERS))
		token->type = COMMENT_PROG;
	else if (argument_recognition(str, token))
		token->type = ARGUMENT;
	else if (*/
/*labels*//*
);
	else if (*/
/*commands*//*
);
	else if (*str == "\"" || (token->prev && token->prev->type == STRING))
		token->type = STRING;

}*/
