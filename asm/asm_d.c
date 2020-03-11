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

#include <libft/libft.h>
#include <fcntl.h>
#include "asm_dasha.h" ///
#include "asm.h"
#include <stdlib.h>
#include <stdio.h>
#include "ft_ptintf.h"


//void			print_in_file(char *file_name, t_token *token, header_t *header)
//{
//	int			fd;
//	int			nulle;
//
//	nulle = 0;
//	fd = open(file_name, O_RDWR);
//	print_header(fd, header);
//	write(fd, &nulle, 4);
//	print_commands(fd, token);
//	close(fd);
//}
//
//void	print_file(char* path)
//{
//	u_int8_t *ptr;
//	u_int32_t buff[3000];
//
//	int	fd = open(path, O_RDWR);
//	int ret = read(fd, buff, 3000);
//	ptr = (u_int8_t*)buff;
//	int i = 0;
//	while (ret--)
//	{
//		printf("%02x", *ptr);
//		if (i && (i + 1) % 2 == 0)
//			printf(" ");
//		if (i && (i + 1) % 16 == 0)
//			printf("\n");
//		i++;
//		ptr++;
//	}
//	close(fd);
//}

//int main(void)
//{
//	t_token		*token;
//	t_label		*label;
//	header_t	header;
//	t_token_sec	check_list;
//	int			fd;
//
//	//
//	char  *binflie = "/Users/mcanhand/test1.cor";
//	fclose(fopen(binflie, "w"));
//	//
//
//	token = NULL;
//	label = NULL;
//	fd = open("/Users/mcanhand/test.s", O_RDONLY);
//	tokenize(fd, &token, &label);
//	token_sequence(token, &check_list);
//	label_substitution(label);
//	init_headers(&header, token, &check_list);
//	print_in_file("/Users/mcanhand/test1.cor", token, &header);
//	close(fd);
//
//	print_file(binflie);
//	return (0);
//}

