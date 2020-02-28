/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memlist_bottleneck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:04:06 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/26 20:14:58 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "blackbox_memlist.h"

void	ml_innerlist(void *ptr, u_int8_t rule,
											t_ml_lists **lst, t_ml_lists **head)
{
	if (rule == ML_MALLOC)
	{
		if (!ml_push_front(&(*lst)->list, ml_create(ptr)))
		{
			ft_putendl("ERROR: can't alloc memory");
			exit(1);
		}
	}
	else if (rule == ML_DELELEM)
		ml_delelem(&(*lst)->list, ptr);
	else if (rule == ML_CLEARLIST)
		ml_clear_lst(lst, head);
}

void	ml_static_lists(void *ptr, u_int8_t rule, u_int32_t list_num)
{
	static	t_ml_lists	*lst;
	t_ml_lists			*head;

	if (rule == ML_CLEARALL)
	{
		ml_clear_all_lists(lst, NULL);
		lst = NULL;
		return ;
	}
	head = lst;
	while (lst && lst->next && lst->list_num < list_num)
		lst = lst->next;
	if ((!lst || lst->list_num != list_num))
		if (rule == ML_MALLOC)
			lst = add_ml_list(list_num, &lst);
		else
			go_exit("COMPILE ERROR: you want delete element(s) in memory \
group what does not exist");
	ml_innerlist(ptr, rule, &lst, &head);
	if (head)
		lst = head;
}
