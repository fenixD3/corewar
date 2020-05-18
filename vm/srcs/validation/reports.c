/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reports.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:28:05 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:28:11 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_usage(void)
{
	ft_printf("\033[0;35mUsage\033[0m:\t./corewar [-dump N -n N -v N]"
	" [-vis] [-a] <filename1.cor> <...>\n");
	ft_printf("\t\033[0;35m -a\033[0m    : Prints output from \"aff\""
	"(Default is to hide it)\n");
	ft_printf("\t\033[0;35m -vis\033[0m  : Calls visual interface\n");
	ft_printf("\t\033[0;35m -n\033[0m <N>: Sets order of champions\n");
	ft_printf("\n#### TEXT OUTPUT MODE ############################"
	"##############################\n");
	ft_printf("\t\033[0;35m -v\033[0m <verbosity level>\n\t(Verbosity levels, "
	"can be added together to enable several)\n");
	ft_printf("\t\t  1 : Show lives\n\t\t      2 : Show cycles\n");
	ft_printf("\t\t  4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("\t\t  8 : Show deaths\n");
	ft_printf("\t\t 16 : Show PC movements (Except for jumps)\n");
	ft_printf("\t\033[0;35m -dump\033[0m <number of cycles to dump a game>\n"
	"\t(Dumps memory after N cycles then exits)\n");
	ft_printf("\n#### VISUAL INTERFACE USAGE ##########################"
	"##########################\n\tClick on a cell of arena to see ONLY "
	"carriages on this cell. Click on a free space on the side menu to see ALL "
	"carriages\n\tClick on the side menu to see info about particular carriage."
	" Click again to hide extended data\n\tPress ENTER to speed up the game\n");
	ft_printf("\tPress ARROW to the RIGHT to take control "
	"of the game cycles\n");
	ft_printf("\tPress ESC to exit the the game\n");
	exit(5);
}

void	get_error(char *error)
{
	ft_printf("%s\n", error);
	exit(1);
}
