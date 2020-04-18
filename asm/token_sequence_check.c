/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sequence_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:47:46 by mcanhand          #+#    #+#             */
/*   Updated: 2020/04/04 16:55:15 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "asm_dasha.h"
#include "asm.h"


void	if_str_check(t_token *token, t_token_sec *check_list)
{
	if (token->type == STRING)
	{
		token = token->prev;
		while (token && token->type == NEW_LINE)
			token = token->prev;
		if (!token || (token->type != STRING && token->type != NAME &&
												token->type != COMMENT_PROG))
			token_exception(ASM_INVALID_STR_PLACE, token, 0);
		if (token->type == NAME)
			check_list->str_name = true;
		else if (token->type == COMMENT_PROG)
			check_list->str_comment = true;
	}
}

void	if_command(t_token *token, t_token_sec *check_list)
{
	const char	*com_name = (char *)(token->content);
	int			i;

	i = 0;
	if (token->type == COMMAND)
	{
		if (!check_list->str_name)
			go_exit(ASM_NAME_MISSING);
		if (!check_list->str_comment)
			go_exit(ASM_CMNT_MISSING);
		if (!check_list->new_line)
			token_exception(ASM_NL_MISSING, token, 0);
		else
		{
			check_list->new_line = false;
			check_list->command = true;
			check_list->arg = false;
			while (g_op[i].name && !ft_strequ(com_name, g_op[i].name))
				i++;
			if (!g_op[i].code || !(token->content = (void*)&g_op[i].code))
				token_exception(ASM_INVALID_CMD, token, 0);
			if (g_op[i].code > MAX_COMMANDS)
				go_exit("ERROR: Please don't touch options.h file");
			command_check(token);
		}
	}
}

void token_sequence(t_token *token, t_token_sec	*check_list)
{
	ft_memset(check_list, 0, sizeof(*check_list));
	check_list->new_line = true; /// нужно ли инициализировать отдельно? не знаю, вроде и без него работает
	while (token != NULL)
	{
		if (token->type == SEPARATOR)
		{
			if (check_list->separator)
				token_exception(ASM_WRONG_SEPARATOR, token, 0);
			check_list->separator = true;
		}
		if_nl_or_comment(token, check_list);
		if_name(token, check_list);
		if_comment_prog(token, check_list);
		if_str_check(token, check_list);
		if_command(token, check_list);
		if_label(token, check_list);
		if_arg(token, check_list);
		token = token->next;
	}
}
