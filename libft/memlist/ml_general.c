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

void		*ml_malloc(size_t size, uint32_t list_num)
{
	void *data;

	if (!(data = malloc(size)))
	{
		ml_static_lists(NULL, ML_CLEARLIST, list_num);
		return (NULL);
	}
	ml_static_lists(data, ML_MALLOC, list_num);
	return (data);
}

void		ml_free(void *ptr, uint32_t list_num)
{
	ml_static_lists(ptr, ML_DELELEM, list_num);
}

void		ml_free_list(uint32_t list_num)
{
	ml_static_lists(NULL, ML_CLEARLIST, list_num);
}

void		ml_free_all(void)
{
	ml_static_lists(NULL, ML_CLEARALL, 0);
}
