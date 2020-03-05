/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_strnew.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:22:55 by mdeanne           #+#    #+#             */
/*   Updated: 2019/06/27 17:22:55 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcirc_strnew(char const *content, size_t content_size)
{
	t_list *new;

	new = (t_list*)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (content)
	{
		new->content = (void *)ft_strdup(content);
		if (!(new->content))
		{
			free(new);
			return (NULL);
		}
	}
	else
		new->content = NULL;
	new->content_size = content_size;
	new->next = new;
	return (new);
}
