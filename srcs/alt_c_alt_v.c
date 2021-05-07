/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_c_alt_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:32:09 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/16 01:54:41 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

char		*ft_copy(int *c_i, char *line, int start)
{
	char	*cp;
	int		i;
	int		j;

	cp = NULL;
	i = ft_strlen(line) - *c_i;
	j = ft_strlen(line) - start;
	if (*c_i < start)
	{
		cp = ft_strsub(line, j, i - j + 1);
	}
	else if (*c_i > start)
	{
		cp = ft_strsub(line, i, j - i);
	}
	return (cp);
}

char		*ft_paste(int *c_i, char *line)
{
	char	*tmp;
	char	*rest;
	char	*ret_line;
	char	*cl;

	tmp = ft_strsub(line, 0, ft_strlen(line) - *c_i);
	cl = NULL;
	rest = ft_strsub(line, ft_strlen(line) - *c_i, *c_i);
	ret_line = ft_strjoin(tmp, g_cp);
	cl = ret_line;
	ret_line = ft_strjoin(ret_line, rest);
	ft_strdel(&cl);
	ft_strdel(&tmp);
	ft_strdel(&rest);
	ft_clearline();
	ft_putstr(ret_line);
	return (ret_line);
}
