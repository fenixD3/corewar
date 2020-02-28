/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 15:22:06 by ylila             #+#    #+#             */
/*   Updated: 2020/02/26 15:49:26 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "memlist.h"

void *ft_memalloc(size_t size, u_int32_t lst_num)
{
	void *new_mem;

	if (!(new_mem = ml_malloc(size, lst_num)))
		return (NULL);
	return (ft_memset(new_mem, 0, size));
}
