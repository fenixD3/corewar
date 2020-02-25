/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:16:25 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 19:16:27 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blackbox_memlist.h"

void		ml_clear_all_lists(t_ml_lists *lst)
{
	t_ml_lists *prev;

	prev = lst;
	lst = lst->next;
	while (lst)
	{
		ml_clear_lst(&prev->list);
		free(prev);
		prev = lst;
		lst = lst->next;
	}
	ml_clear_lst(&prev->list);
}

_Bool		ml_clear_lst(t_ml **head)
{
	t_ml *prev;

	if (!head || !*head)
		return (0);
	prev = *head;
	*head = (*head)->next;
	while (*head != NULL)
	{
		free(prev->data);
		free(prev);
		prev = *head;
		*head = (*head)->next;
	}
	free(prev->data);
	free(prev);
	return (1);
}

void		ml_delelem(t_ml **head, void *ptr)
{
	t_ml *tmp;

	tmp = *head;
	if (tmp->data == ptr)
		*head = (*head)->next;
	else
	{
		while (tmp->data != ptr)
			tmp = tmp->next;
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	free(tmp->data);
	free(tmp);
}
