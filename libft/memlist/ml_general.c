/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_general.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:16:31 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 19:16:33 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blackbox_memlist.h"
#include "libft.h"

static void		ml_static_list(void *ptr, int rule)
{
	static t_ml *head;

	if (rule == ML_MALLOC)
	{
		if (!ml_push_front(&head, ml_create(ptr)))
		{
			ft_putendl("ERROR: can't alloc memory");
			exit(1);
		}
	}
	else if (rule == ML_DELELEM)
		ml_delelem(&head, ptr);
	else if (rule == ML_CLEARLIST)
		ml_clear_lst(&head);
}

void			*ml_malloc(size_t size)
{
	void *data;

	if (!(data = malloc(size)))
	{
		ml_static_list(NULL, ML_CLEARLIST);
		return (NULL);
	}
	ml_static_list(data, ML_MALLOC);
	return (data);
}

void			ml_free(void *ptr)
{
	ml_static_list(ptr, ML_DELELEM);
}

void			ml_free_all(void)
{
	ml_static_list(NULL, ML_CLEARLIST);
}
