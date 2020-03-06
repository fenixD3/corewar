/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:26 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 16:22:28 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft/libft.h>
#include <fcntl.h>
#include <libft/get_next_line.h>
#include "file_to_list.h"
#include "asm.h"
#include "op.h"

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
}*/

int main(void)
{
	t_token *token;
	t_label *label;
	t_cmd	*cmd;
	int fd;

	token = NULL;
	label = NULL;

	fd = open("/Users/mdeanne/corewar/vm_champs/test.s", O_RDONLY);
	tokenize(fd, &token, &label);
	cmd = make_commands_lst(token);

	return (0);
}