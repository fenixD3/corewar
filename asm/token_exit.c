/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:50:16 by mcanhand          #+#    #+#             */
/*   Updated: 2020/03/11 15:50:23 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_dasha.h"

int	token_exit(char *error, t_token *token)
{
	if (error)
		printf("[%03d:%03d] %s\n", token->row, token->column, error);
	exit(1);
	return (0);
}
