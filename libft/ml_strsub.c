/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:28:00 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strsub(const char *s, unsigned int start, size_t len,
															u_int32_t lst_num)
{
	char *substr;

	if (!s || !(substr = ml_strnew(len, lst_num)))
		return (NULL);
	substr = ft_strncpy(substr, s + start, len);
	return (substr);
}
