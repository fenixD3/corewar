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
#include "op.h"
#include "file_to_list.h"
#include <stdlib.h>

#define ML_FLST		1
#define ML_TOKEN	2
#define ML_ARGUMENT	3
#define ML_T_CONTENT 4
#define ML_LABEL	5


#define ENDSTR		1
#define NOTENDSTR	2

typedef enum	s_token_type
{
	NAME = 1,
	COMMENT_PROG,
	COMMAND,
	STRING,
	COMMENT,
	LABEL,
	ARGUMENT,
	ARGUMENT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}				t_token_type;



typedef struct	s_token
{
	t_token_type 	type;
	u_int32_t		row;
	u_int16_t		column;
	void 			*content;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_label
{
	char			*name;
	t_token 		*token;
	struct s_label	*prev;
	struct s_label	*next;
}				t_label;

typedef struct	s_argument
{
	t_token_type	type;
	void 			*content;
	u_int32_t		num;
}				t_arg;

typedef struct	s_parser_carriage
{
	u_int32_t		row;
	u_int16_t		column;
	char			*line;
}				t_pc;

t_token *
add_token(t_pc *pc, t_token **token_tail, t_label **label_tail, u_int8_t flag);
void			add_label(char *str, t_token *token, t_label **tail, t_arg_type arg_type);
t_arg           *add_arg(char *str, t_arg_type type);
char			*add_string(char *str, t_token *token);

void			token_fill(char *str, t_token *token, t_label **tail, u_int8_t flag);

///// not need

_Bool	is_special_char(char c, char *specials);

_Bool	skip_delims(char **line, char *delims, char *comments);
char	**fast_strsplit(char *line, char *delims, char *comments, void *alloc_func(size_t)); // may be replaced to libft

#endif
