/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_givemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 21:20:40 by mdeanne           #+#    #+#             */
/*   Updated: 2020/03/16 21:20:41 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blackbox_memlist.h"
#include "libft.h"

t_ml	*ml_bb_givemem(t_ml_lists *lst, u_int32_t list_num)
{
	while (lst && lst->list_num != list_num)
		lst = lst->next;
	if (!lst)
		go_exit("COMPILE ERROR: you want find t_ml list in memory group what \
does not exist");
	return (lst->list);
}
