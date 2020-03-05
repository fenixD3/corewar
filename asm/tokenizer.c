/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:33 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 16:22:35 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "asm.h"
#include "libword.h"


#include <stdio.h>


void	tokenize(int fd, t_token **token, t_label **label)
{
	t_pc		pc;
	u_int8_t	flag;
	char 		*tmp;

	static int i;

	pc.row = 0;
	while ((get_next_line(fd, &tmp)) > 0)
	{
		pc.line = tmp;
		pc.column = 0;
		flag = 0;
		rewind_n(&pc, ft_skipdelims(pc.line, SPACES) - tmp);
		while (*pc.line)
		{
			add_token(&pc, token, label, flag);
			if ((flag = token_rewind(&pc, *token)) == ENDLINE)
				break ;
		}
		add_token(&pc, token, label, flag);
		pc.line = tmp;
		free(tmp);
		pc.row++;
	}
	///здесь проверка lseek'ом
	lseek(fd, -1, SEEK_CUR);
	read(fd, tmp, 1);
	if (*tmp == '\n')

		add_token(&pc, token, label, ENDFILE);
	if (!*token)
		go_exit("ERROR: File is empty");
	while ((*token)->prev)
		*token = (*token)->prev;
//	while ((*label)->prev)
//		*label = (*label)->prev;
}
