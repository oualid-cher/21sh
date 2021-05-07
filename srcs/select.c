/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:33:25 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/21 23:15:37 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void			ft_selectleft(int *c_i, char *line, long c, int start)
{
	int			len;

	len = ft_strlen(line);
	if (*c_i > start && start >= 0 && *c_i < len && *c_i && c == LEFT)
	{
		tputs(tgetstr("mr", NULL), 1, ft_put);
		start = *c_i;
		ft_putchar(line[len - *c_i]);
		tputs(tgetstr("le", NULL), 1, ft_put);
	}
	else if (*c_i > 0 && *c_i < len && c == RIGHT)
	{
		tputs(tgetstr("me", NULL), 1, ft_put);
		ft_putchar(line[len - *c_i]);
		tputs(tgetstr("le", NULL), 1, ft_put);
	}
}

void			ft_selectright(int *c_i, int start, char *line, long c)
{
	int		len;

	len = ft_strlen(line);
	if (*c_i <= start && start >= 0 && *c_i > 0 && c == RIGHT)
	{
		tputs(tgetstr("mr", NULL), 1, ft_put);
		start = *c_i;
		ft_putchar(line[len - *c_i]);
		tputs(tgetstr("le", NULL), 1, ft_put);
	}
	else if (*c_i > 0 && *c_i < len && c == LEFT)
	{
		tputs(tgetstr("me", NULL), 1, ft_put);
		ft_putchar(line[len - *c_i]);
		tputs(tgetstr("le", NULL), 1, ft_put);
	}
}

void			ft_else(char **line, long c, int *c_i, int s_start)
{
	*line = ft_leftright(line, c, c_i);
	tputs(tgetstr("me", NULL), 1, ft_put);
	ft_clearline();
	if (c == ALT_C)
	{
		ft_strdel(&g_cp);
		g_cp = ft_copy(c_i, *line, s_start);
	}
	ft_putstr(*line);
	*c_i = 0;
}

int				if_r_l_ac(t_sl *select, char **line, int *c_i)
{
	if (((*select).c != RIGHT && (*select).c != LEFT) || ((*select).c == ALT_C))
	{
		ft_else(line, (*select).c, c_i, (*select).s_start);
		return (0);
	}
	else if ((*select).first_c == LEFT)
	{
		ft_selectleft(c_i, (*line), (*select).c, (*select).start);
		(*line) = ft_leftright(line, (*select).c, c_i);
		if (*c_i < (*select).s_start)
			return (0);
	}
	return (1);
}

char			*ft_select(int *c_i, char **line)
{
	t_sl		select;

	select.c = 0;
	select.start = *c_i;
	select.s_start = select.start;
	select.first_c = 0;
	while (1)
	{
		read(1, &select.c, 4);
		if (!select.first_c)
			select.first_c = select.c;
		if (!(if_r_l_ac(&select, line, c_i)))
			break ;
		else if (select.first_c == RIGHT)
		{
			ft_selectright(c_i, select.start, *line, select.c);
			ft_leftright(line, select.c, c_i);
			if (*c_i > select.s_start)
				break ;
		}
		select.c = 0;
	}
	return (ft_strdup(*line));
}
