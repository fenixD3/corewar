/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:04:17 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 19:04:19 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

t_token *add_token(t_pc *pc)
{
	t_token *new;

	new = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new->row = pc->row;
	new->column = pc->column;


	return (new);
}