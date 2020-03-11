/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_args_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:50:26 by mcanhand          #+#    #+#             */
/*   Updated: 2020/03/11 15:50:31 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <fcntl.h>
#include "asm_dasha.h"
#include <stdlib.h>
#include <stdio.h>
#include "ft_ptintf.h"


void			print_in_file(char *file_name, t_token *token, header_t *header)
{
	int			fd;
	int			nulle;

	nulle = 0;
	fd = open(file_name, O_RDWR);
	print_header(fd, header);
	write(fd, &nulle, 4);
	print_commands(fd, token);
	close(fd);
}

void	print_file(char* path)
{
	u_int8_t *ptr;
	u_int32_t buff[3000];

	int	fd = open(path, O_RDWR);
	int ret = read(fd, buff, 3000);
	ptr = (u_int8_t*)buff;
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
	close(fd);
}

char		*parse_file_name(char *file_path)
{
	char		*name;
	int			name_len;

	name_len = ft_strlen(file_path);
	name = ft_strcat(ft_strsub(file_path, 0, name_len - 1), "cor"); //ОЧИСТКА памяти
	return (name);
}

char	*open_files(char *file_name, t_token_sec *check_list,
		t_token **token)
{
	int	fd;
	char		*name;
	t_label		*label;

	label = NULL;
	//	//проверка read'ом
	name = parse_file_name(file_name);
//	fclose(fopen(name, "w"));//fclose!!!!!!!!!!
	fd = open(file_name, O_RDONLY);
	tokenize(fd, token, &label);
	token_sequence(*token, check_list);
	label_substitution(label);
	return (name);
}

int main(int ac, char **av)
{
	t_token		*token;
	header_t	header;
	t_token_sec	check_list;
	int			i;
	char        *file_tofill;

	i = 1;
	token = NULL;
	while (i < ac)
	{
		file_tofill = open_files(av[i], &check_list, &token);
		init_headers(&header, token, &check_list);
		print_in_file(file_tofill, token, &header);
		print_file(file_tofill);
		printf("\n\n");
		i++;
	}

//	ml_free_all();
	return (0);
}
