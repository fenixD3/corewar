/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memlist_bottleneck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:04:06 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/25 18:04:09 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "blackbox_memlist.h"

void	ml_innerlist(void *ptr, uint8_t rule, t_ml **head)
{
	if (rule == ML_MALLOC)
	{
		if (!ml_push_front(head, ml_create(ptr)))
		{
			ft_putendl("ERROR: can't alloc memory");
			exit(1);
		}
	}
	else if (rule == ML_DELELEM)
		ml_delelem(head, ptr);
	else if (rule == ML_CLEARLIST)
		ml_clear_lst(head);
}

void	ml_static_lists(void *ptr, uint8_t rule, uint32_t list_num)
{
	static	t_ml_lists	*lst;
	t_ml_lists			*tmp;

	if (rule == ML_CLEARALL)
	{
		ml_clear_all_lists(lst);
		lst = NULL;
		return ;
	}
	tmp = lst;
	while (lst && lst->next && lst->list_num < list_num)
		lst = lst->next;
	if (!lst || lst->list_num != list_num)
		lst = add_ml_list(list_num, &lst);
	ml_innerlist(ptr, rule, &lst->list);
	if (tmp)
		lst = tmp;
}
