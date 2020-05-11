/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_comands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:50:34 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 00:05:08 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

u_int8_t	calc_arg_type_code(t_token *token)
{
	u_int8_t		num_args;
	int				i;
	unsigned int	res;
	t_op			*op;

	i = 0;
	res = 0;
	op = &g_op[*(u_int8_t*)token->content - 1];
	num_args = op->num_args;
	while (num_args--)
	{
		while ((token->type != ARGUMENT && token->type != ARGUMENT_LABEL))
			token = token->next;
		if (((t_arg*)token->content)->type & T_REG)
			res |= REG_CODE << (i + 6);
		else if (((t_arg*)token->content)->type & T_IND)
			res |= IND_CODE << (i + 6);
		else if (((t_arg*)token->content)->type & T_DIR)
			res |= DIR_CODE << (i + 6);
		token = token->next;
		i -= 2;
	}
	return (res);
}

void		write_reverse(t_token *token, t_op *op, int fd)
{
	u_int32_t		*p32;
	u_int8_t		*p8;

	p32 = (u_int32_t*)&((t_arg*)token->content)->num;
	p8 = (u_int8_t*)p32;
	if (((t_arg*)token->content)->type & T_DIR)
	{
		if (op->size_t_dir == DIR_LONG_LEN)
		{
			write(fd, &p8[3], 1);
			write(fd, &p8[2], 1);
		}
	}
	write(fd, &p8[1], 1);
	write(fd, &p8[0], 1);
}

void		print_args(int fd, t_token *token)
{
	t_op			*op;
	u_int8_t		res8;
	u_int8_t		num_args;

	op = &g_op[*(u_int8_t*)token->content - 1];
	num_args = op->num_args;
	while (num_args--)
	{
		while ((token->type != ARGUMENT && token->type != ARGUMENT_LABEL))
			token = token->next;
		if (((t_arg*)token->content)->type & T_REG)
		{
			res8 = (u_int8_t)((t_arg*)token->content)->num;
			write(fd, &res8, 1);
		}
		else
			write_reverse(token, op, fd);
		token = token->next;
	}
}

void		print_commands(int fd, t_token *token)
{
	unsigned char	res;
	int				com_code;

	while (token->next != NULL)
	{
		if (token->type == COMMAND)
		{
			com_code = *(u_int8_t *)token->content - 1;
			write(fd, &g_op[com_code].code, 1);
			if (g_op[com_code].argument_type_code)
			{
				res = calc_arg_type_code(token);
				write(fd, &res, 1);
			}
			print_args(fd, token);
		}
		token = token->next;
	}
}
