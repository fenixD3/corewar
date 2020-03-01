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
#include "libword.h"

/*
t_arg	*add_arg(char *str, t_arg_type type)
{
	t_arg *new;

	new = (t_arg*)ml_malloc(sizeof(t_arg), ML_ARGUMENT);
	new->type = type;
	new->content = NULL;
	if (type & T_REG)
		new->num = ft_atoi(str + 1);
	else if (type & T_LAB)
	{
		new->content = ft_strndup(str,
				ft_skipword(str, DELIMITERS) - str, ML_ARGUMENT);
	}
}

_Bool	is_good_label(char *str, _Bool argument)
{
	while (*str && !ft_isspecial(*str, DELIMITERS))
	{
		if (!argument && *str == LABEL_CHAR)
			return (1);
		if (!ft_isspecial(*str, LABEL_CHARS) )
			return (0);
	}
	return (1);
}



_Bool	arg_label_recognition(char *str, t_token *token)
{
	char *word_end;
	if (*str == REGISTER_CHAR && ft_isdigitalword(str + 1, DELIMITERS))
		token->content = (void*)add_arg(str, T_REG);
	else if (*str == DIRECT_CHAR && ft_isdigitalword(str + 1, DELIMITERS))

	word_end = ft_skipword(str, DELIMITERS);
	if (word_end - str > 1 && )
		return (2);
}

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
	else if (arg_label_recognition(str, token))
		token->type = ARGUMENT;
	else if (
//labels
1
);
	else if (
//commands
1
);
	else if (*str == "\"" || (token->prev && token->prev->type == STRING))
		token->type = STRING;

}
*/
