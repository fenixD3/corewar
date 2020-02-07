/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackbox_memlist.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:16:00 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 19:16:07 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLACKBOX_MEMLIST_H
# define BLACKBOX_MEMLIST_H
# define ML_MALLOC 1
# define ML_DELELEM 2
# define ML_CLEARLIST 3
# include <stdlib.h>

/*
** ml is acronym for words "memory list"
*/

typedef struct	s_ml
{
	void		*data;
	struct s_ml	*next;
	struct s_ml	*prev;
}				t_ml;

t_ml			*ml_create(void *ptr);
_Bool			ml_push_front(t_ml **head, t_ml *new);

void			ml_delelem(t_ml **head, void *ptr);
_Bool			ml_clear_lst(t_ml **head);

#endif
