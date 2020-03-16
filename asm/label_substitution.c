/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:32:46 by mdeanne           #+#    #+#             */
/*   Updated: 2020/03/09 14:20:00 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"
#include "libft.h"
#include "asm.h"
#include "errors.h"
#include "asm_dasha.h"

_Bool	find_label(t_label **head, t_label *label_arg)
{
	_Bool l_before_al;

	l_before_al = 1;
	while (*head)
	{
		if ((*head) == label_arg)
			l_before_al = 0;
		if ((*head)->token->type == LABEL &&
									ft_strequ((*head)->name, label_arg->name))
			break ;
		*head = (*head)->next;
	}
	if (!*head)
		token_exit(ASM_NO_LABEL, label_arg->token);
	return (l_before_al);
}

int 	count_length_to_label(t_label *label, t_label *label_arg)
{
	int			length;
	t_token		*token;
	const _Bool	before = find_label(&label, label_arg);

	length = 0;
	token = label_arg->token;
	while (token && token->type != COMMAND)
		token = token->prev;
	if (before && token)
		token = token->prev;
	while (token)
	{
		if (token->type == COMMAND)
			length += command_length(token);
		if (token->type == LABEL && token->content == label)
			break ;
		token = (before) ? token->prev : token->next;
	}
	if (!token)
		go_exit("ERROR: Can't find label"); ////мало ли
	if (before)
		length = -length;
	return (length);
}


void 	label_substitution(t_label *head)
{
	t_label *tmp;

	if (!head)
		return ;
	tmp = head;
	while (tmp)
	{
		if (!tmp->next || !tmp->name)
			tmp = tmp;
		if (tmp->token->type == ARGUMENT_LABEL)
		{
			((t_arg*)tmp->token->content)->num = count_length_to_label(head, tmp);
			((t_arg*)tmp->token->content)->content = NULL;
			((t_arg*)tmp->token->content)->type &= ~T_LAB;
			tmp->token->type = ARGUMENT;

		}
		tmp = tmp->next;
	}
	ml_free_list(ML_LABEL);
}
