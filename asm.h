/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:38:40 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 13:38:44 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
#define ASM_H

#define INSTRUCTION 1
#define ARGUMENT_1 2
#define ARGUMENT_2 3
#define ARGUMENT_3 4


typedef struct	s_token
{
	unsigned short	type;
	unsigned int	line;

}				t_token;

typedef struct	s_label
{

}				t_label;

_Bool	is_special_char(char c, char *specials);

_Bool	skip_delims(char **line, char *delims, char *comments);
char	**fast_strsplit(char *line, char *delims, char *comments, void *alloc_func(size_t)); // may be replaced to libft

#endif
