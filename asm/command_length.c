/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:19:19 by mdeanne           #+#    #+#             */
/*   Updated: 2020/03/06 18:19:21 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "asm.h"

u_int32_t	command_length(t_token *token)
{
	t_op		*op;
	uint32_t	lenth;
	u_int8_t	num_args;

	op = &g_op[*(u_int8_t*)token->content - 1];
	lenth = COMMAND_LEN;
	num_args = op->num_args;
	lenth += op->argument_type_code;
	while (num_args--)
	{
		while (/*token &&*/(token->type != ARGUMENT && token->type != ARGUMENT_LABEL))
			token = token->next;
/*		if (!token)
			go_exit("ERROR: number of args not valid"); // возможно не нужная проверка*/
		if (((t_arg*)token->content)->type & T_REG)
			lenth += REG_LEN;
		else if (((t_arg*)token->content)->type & T_IND)
			lenth += IND_LEN;
		else if (((t_arg*)token->content)->type & T_DIR)
			lenth += op->size_t_dir;
		token = token->next;
	}
	return (lenth);
}