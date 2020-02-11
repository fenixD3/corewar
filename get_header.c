//
// Created by Mort Deanne on 11/02/2020.
//

#include <libft/libft.h>
#include "op.h"
#include "file_to_list.h"
#include "asm.h"

static int set_string(char *field, char *line, _Bool its_name)
{
	if (!skip_delims(&line, DELIMITERS, COMMENTS))
		go_exit(its_name ? "No .name string" : "No .comment string");

}

static int set_name_or_comment(header_t *header, char *line)
{
	if (!skip_delims(&line, DELIMITERS, COMMENTS))
		return (0);
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (*header->prog_name)
			go_exit("Name token doubled");
		else
			set_string(header->prog_name, line, 1);
	}
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		if (*header->comment)
			go_exit("Comment token doubled");
		else
			set_string(header->comment, line, 0);
	}
}

void 	get_header_strings(header_t *header, t_fline **flst)
{


}