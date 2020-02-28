/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:39:55 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/26 15:50:56 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "memlist.h"

char *ft_strndup(const char *s1, size_t n, u_int32_t lst_num)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	if (len < n)
		str = (char*)ml_malloc(sizeof(str) * (len + 1), lst_num);
	else
		str = (char*)ml_malloc(sizeof(str) * (n + 1), lst_num);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}
