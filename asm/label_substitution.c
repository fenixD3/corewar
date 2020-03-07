/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:32:46 by mdeanne           #+#    #+#             */
/*   Updated: 2020/03/05 16:32:48 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"
#include "libft.h"
#include "asm.h"

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
	{
		ft_printf("ERROR: [%03d:%03d] label doesn't exist",
				label_arg->token->row, label_arg->token->column); /// заменить нормальной функцией ошибки
		exit (1);
	}
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
		go_exit("WTF ERROR"); ////мало ли
	if (before)
		length = -length;
	return (length);
}

#include <stdio.h>

void 	label_substitution(t_label *head)
{
	t_label *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->token->type == ARGUMENT_LABEL)
			printf("%s -> %d\n", tmp->name, count_length_to_label(head, tmp));
		tmp = tmp->next;
	}
}
