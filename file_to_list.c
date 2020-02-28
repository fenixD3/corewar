/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:27:33 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 18:27:36 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <get_next_line.h>
#include "file_to_list.h"

void add_line_lst(t_fline **head, t_fline **tail, char *line, u_int32_t lst_num)
{
	t_fline *new;

	if (!(new = (t_fline*)ml_malloc(sizeof(t_fline), lst_num)))
		go_exit("ERROR: can't alloc memory");
	new->next = NULL;
	if (!*head)
		*head = new;
	new->line = line;
	if (*tail)
		(*tail)->next = new;
	*tail = new;
}

t_fline		*file_to_list(int fd)
{
	char	*line;
	t_fline	*tail;
	t_fline *head;
	int		flag;

	tail = NULL;
	head = NULL;
	line = NULL;

	while (get_next_line(fd, &line) > 0)
		add_line_lst(&head, &tail, line, 0);
	return (head);
}
