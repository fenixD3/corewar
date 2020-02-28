/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_strsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:11 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 16:22:14 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	is_special_char(char c, char *specials)
{
	while (*specials)
	{
		if (c == *specials)
			return (1);
		specials++;
	}
	return (0);
}

_Bool skip_delims(char **line, char *delims, char *comments)
{
	while (**line && is_special_char(**line, delims))
		(*line)++;
	if (!*line || (comments && is_special_char(**line, comments)))
		return (0);
	return (1);
}

static _Bool	skip_word(char **line, char *delims, char *comments)
{
	while (**line)
	{
		if (is_special_char(**line, delims))
			return (1);
		if (is_special_char(**line, comments))
			return (0);
		(*line)++;
	}
	return (0);
}

static size_t	count_words(char *line, char *delims, char *comments)
{
	size_t	words;

	words = 0;
	while (*line)
	{
		if (!skip_delims(&line, delims, comments))
			break ;
		words++;
		if (!skip_word(&line, delims, comments))
			break ;
		line++;
	}
	return (words);
}

char			**fast_strsplit(char *line, char *delims, char *comments, void *alloc_func(size_t))
{
	char 	**arrptr;
	size_t	words;

	if (!line || !*line || !delims || !*delims ||
								!(words = count_words(line, delims, comments)))
		return (NULL);
	arrptr = (char**)alloc_func(sizeof(char*) * (words + 1));
	while (*line)
	{
		if (!skip_delims(&line, delims, comments))
			break ;
		*arrptr = line;
		arrptr++;
		if (!skip_word(&line, delims, comments))
			break ;
		*line = '\0';
		line++;
	}
	*arrptr = NULL;
	return (arrptr - words);
}
