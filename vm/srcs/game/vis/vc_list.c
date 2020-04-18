/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vc_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: null <null@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 21:22:40 by null              #+#    #+#             */
/*   Updated: 2020/04/14 21:22:40 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools *vs;

void	add_new_vc(t_vc **head, t_carriages *new)
{
	t_vc *new_vc;

	new_vc = (t_vc*)ml_malloc(sizeof(t_vc), CARRIAGE_VISUAL);
	new_vc->is_open = 0;
	new_vc->carriage = new;
	new_vc->next = 0;
	insert_vc(head, find_prev_to_insert(*head, new_vc), new_vc);
}

void    insert_vc(t_vc **head, t_vc *prev, t_vc *insert)
{
	if (!*head)
		*head = insert;
	else if (!prev)
	{
		insert->next = *head;
		*head = insert;
	}
	else
	{
		insert->next = prev->next;
		prev->next = insert;
	}
}

t_vc    *cut_vc(t_vc **prev)
{
	t_vc *tmp;

	if (!(*prev)->next)
	{
		tmp = *prev;
		*prev = NULL;
		return (tmp);
	}
	tmp = (*prev)->next;
	(*prev)->next = (*prev)->next->next;
	return (tmp);
}
