/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_typeflags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:11:10 by mdeanne           #+#    #+#             */
/*   Updated: 2019/12/10 22:11:14 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

_Bool	is_ddioouuxx(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X' ||
		c == 'D' || c == 'O' || c == 'U')
		return (1);
	return (0);
}

_Bool	is_aaeeffgg(char c)
{
	if (c == 'f' || c == 'F' || c == 'e' || c == 'E' || c == 'a' || c == 'A' ||
		c == 'g' || c == 'G')
		return (1);
	return (0);
}

_Bool	is_csp(char c)
{
	if (c == 'c' || c == 's' || c == 'p')
		return (1);
	return (0);
}