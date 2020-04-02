/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:26 by mdeanne           #+#    #+#             */
/*   Updated: 2020/04/02 10:33:46 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft/libft.h>
#include <fcntl.h>
#include <libft/get_next_line.h>
//#include "file_to_list.h"
#include "asm.h"
#include "op.h"


/*
#include "options.h"
void	command_nametonum(t_token *token)
{
	char	*com_name;
	int 	i;

	i = 0;
	while (token)
	{
		if (token->type == COMMAND)
		{
			com_name = (char *)(token->content);
			while (!ft_strequ(com_name, g_op[i].name))
				i++;
			token->content = (void*)ml_malloc(sizeof(u_int8_t), ML_CMD_NUM);
			token->content = (void*)&g_op[i].code;
		}
		token = token->next;
	}

}

//int main(int ac, char **av)
//{
//	int fd;
//	t_fline *flst;
//
//	if (ac < 2)
//		go_exit("Give me file, bitch!");
//
//	if (!(fd = open(av[1], O_RDONLY)))
//		go_exit("Open file error");
//
//	flst = file_to_list(fd);
//
//	char *line = flst->next->line;
//	printf("%s\n\n", line);
//	char **arrptr;
//	if (!(arrptr = fast_strsplit(line, DELIMITERS, COMMENTS, malloc)))
//		return (2);
//	while (*arrptr)
//	{
//		printf("%s\n", *arrptr);
//		arrptr++;
//	}
//	return (0);
//}

#include<stdlib.h>
#include<stdio.h>
#include "ft_ptintf.h"
/// print memory
*/
/*int main(void)
{
	int fd = open("/Users/mdeanne/corewar/vm_champs/test.cor", O_RDONLY);
	uint8_t buf[3000];
	uint8_t *ptr;
	lseek(fd, PROG_NAME_LENGTH + COMMENT_LENGTH + 16, SEEK_CUR);
	int ret = read(fd, buf, 3000);
	ptr = buf;
	int i = 0;
	while (ret--)
	{
		printf("%02x", *ptr);
		if (i && (i + 1) % 2 == 0)
			printf(" ");
		if (i && (i + 1) % 16 == 0)
			printf("\n");
		i++;
		ptr++;
	}

	return (0);
}*//*


int main(void)
{
	t_token *token;
	t_label *label;

	int fd;

	token = NULL;
	label = NULL;

	fd = open("/Users/mdeanne/corewar/vm_champs/test.s", O_RDONLY);
	tokenize(fd, &token, &label);
	//print_tokens(token, 1);
	command_nametonum(token); // будет в проверке => удалить
	label_substitution(label); // очищает все t_label - больше незья обращаться
	print_tokens(token, 2);

	return (0);
}*/
