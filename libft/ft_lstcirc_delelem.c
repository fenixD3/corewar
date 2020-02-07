/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_delelem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:28:43 by mdeanne           #+#    #+#             */
/*   Updated: 2020/01/09 23:47:36 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcirc_delelem(t_list **del_elem)
{
	t_list *prev;

	if (!del_elem || !*del_elem)
		return (NULL);
	if ((*del_elem)->next == *del_elem)
	{
		if ((*del_elem)->content)
			free((*del_elem)->content);
		free(*del_elem);
		return (NULL);
	}
	prev = (*del_elem)->next;
	while (prev->next != (*del_elem))
		prev = prev->next;
	prev->next = (*del_elem)->next;
	if ((*del_elem)->content)
		free((*del_elem)->content);
	free(*del_elem);
	return (prev);
}
