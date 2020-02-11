//
// Created by Mort Deanne on 11/02/2020.
//

#ifndef ASM_H
#define ASM_H

_Bool	is_special_char(char c, char *specials);

_Bool	skip_delims(char **line, char *delims, char *comments);
char	**fast_strsplit(char *line, char *delims, char *comments); // may be replaced to libft

#endif
