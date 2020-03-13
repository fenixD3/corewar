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
#include <errno.h>
#include <stdbool.h>
#include "ft_ptintf.h" ///

void			print_in_file(char *file_name, t_token *token, header_t *header)
{
	int			fd;
	int			nulle;
	char		*name;

	nulle = 0;
	errno = 0;

	if ((name = ft_strrchr(file_name, '.')))
		*name = '\0';
	name = ml_strjoin(file_name, ".cor", ML_CHECK_N_FILENAME);
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
	{
		perror("ERROR: Cant't write in file because");
		exit (1);
	}
	ft_printf("Writing output program to %s\n", name);
	print_header(fd, header);
	write(fd, &nulle, 4);
	print_commands(fd, token);
	close(fd);
}

void open_and_tokenize_file(char *file_name, t_token_sec *check_list,
																t_token **token)
{
	int	fd;
	char		*name;
	t_label		*label;

	label = NULL;

	errno = 0;
	if ((fd = open(file_name, O_DIRECTORY)) >= 0)
	{
		ft_printf("ERROR: file %s is a directory\n", file_name);
		exit (1);
	}
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		strerror(errno);
		exit (1);
	}
	tokenize(fd, token, &label);
	close(fd);

	//print_tokens(*token, 0);

	token_sequence(*token, check_list);
	label_substitution(label);
}

int main(int ac, char **av)
{
	t_token		*token;
	header_t	header;
	t_token_sec	check_list;
	int			i;

	i = 0;
	while (++i < ac)
	{
		ft_printf("\nReading %s\n", av[i]);
		token = NULL;
		open_and_tokenize_file(av[i], &check_list, &token);
		init_headers(&header, token, &check_list);
		print_in_file(av[i], token, &header);
		ml_free_all();
	}


	return (0);
}
