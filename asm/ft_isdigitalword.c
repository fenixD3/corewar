/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigitalword.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:03:55 by mdeanne           #+#    #+#             */
/*   Updated: 2020/04/02 10:33:46 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libword.h"

_Bool	ft_isdigitalword(char *str, char *delims)
{
	if (!ft_isdigit(*str))
		return (0);
	while (*str && !ft_isspecial(*str, delims))
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
