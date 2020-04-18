/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exception.c                                       :+:      :+:    :+:   */
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
#include "libword.h"

void	print_indent(char *str, u_int16_t end)
{
	while (*str && --end)
	{
		if (*str == '\t')
			write(1, "\t", 1);
		else
			write(1, " ", 1);
		str++;
	}
}

char *give_string_from_ml(u_int32_t row)
{
	t_ml *lst;

	lst = ml_givemem(ML_GNL_LINE);
	while (lst->next)
		lst = lst->next;
	while (--row)
		lst = lst->prev;
	return ((char *)lst->data);
}

void token_exception(char *error, t_token *token, _Bool warning)
{
    u_int16_t indent;
    char *begin;
    char *str;

	begin = give_string_from_ml(token->row);
	str = ft_skipdelims(begin, SPACES);
    ft_printf("[%d:%d] %s\n\t%s\n\t", token->row, token->column, error, str);
	print_indent(str, token->column - (str - begin));
	ft_printf("\033[0;31m%c\033[0m\n", '^');
	if (!warning)
    	exit (1);
}
