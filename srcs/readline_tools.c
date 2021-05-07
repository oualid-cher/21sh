/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:00:45 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 17:04:12 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		ft_delchar(void)
{
	ft_putchar(8);
	ft_putchar(127);
	ft_putchar(8);
}

void		ft_clearline(void)
{
	tputs(tgetstr("rc", NULL), 1, ft_put);
	tputs(tgetstr("cr", NULL), 1, ft_put);
	tputs(tgetstr("cd", NULL), 1, ft_put);
	ft_putstr(g_pr);
	tputs(tgetstr("sc", NULL), 1, ft_put);
}

void		ft_delline(int c_i)
{
	char	*tmp;
	char	*rest;
	int		*coor;

	tmp = NULL;
	rest = NULL;
	tmp = ft_strsub(g_line, 0, ft_strlen(g_line) - c_i - 1);
	rest = ft_strsub(g_line, ft_strlen(g_line) - c_i, ft_strlen(g_line));
	ft_strdel(&g_line);
	g_line = ft_strjoin(tmp, rest);
	coor = ft_getpos();
	if (rest && rest[0])
		ft_putstr(rest);
	ft_putchar(' ');
	tputs(tgoto(tgetstr("cm", NULL), coor[1] - 1, coor[0] - 1), 1, ft_put);
	ft_strdel(&rest);
	ft_strdel(&tmp);
	ft_memdel((void*)&coor);
}

DIR			**ft_tab_init(char **str, struct dirent **rd)
{
	(*rd) = NULL;
	(*str) = NULL;
	return (save_dir(1));
}

DIR			**ft_tab(char old_c, char ***shell, int *j)
{
	struct dirent	*rd;
	DIR				**op;
	char			*str;

	op = ft_tab_init(&str, &rd);
	if (!(ft_strchr(g_line, ' ')) && !ft_strchr(g_line, '/'))
		ft_shellfinder(*shell, old_c, j, op);
	else
	{
		if (ft_openmanager(old_c, op, &str))
			return (NULL);
		while ((rd = readdir(*op)))
			if ((!str && ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name
			, "..")) || (ft_strnstr(rd->d_name, str, ft_strlen(str)) &&
			ft_strcmp(rd->d_name, ".") && ft_strcmp(rd->d_name, "..")))
				break ;
		ft_strdel(&str);
		if (!rd)
		{
			op = save_dir(0);
			return (NULL);
		}
		ft_newline(j, rd);
	}
	return (op);
}
