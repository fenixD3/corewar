/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:59:32 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:03 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static size_t	len_num(int num)
{
	if (num >= 0 && num <= 9)
		return (1);
	return (len_num(num / 10) + 1);
}

char			*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	nbr;

	len = len_num(n);
	if (!(str = ft_strnew(len)))
		return (NULL);
	nbr = (n < 0) ? (unsigned int)(-n) : (unsigned int)(n);
	if (nbr == 0)
		*str = '0';
	while (len-- && nbr)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[len] = '-';
	return (str);
}
