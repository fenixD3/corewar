/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:35:08 by mdeanne           #+#    #+#             */
/*   Updated: 2020/04/02 10:33:46 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libword.h"

char	*ft_skipword(char *str, char *delims)
{
	while (*str && !ft_isspecial(*str, delims))
		str++;
	return (str);
}

char	*ft_skipdelims(char *str, char *delims)
{
	while (*str && ft_isspecial(*str, delims))
		str++;
	return (str);
}
