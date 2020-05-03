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

t_vis_tools *g_vs;

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

void 	delete_vc_by_deletion_carriage(t_carriages *del)
{
	t_vc	*prev;
	t_vc	*curr;

	prev = g_vs->vc_list;
	if (prev->carriage == del && !prev->next)
	{
/*		ml_free(prev, CARRIAGE_VISUAL);
		g_vs->vc_list = NULL;*/
		ml_free(cut_vc(&g_vs->vc_list), CARRIAGE_VISUAL);
	}
	else if (!prev->next)
		go_exit("COMPILE ERROR: discrepancy t_vc and t_carriage lists"); ///may be deleted
	else if (prev->carriage == del)
	{
		g_vs->vc_list = prev->next;
		ml_free(prev, CARRIAGE_VISUAL);
	}
	else
	{
		curr = prev->next;
		while (curr)
		{
			if (curr->carriage == del)
				break ;
			prev = curr;
			curr = curr->next;
		}
		if (!curr)
			go_exit("COMPILE ERROR: discrepancy t_vc and t_carriage lists"); ///may be deleted
		ml_free(cut_vc(&prev), CARRIAGE_VISUAL);
	}
}