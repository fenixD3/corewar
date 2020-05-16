/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:29 by ylila             #+#    #+#             */
/*   Updated: 2020/04/02 10:33:46 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ml_get_next_line(const int fd, char **line, u_int32_t lst_num)
{
	char			buf[BF_SZ_GNL + 1];
	static t_gnl	*lst;
	char			*tmp;
	ssize_t			b;

	if (fd < 0 || !line || (!find_fd(&lst, fd) && !(ad_fd(&lst, new_node(fd)))))
		return (-1);
	find_fd(&lst, fd);
	while (!(ft_strchr(lst->str, '\n')) && (b = read(fd, &buf, BF_SZ_GNL)) > 0)
	{
		buf[b] = '\0';
		tmp = lst->str;
		lst->str = ft_strjoin(lst->str, buf);
		ft_strdel(&tmp);
	}
	if (b == -1 || (!*(tmp = lst->str) && free_node(&lst)))
		return (b == -1 ? -1 : 0);
	if (!(lst->lb = ft_strchr(lst->str, '\n')))
		*line = ml_strdup(lst->str, lst_num);
	else
		*line = ml_strsub(lst->str, 0, lst->lb - lst->str, lst_num);
	lst->str = ft_strsub(lst->str, (unsigned int)(ft_strlen(*line) + 1),
			ft_strlen(lst->str) - ft_strlen(*line));
	ft_strdel(&tmp);
	return (1);
}
