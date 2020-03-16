/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 15:44:23 by klaurine          #+#    #+#             */
/*   Updated: 2020/03/16 15:44:25 by klaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memlist.h"
#include "asm.h"
#include "ft_ptintf.h"

void        token_exit(char *error, t_token *token)
{
    u_int32_t i;
    t_ml *lst;
    char *s;

    i = token->row;
	lst = ml_givemem(ML_GNL_LINE);
    while (lst->next)
		lst = lst->next;
    while (--i)
		lst = lst->prev;
    s = (char *)lst->data;
    i = 0;
    while (s && (' ' == *s || '\t' == *s))
	{
		i += (*s == ' ') ? 1 : 4;
		s++;
	}
    ft_printf("%s\n\t%s\n\t", error, s);
    if (token->column - i - 1)
		ft_printf("%*c", token->column - i - 1, ' ');
	ft_printf("\033[0;31m%c\033[0m\n", '^');
    exit (1);
}
