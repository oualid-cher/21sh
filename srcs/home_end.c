/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:16:11 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/21 12:55:23 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		ft_home(char *str, int *c_i)
{
	int		i;

	i = *c_i;
	while (i++ < ft_strlen(str))
		ft_leftright(&str, LEFT, c_i);
	tputs(tgetstr("rc", NULL), 1, ft_put);
}

void		ft_end(char *str, int *c_i)
{
	int		i;

	i = *c_i;
	while (--i >= 0)
		ft_leftright(&str, RIGHT, c_i);
}
