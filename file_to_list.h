/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    file_to_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:27:39 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 18:27:41 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_TO_LIST_H
# define FILE_TO_LIST_H

typedef struct	s_fline
{
	char			*line;
	struct s_fline	*next;
}				t_fline;

t_fline			*file_to_list(int fd);

#endif
