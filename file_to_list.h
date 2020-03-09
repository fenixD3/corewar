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
# include <stdlib.h>
# include <stdint.h>

typedef uint32_t u_int32_t;

typedef struct	s_fline
{
	char			*line;
	struct s_fline	*next;
}				t_fline;

t_fline *file_to_list(int fd, u_int32_t lst_num);

#endif
