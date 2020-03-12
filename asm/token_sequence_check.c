/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sequence_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:47:46 by mcanhand          #+#    #+#             */
/*   Updated: 2020/03/11 15:47:52 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "asm_dasha.h"
#include "asm.h"

/*
void 	init_check_list(t_token_sec *check_list)
{
	check_list->arg = false;
	check_list->command = false;
	check_list->comment = false;
	check_list->comment_prog = false;
	check_list->separator = false;
	check_list->str_comment = false;
	check_list->str_name = false;
	check_list->name = false;
	check_list->new_line = true;
	check_list->chmp_name = NULL;
	check_list->chmp_comment = NULL;
	check_list->label = false;
}
*/

void	comm_or_name(t_token *token, t_token_sec *check_list)
{
	if ((check_list->name && !check_list->comment_prog) ||
		(check_list->name && check_list->comment_prog &&
		check_list->str_comment))
	{
		check_list->chmp_name = (check_list->str_name) ?
		ml_strjoin(check_list->chmp_name,
		((char *)token->content + 1), ML_CHECK) : ((char *)token->content + 1);
		check_list->str_name = true;
		check_list->new_line = false;
	}
	else if ((check_list->comment_prog && check_list->name &&
		check_list->str_name) || (!(check_list->name &&
		check_list->str_name) && check_list->comment_prog))
	{
		check_list->chmp_comment = (check_list->str_comment) ?
		ml_strjoin(check_list->chmp_comment,
		((char *)token->content + 1), ML_CHECK) : ((char *)token->content + 1);
		check_list->str_comment = true;
		check_list->new_line = false;
	}
	else
		token_exit(ASM_FILE_ERR, token);
}

void	if_str_check(t_token *token, t_token_sec *check_list)
{
	unsigned long len;
	int		limit;

	if (token->type == STRING)
	{
		limit = (check_list->name && !check_list->comment_prog) ?
		        PROG_NAME_LENGTH : COMMENT_LENGTH;
		if (ft_strlen((char *)token->content) > limit)
			token_exit(((check_list->name && !check_list->comment_prog) ?
			            ASM_TOLONG_NAME : ASM_TOLONG_COMMENT), token);
		len = ft_strlen((char *)token->content) - 1;
		((char *)token->content)[len] = '\0';
		comm_or_name(token, check_list);
	}
}

void	if_command(t_token *token, t_token_sec *check_list)
{
	const char	*com_name = (char *)(token->content);
	int			i;

	i = 0;
	if (token->type == COMMAND)
	{
		if (!check_list->str_comment || !check_list->name)
			token_exit(ASM_C_N_MISSING, token);
		if (!check_list->new_line)
			token_exit(ASM_NL_MISSING, token);
		else
		{
			check_list->new_line = false;
			check_list->command = true;
			check_list->arg = false;
			while (g_op[i].name && !ft_strequ(com_name, g_op[i].name)) /// added "g_op[i].name &&"
				i++;
			if (!g_op[i].code || !(token->content = (void*)&g_op[i].code))
				token_exit(ASM_INVALID_CMD, token);
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
				token_exit(ASM_WRONG_SEPARATOR, token);
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
