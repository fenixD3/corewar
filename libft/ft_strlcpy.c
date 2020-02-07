/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:03:13 by mdeanne           #+#    #+#             */
/*   Updated: 2019/06/25 16:41:15 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	if (!src || !dst)
		return (0);
	if (!size)
		return (ft_strlen(src));
	len = 0;
	while (src[len] && len < size - 1)
	{
		dst[len] = src[len];
		len++;
	}
	dst[len] = '\0';
	return (ft_strlen(src));
}
