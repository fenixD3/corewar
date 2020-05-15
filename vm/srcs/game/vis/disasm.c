/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaurine <hecvi@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 21:28:48 by klaurine          #+#    #+#             */
/*   Updated: 2020/05/15 17:14:50 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "options.h"
#include "disasm.h"

int		types_of_args(unsigned char type, t_disasm *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = 6;
	while (i < g_op[s->code - 1].num_args)
	{
		tmp = (type >> j) & 3;
		if (tmp == REG_CODE && !(T_REG & g_op[s->code - 1].args_type[i]))
			return (0);
		else if (tmp == IND_CODE && !(T_IND & g_op[s->code - 1].args_type[i]))
			return (0);
		else if (tmp == DIR_CODE && !(T_DIR & g_op[s->code - 1].args_type[i]))
			return (0);
		else if (!tmp)
			return (0);
		s->args[i] = tmp;
		i++;
		j -= 2;
	}
	return (1);
}

void	command_output(t_disasm *s, int i, int j, char **str)
{
	char	*tmp;

	tmp = *str;
	while (g_op[s->code - 1].name[i])
	{
		tmp[i] = g_op[s->code - 1].name[i];
		i++;
	}
	tmp[i++] = ' ';
	if (!(g_op[s->code - 1].argument_type_code))
	{
		i = add_dir_ind(s, str, i, j);
		tmp[i] = '\0';
	}
	while (j < g_op[s->code - 1].num_args &&
										g_op[s->code - 1].argument_type_code)
	{
		i = add_reg(s, str, i, j);
		if (++j < g_op[s->code - 1].num_args)
		{
			tmp[i++] = SEPARATOR_CHAR;
			tmp[i++] = ' ';
		}
		tmp[i] = '\0';
	}
}

void	disasm(t_carriages *champ, char *str, unsigned char *arena)
{
	int			i;
	int			j;
	t_disasm	s;

	i = 0;
	j = 0;
	if (champ->cycle_op < 0 || champ->op_code == 0 || champ->op_code > 16)
		return ((void)ft_strcpy(str, "Incorrect command"));
	s.code = champ->op_code;
	s.args[0] = '0';
	s.arena = arena;
	s.bogie = do_steps(champ->op_pos, 1, arena);
	if (!(g_op[s.code - 1].argument_type_code))
		return (command_output(&s, i, j, &str));
	else if (!types_of_args(*(s.bogie), &s))
		return ((void)ft_strcpy(str, "Incorrect command arguments"));
	if (!arguments_value(&s, do_steps(s.bogie, 1, arena), i))
		return ((void)ft_strcpy(str, "Incorrect value of T_REG"));
	return (command_output(&s, i, j, &str));
}
