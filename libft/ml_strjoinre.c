/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_strjoinre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:48:27 by mdeanne           #+#    #+#             */
/*   Updated: 2019/06/25 16:41:15 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ml_strjoinre(char **s1, char const *s2, u_int32_t lst_num)
{
	char *new;

	if (!(new = ml_strjoin(*s1, s2, lst_num)))
		return (NULL);
	free(*s1);
	*s1 = new;
	return (*s1);
}
