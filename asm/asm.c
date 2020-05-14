/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:26 by mdeanne           #+#    #+#             */
/*   Updated: 2020/05/14 18:54:43 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "ft_ptintf.h"
#include "asm.h"

void	print_in_file(char *file_name, t_token *token, header_t *header)
{
	int			fd;
	int			nulle;
	char		*name;

	nulle = 0;
	errno = 0;
	if ((name = ft_strrchr(file_name, '.')))
		*name = '\0';
	name = ml_strjoin(file_name, ".cor", ML_CHECK);
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
	{
		perror("ERROR: Cant't write in file because");
		exit(1);
	}
	ft_printf("Writing output program to %s\n", name);
	print_header(fd, header);
	write(fd, &nulle, 4);
	print_commands(fd, token);
	close(fd);
}

void	open_and_tokenize_file(char *file_name, t_token_sec *check_list,
							t_token **token)
{
	int		fd;
	t_label	*label;

	label = NULL;
	errno = 0;
	if ((fd = open(file_name, O_DIRECTORY)) >= 0)
	{
		ft_printf("ERROR: %s is a directory\n", file_name);
		exit(1);
	}
	else if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("ERROR: file %s does not exist\n", file_name);
		exit(1);
	}
	tokenize(fd, token, &label);
	close(fd);
	token_sequence(*token, check_list);
	label_substitution(label);
}

int		main(int ac, char **av)
{
	t_token		*token;
	header_t	header;
	t_token_sec	check_list;
	int			i;

	i = 0;
	while (++i < ac)
	{
		token = NULL;
		open_and_tokenize_file(av[i], &check_list, &token);
		init_headers(&header, token);
		print_in_file(av[i], token, &header);
		ml_free_all();
	}
	return (0);
}
