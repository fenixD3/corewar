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

void		newline_endfile_check(int fd, int ret)
{
	char		c;

	if (ret < 0 || lseek(fd, -1, SEEK_CUR) == -1 || read(fd, &c, 1) != 1)
		go_exit("ERROR: Read of file");
	if (c != '\n')
		go_exit("ERROR: No new line before end of file");
}

void	tokenize_line(t_pc *pc, t_token **token, t_label **label, char *str)
{
	u_int8_t	flag;

	pc->line = str;
	pc->column = 0;
	flag = 0;
	rewind_n(pc, ft_skipdelims(pc->line, SPACES) - str);
	while (*pc->line)
	{
		add_token(pc, token, label, flag);
		if ((flag = token_rewind(pc, *token)) == ENDLINE)
			break ;
	}
	add_token(pc, token, label, flag);
	pc->line = str;
	pc->row++;
	free(str);
}

void	set_lists_at_start(t_token **token, t_label **label)
{
	while ((*token)->prev)
		*token = (*token)->prev;
	while ((*label)->prev)
		*label = (*label)->prev;
}

void	tokenize(int fd, t_token **token, t_label **label)
{
	t_pc		pc;

	char 		*tmp;
	int 		ret;

	pc.row = 0;
	while ((ret = get_next_line(fd, &tmp)) > 0)
		tokenize_line(&pc, token, label, tmp);
	if (!*token)
		go_exit("ERROR: File is empty");
	newline_endfile_check(fd, ret);
	add_token(&pc, token, label, ENDFILE);
	set_lists_at_start(token, label);
}
