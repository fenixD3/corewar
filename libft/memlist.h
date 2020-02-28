/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:18:24 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 19:18:26 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMLIST_H
# define MEMLIST_H
# include <stdlib.h>

/*
** ml is acronym for words "memory list"
*/

void		*ml_malloc(size_t size, u_int32_t list_num);
void		ml_free(void *ptr, u_int32_t list_num);
void		ml_free_list(u_int32_t list_num);
void		ml_free_all(void);

#endif
