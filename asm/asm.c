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

#include "asm_dasha.h"

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

int main(void)
{
	t_token		*token;
	t_label		*label;
	header_t	*header;
	t_token_sec	*check_list;
	int			fd;
	int			fd_wr;
	uint8_t buff[128];
	u_int32_t *ptr32;

	token = NULL;
	label = NULL;

	fd = open("/Users/romancheremin/Desktop/mdall/test.s", O_RDONLY);
	fd_wr = open("/Users/romancheremin/Desktop/mdall/my_bits", O_RDWR);
//	fd = open("/Users/mcanhand/test.s", O_RDONLY);
//	fd_wr = open("/Users/mcanhand/my_bits", O_RDWR);
	tokenize(fd, &token, &label);
	token_sequence(token, &check_list);
    init_headers(&header, token, check_list);

	print_header(fd_wr, header);
	lseek(fd_wr, 0, SEEK_SET);

	int ret = read(fd_wr, buff, 128);
	close(fd_wr);
	close(fd);
	ptr32 = (u_int32_t*)buff;
	printf("%0x\n", *ptr32);
	ml_free_list(2);

	ml_free_list(3);
	ml_free_list(4);
	ml_free_list(5);
	return (0);
}
