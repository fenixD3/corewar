/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:28:05 by mdeanne           #+#    #+#             */
/*   Updated: 2020/05/17 14:28:11 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_wordequ(char *ethalon, char *str, char *delims)
{
	while (*ethalon && *str)
	{
		if (!*ethalon && *str)
		{
			while (*delims)
			{
				if (*str == *delims)
					return (1);
				delims++;
			}
			return (0);
		}
		if (*ethalon != *str)
			return (0);
		ethalon++;
		str++;
	}
	return (1);
}
