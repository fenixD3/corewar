/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_findcontent_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:21:36 by mdeanne           #+#    #+#             */
/*   Updated: 2019/06/27 17:30:39 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstcirc_findcontent_size(t_list **lst, size_t content_size)
{
	t_list *cur;

	if (!lst || !*lst)
		return (0);
	if ((*lst)->content_size == content_size)
		return (1);
	cur = (*lst)->next;
	while (cur != *lst && cur->content_size != content_size)
		cur = cur->next;
	if (cur == *lst)
		return (0);
	return ((*lst = cur) == cur);
}
