/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_complex_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 23:33:04 by mdeanne           #+#    #+#             */
/*   Updated: 2020/01/04 23:33:06 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_complex_string(char *str, char delim)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == delim)
		{
			i++;
			while (*str && *str == delim)
				str++;
		}
		if (*str)
			str++;
	}
	return (i);
}
