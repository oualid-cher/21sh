/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_leftright.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 00:38:57 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 17:04:46 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void	ft_left(int *coor, int *c_i, int col)
{
	if (coor[1] == 1)
		tputs(tgoto(tgetstr("cm", NULL), col - 1, coor[0] - 2), 1, ft_put);
	else
		tputs(tgetstr("le", NULL), 0, ft_put);
	*c_i += 1;
}

void	ft_right(int *coor, int *c_i, int col)
{
	if (coor[1] == col)
		tputs(tgoto(tgetstr("cm", NULL), 0, coor[0]), 1, ft_put);
	else
		tputs(tgetstr("nd", NULL), 1, ft_put);
	*c_i -= 1;
}

void	ft_adjustcursor(int c_i, char *line, long c)
{
	int		i;

	i = ft_strlen(line) - c_i;
	tputs(tgetstr("cr", NULL), 0, ft_put);
	if (c == LEFT)
		while (--i >= 0 && line[i] != 1)
		{
			tputs(tgetstr("nd", NULL), 1, ft_put);
		}
}

char	*ft_leftright(char **line, long c, int *c_i)
{
	static int		len;
	int				col;
	int				*coor;
	char			*tmp;

	col = tgetnum("co");
	tmp = NULL;
	if (*line)
		len = ft_strlen(*line);
	if (c == UP || c == DOWN)
		*c_i = 0;
	coor = ft_getpos();
	if (c == LEFT && *c_i < len)
		ft_left(coor, c_i, col);
	else if (c == RIGHT && *c_i > 0)
		ft_right(coor, c_i, col);
	if (ft_isprint(c) && ((tmp = (*line)) || !tmp))
	{
		ft_linemod(c, c_i, &(*line));
		ft_strdel(&tmp);
	}
	if (*line && (*line)[len - (*c_i)] == 1)
		ft_adjustcursor(*c_i, *line, c);
	ft_memdel((void*)&coor);
	return (*line);
}

char	*ft_middlewrite(char **line, int *i, long c)
{
	int		j;
	char	*mod_line;
	char	*rest_line;
	int		*coor;
	char	*tmp;

	tmp = NULL;
	mod_line = NULL;
	rest_line = NULL;
	coor = ft_getpos();
	j = 0;
	j = ft_strlen(*line) - *i;
	mod_line = ft_strsub(*line, 0, j);
	rest_line = ft_strsub(*line, j, ft_strlen(*line) - j);
	tmp = mod_line;
	mod_line = ft_strjoin(mod_line, (char *)&c);
	ft_strdel(&tmp);
	tmp = mod_line;
	mod_line = ft_strjoin(mod_line, rest_line);
	ft_strdel(&tmp);
	ft_putstr(rest_line);
	tputs(tgoto(tgetstr("cm", NULL), coor[1] - 1, coor[0] - 1), 1, ft_put);
	ft_memdel((void*)&coor);
	ft_strdel(&rest_line);
	return (mod_line);
}
