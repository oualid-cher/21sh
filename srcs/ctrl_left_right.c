/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 11:37:25 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/16 01:33:47 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		ft_ctrl_left(int *c_i, char *str)
{
	int		i;

	i = ft_strlen(str) - *c_i - 1;
	while (i > 0)
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i--;
			break ;
		}
		i--;
	}
	while (*c_i < ft_strlen(str) && *c_i < (ft_strlen(str) - i))
		ft_leftright(&str, LEFT, c_i);
}

void		ft_ctrl_right(int *c_i, char *str)
{
	int		i;

	i = ft_strlen(str) - *c_i - 1;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			break ;
		}
	}
	while (*c_i >= 0 && *c_i > (ft_strlen(str) - i))
		ft_leftright(&str, RIGHT, c_i);
}
