/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blackbox_memlist.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:16:00 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/26 19:23:23 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLACKBOX_MEMLIST_H
# define BLACKBOX_MEMLIST_H
# define ML_MALLOC 1
# define ML_DELELEM 2
# define ML_CLEARLIST 3
# define ML_CLEARALL 4
# include <stdlib.h>
# include <stdint.h>
/*
** ml is acronym for words "memory list"
*/

typedef uint8_t u_int8_t;
typedef uint32_t u_int32_t;

typedef struct	s_ml
{
	void		*data;
	struct s_ml	*next;
	struct s_ml	*prev;
}				t_ml;

typedef struct	s_ml_lists
{
	t_ml				*list;
	u_int32_t			list_num;
	struct s_ml_lists	*next;
	struct s_ml_lists	*prev;
}				t_ml_lists;

void			ml_static_lists(void *ptr, u_int8_t rule, u_int32_t list_num);

t_ml_lists		*add_ml_list(u_int32_t list_num, t_ml_lists **cur,
															t_ml_lists **head);
t_ml			*ml_create(void *ptr);
_Bool			ml_push_front(t_ml_lists **head, t_ml *new);

void			ml_clear_all_lists(t_ml_lists *lst, t_ml_lists *head);
void			ml_delelem(t_ml **head, void *ptr);
u_int8_t		ml_clear_lst(t_ml_lists **lst, t_ml_lists **head);

#endif
