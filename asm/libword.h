/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libword.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:55:11 by mdeanne           #+#    #+#             */
/*   Updated: 2020/04/02 10:33:46 by yas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBWORD_H
# define LIBWORD_H

int		ft_wordequ(char *ethalon, char *str, char *delims);
_Bool	ft_isspecial(char c, char *special);
char	*ft_skipword(char *str, char *delims);
char	*ft_skipdelims(char *str, char *delims);
_Bool	ft_isdigitalword(char *str, char *delims);

#endif
