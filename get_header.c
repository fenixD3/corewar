/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:34:59 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/13 23:35:01 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include "op.h"
#include "file_to_list.h"
#include "asm.h"

static int	set_string(header_t *header, char *line, _Bool its_name, _Bool new)
{
	char *end;
	char *str;

	if (new && (!skip_delims(&line, DELIMITERS, COMMENTS) || *(line++) != '"'))
		go_exit(its_name ? "No .name string" : "No .comment string");
	end = line;
	str = (its_name) ? header->prog_name : header->comment;
	if ((end = ft_strchr(line, '"')))
	{
		if (ft_strlen(str) + end - line < (its_name) ? PROG_NAME_LENGTH : COMMENT_LENGTH)
			ft_strlcat(str, line, end - line);
		else
			go_exit((its_name) ? "Champion name too long (Max length 128)" : "Champion comment too long (Max length 2048)"); /// нужно выводить по PROG_NAME_LENGTH : COMMENT_LENGTH
	}
//	else if
	return (0);
}

static int	set_name_or_comment(header_t *header, t_fline *flst)
{
	char	*line;
	_Bool	its_name;

	line = flst->line;
	if (!skip_delims(&line, DELIMITERS, COMMENTS))
		return (0);
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		its_name = (*header->prog_name) ? go_exit("Name token doubled") : 1;
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		its_name = (*header->comment) ? go_exit("Comment token doubled") : 0;
	else
		return (-1);
	if (set_string(header, line, its_name, 1))
		;//while
	return (0);
}

void		get_header_strings(header_t *header, t_fline *flst)
{
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
}
