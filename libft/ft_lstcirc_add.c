/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:25:51 by mdeanne           #+#    #+#             */
/*   Updated: 2019/06/27 17:28:37 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcirc_add(t_list **cur, char const *content, size_t content_size)
{
	t_list *new;

	if (!cur || !(new = ft_lstcirc_strnew(content, content_size, 0)))
		return (NULL);
	if (!*cur)
		*cur = new;
	else
	{
		new->next = (*cur)->next;
		(*cur)->next = new;
	}
	return (new);
}
