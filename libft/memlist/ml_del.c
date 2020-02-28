/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:16:25 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/26 20:17:36 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "blackbox_memlist.h"

void		ml_clear_all_lists(t_ml_lists *lst, t_ml_lists *head)
{
	t_ml_lists *prev;

	prev = lst;
	lst = lst->next;
	while (lst)
	{
		ml_clear_lst(&prev, &head);
		free(prev);
		prev = lst;
		lst = lst->next;
	}
	ml_clear_lst(&prev, &head);
}

_Bool		ml_list_del_elem(t_ml_lists **lst, t_ml_lists **head)
{
	if ((*lst)->prev)
		(*lst)->prev->next = (*lst)->next;
	if ((*lst)->next)
		(*lst)->next->prev = (*lst)->prev;
	if (*lst == *head && (*lst)->next)
		*head = (*head)->next;
	else if (*lst == *head)
		*head = NULL;
	free(*lst);
	return (0);
}

u_int8_t	ml_clear_lst(t_ml_lists **lst, t_ml_lists **head)
{
	t_ml *cur;
	t_ml *prev;

	if (!lst || !*lst)
		return (0);
	if ((*lst)->list)
	{
		cur = (*lst)->list;
		prev = cur;
		cur = cur->next;
		while (cur != NULL)
		{
			free(prev->data);
			free(prev);
			prev = cur;
			cur = cur->next;
		}
		free(prev->data);
		free(prev);
	}
	ml_list_del_elem(lst, head);
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
		while (tmp && tmp->data != ptr)
			tmp = tmp->next;
		if (!tmp)
			go_exit("COMPILE ERROR: no element to free in memory group");
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	free(tmp->data);
	free(tmp);
}
