/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:05:46 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strmapi(const char *s, char (*f)(unsigned int, char),
															u_int32_t lst_num)
{
	unsigned int	i;
	char			*new_str;
	char			*ptr2new;

	if (!s || !f || !(new_str = ml_strnew(ft_strlen(s), lst_num)))
		return (NULL);
	i = 0;
	ptr2new = new_str;
	while (s[i])
	{
		*ptr2new++ = (*f)(i, s[i]);
		++i;
	}
	return (new_str);
}
