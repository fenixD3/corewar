/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:33 by mdeanne           #+#    #+#             */
/*   Updated: 2020/04/04 16:38:55 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include "asm.h"
#include "libword.h"

void newline_endfile_check(int fd, char *line, int ret, t_token *token)
{
	char *tmp;
	char c;

	if (ret < 0 || !token || !token->prev)
		go_exit("ERROR: with file");
	if (token->prev->type == COMMENT && token->prev->prev &&
	token->prev->prev->type == NEW_LINE)
		return ;
	tmp = line + ft_strlen(line) - 1;
	while (tmp + 1 != line)
	{
		if (!ft_isspecial(*tmp, SPACES))
			break ;
		tmp--;
	}
	if (tmp + 1 == line)
		return ;
	if (lseek(fd, -1, SEEK_CUR) == -1 || read(fd, &c, 1) != 1)
		go_exit("ERROR: cant't read file");
	if (c != '\n')
		go_exit("ERROR: No new line before end of file");
}

void	tokenize_line(t_pc *pc, t_token **token, t_label **label, char *str)
{
	u_int8_t	flag;

	flag = 0;
	pc->line = str;
	pc->row++;
	pc->column = 1;
	if (check_prev_str(*token, 0) != NOTENDSTR)
		rewind_n(pc, ft_skipdelims(pc->line, SPACES) - str);
	while (*pc->line || !flag)
	{
		add_token(pc, token, label, flag);
		if ((flag = token_rewind(pc, *token)) == TKNZE_BREAK)
			break ;
	}
	if ((*token)->type != NEW_LINE)
		add_token(pc, token, label, ENDLINE);
	pc->line = str;
}

void	set_lists_at_start(t_token **token, t_label **label)
{
	while ((*token)->prev)
		*token = (*token)->prev;
	while (*label && (*label)->prev)
		*label = (*label)->prev;
}

void	tokenize(int fd, t_token **token, t_label **label)
{
	t_pc		pc;
	char 		*tmp;
	int 		ret;

	int i = 0;

	pc.row = 0;
	while ((ret = ml_get_next_line(fd, &tmp, ML_GNL_LINE)) > 0)
	{
		i++;
		if (i == 4)
			i++;
		tokenize_line(&pc, token, label, tmp);
	}
	if (!*token)
		go_exit("ERROR: File is empty");
	newline_endfile_check(fd, pc.line, ret, (*token));
	add_token(&pc, token, label, ENDFILE);
	set_lists_at_start(token, label);
	//ml_free_list(ML_GNL_LINE);
}
