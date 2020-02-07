/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <mdeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 20:08:50 by mdeanne           #+#    #+#             */
/*   Updated: 2019/06/27 17:29:14 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		check(char *str, int ret, char **line, t_list **cur)
{
	if (ret == -1 || (!str || !*str))
		return (ret == -1 ? -1 : 0);
	if (!(*line = (!(ft_strchr(str, '\n')) ? ft_strdup(str) :
			ft_strndup(str, ft_strchr(str, '\n') - str))))
		return (-1);
	if ((ret == 0 && !*str))
		*cur = ft_lstcirc_delelem(cur);
	if (ft_strchr(str, '\n'))
		ft_strcpy(str, ft_strchr(str, '\n') + 1);
	if (ft_strcmp(*line, str) == 0)
		ft_strclr(str);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*cur;
	char			buf[BUFF_SIZE + 1];
	char			*str;
	ssize_t			ret;

	if (fd < 0 || !line || (!(ft_lstcirc_findcontent_size(&cur, (size_t)fd)) &&
							!(cur = ft_lstcirc_add(&cur, NULL, (size_t)fd))))
		return (-1);
	while (!ft_sstrchr((char*)(cur->content), '\n') &&
			(ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		str = (char*)(cur->content);
		buf[ret] = '\0';
		if (!(cur->content = (void*)ft_strjoinre(&str, buf)))
			return (-1);
	}
	str = (char*)(cur->content);
	return (check(str, ret, line, &cur));
}
