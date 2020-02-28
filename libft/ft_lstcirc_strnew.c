/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcirc_strnew.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:22:55 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/26 15:49:02 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "memlist.h"

t_list *
ft_lstcirc_strnew(char const *content, size_t content_size, u_int32_t lst_num)
{
	t_list *new;

	new = (t_list*)ml_malloc(sizeof(t_list), lst_num);
	if (new == NULL)
		return (NULL);
	if (content)
	{
		new->content = (void *) ft_strdup(content, 0);
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
