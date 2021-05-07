/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_tools3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:12:14 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 18:34:55 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int		ft_put(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_quit(t_rline *rline)
{
	if (rline->old_c == '\t')
		rline->op = save_dir(0);
	ft_putchar('\n');
	if (g_line && !g_line[0] && rline->c == 4)
		ft_strdel(&g_line);
	if (rline->print_line && rline->print_line && rline->print_line[0])
		ft_goendline(rline->c_i, rline->print_line);
	ft_strdbldel(&rline->env);
	if (rline->old_c && rline->print_line && rline->print_line[0] &&
	!g_flag)
		ft_historysaver(rline->print_line);
}

void	ft_goendline(int c_i, char *str)
{
	int				*coor;

	coor = ft_getpos();
	tputs(tgoto(tgetstr("cm", NULL), coor[1] - 1 + (c_i % tgetnum("co")),
	coor[0] - 1 + (ft_strlen(str) / tgetnum("co"))), 1, ft_put);
	tputs(tgetstr("cr", NULL), 1, ft_put);
	ft_memdel((void*)&coor);
}

int		ft_delnorme(char **str)
{
	ft_strdel(str);
	ft_strdel(&g_line);
	return (1);
}

char	*ft_change(char **str, t_rline *rline)
{
	int		i;
	char	*line;

	i = -1;
	line = NULL;
	if ((!(*str) || !(*str)[0]) && rline->c == 4 && ft_delnorme(str))
		return (NULL);
	if (rline->c == '\n' && (!rline->print_line))
	{
		ft_strdel(&g_line);
		ft_strdbldel(&rline->env);
		return (ft_strdup("\n"));
	}
	if (g_line && !g_line[0] && rline->old_c != 127)
		ft_strdel(&g_line);
	ft_strdbldel(&rline->env);
	line = ft_strdup(*str);
	while (line[++i])
	{
		if (line[i] == 1)
			line[i] = '\n';
	}
	ft_strdel(str);
	ft_strdel(&g_line);
	return (line);
}
