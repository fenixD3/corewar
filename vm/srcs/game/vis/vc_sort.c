/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vc_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 16:54:00 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/16 16:54:41 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vc		*find_prev_to_insert(t_vc *head, t_vc *insert)
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

t_vc		*find_and_cut_unsorted_elem(t_vc **head)
{
	t_vc	*prev;
	t_vc	*curr;

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
			return (cut_vc(&prev));
		prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

void		sort_vc(t_vc **head)
{
	t_vc	*cutted;

	while ((cutted = find_and_cut_unsorted_elem(head)))
		insert_vc(head, find_prev_to_insert(*head, cutted), cutted);
}
