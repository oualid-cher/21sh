/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:02:42 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 22:48:08 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				ft_openmanager(char old_c, DIR **op, char **str)
{
	if (old_c != '\t')
		*op = ft_pathfinder(str);
	if (!*op)
	{
		ft_strdel(str);
		return (1);
	}
	return (0);
}

int				*ft_getpos(void)
{
	char	c;
	int		i;
	char	buff[30];
	int		*coor;

	c = 0;
	i = 0;
	coor = ft_memalloc(2 * sizeof(int));
	ft_bzero(buff, 30);
	ft_bzero(coor, 2);
	write(1, "\033[6n", 4);
	while (c != 'R')
	{
		read(0, &c, 1);
		buff[i] = c;
		i++;
	}
	i = 0;
	while (buff[i++])
		if (buff[i] == '[')
			coor[0] = ft_atoi(buff + i + 1);
		else if (buff[i] == ';')
			coor[1] = ft_atoi(buff + i + 1);
	return (coor);
}

char			*ft_linemod(long c, int *c_i, char **line)
{
	if (!*c_i)
		(*line) = ft_strjoin((*line), (char*)&c);
	else
		(*line) = ft_middlewrite(line, c_i, c);
	return ((*line));
}

void			ft_del(long old_c, int c_i, char **print_line)
{
	int		tmp_c_i;
	char	*tmp;

	tmp = NULL;
	tmp_c_i = c_i;
	if (old_c == UP || old_c == DOWN || old_c == LEFT || old_c == RIGHT ||
	old_c == B_HOME || old_c == B_END || old_c == ALT_LEFT
	|| old_c == ALT_RIGHT)
	{
		tmp = g_line;
		g_line = ft_strdup(*print_line);
		ft_strdel(&tmp);
		ft_strdel(&(*print_line));
		(*print_line) = ft_strdup(g_line);
	}
	ft_leftright(&g_line, LEFT, &tmp_c_i);
	ft_delline(c_i);
}

void			ft_button(int *c_i, char **print_line, long c)
{
	char	*tmp;

	tmp = NULL;
	if (c == ALT_C && (*print_line) && (*print_line)[0])
	{
		ft_strdel(&g_line);
		g_line = ft_select(c_i, print_line);
	}
	if (c == ALT_LEFT)
		ft_ctrl_left(c_i, *print_line);
	if (c == ALT_RIGHT)
		ft_ctrl_right(c_i, *print_line);
	if (c == B_HOME)
		ft_home(*print_line, c_i);
	if (c == B_END)
		ft_end(*print_line, c_i);
	if (c == ALT_V && g_cp)
	{
		ft_strdel(&g_line);
		if (!(*print_line))
			(*print_line) = ft_strnew(0);
		g_line = ft_paste(c_i, *print_line);
		ft_strdel(print_line);
		*print_line = ft_strdup(g_line);
	}
}
