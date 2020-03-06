/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 20:05:37 by mdeanne           #+#    #+#             */
/*   Updated: 2020/03/06 20:05:39 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memlist.h"
#include "asm.h"

t_cmd 	*add_command(t_token *token, t_cmd **cmd_tail)
{
	t_cmd *new;

	new = (t_cmd*)ml_malloc(sizeof(t_cmd), ML_COMMAND);
	new->token = token;
	new->command_len = command_length(token);
	new->next = NULL;
	if (!*cmd_tail)
		*cmd_tail = new;
	else
		(*cmd_tail)->next = new;
	return (new);
}

t_cmd	*make_commands_lst(t_token *token)
{
	t_cmd *cmd;
	t_cmd *cmd_tail;

	cmd_tail = NULL;
	cmd = NULL;
	while (token)
	{
		while (token && token->type != COMMAND)
			token = token->next;
		if (!token)
			break ;
		add_command(token, &cmd_tail);
		if (!cmd && cmd_tail)
			cmd = cmd_tail;
		token = token->next;
	}
	if (!cmd)
		return (NULL);
	return (cmd);
}