/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:50:07 by mcanhand          #+#    #+#             */
/*   Updated: 2020/03/11 15:50:14 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "options.h"

void	print_reverse(int fd, u_int8_t byte, u_int32_t *num)
{
	while (byte--)
		write(fd, &((u_int8_t*)num)[byte], 1);
}

void	print_header(int fd, t_header *header)
{
	int nullo;

	print_reverse(fd, 4, &header->magic);
	write(fd, &header->prog_name, PROG_NAME_LENGTH);
	nullo = 0;
	write(fd, &nullo, 4);
	print_reverse(fd, 4, &header->prog_size);
	write(fd, &header->comment, COMMENT_LENGTH);
}
