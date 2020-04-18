/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vc_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: null <null@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 21:23:02 by null              #+#    #+#             */
/*   Updated: 2020/04/14 21:23:02 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vc	*find_prev_to_insert(t_vc *head, t_vc *insert)
{
	if (!head || head->carriage->cycle_op > insert->carriage->cycle_op)
		return (NULL);
	while (head->next)
	{
		if (head->next->carriage->cycle_op > insert->carriage->cycle_op)
			return (head);
		head = head->next;
	}
	return (head);
}

t_vc 	*find_and_cut_elem(t_vc **head)
{
	t_vc *prev;
	t_vc *curr;

	if (!*head || !(*head)->next)
		return (NULL);
	prev = *head;
	if ((*head)->carriage->cycle_op > (*head)->next->carriage->cycle_op)
	{
		*head = (*head)->next;
		return (prev);
	}
	curr = prev->next;
	while (curr->next)
	{
		if (curr->carriage->cycle_op > curr->next->carriage->cycle_op)
			return(cut_vc(&prev));
		prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

void sort_vc(t_vc **head)
{
	t_vc *cutted;

	while ((cutted = find_and_cut_elem(head)))
		insert_vc(head, find_prev_to_insert(*head, cutted), cutted);
}
