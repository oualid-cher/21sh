/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:09:11 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 18:33:33 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			ft_func2(t_rline *rline)
{
	char	**tmp;

	tmp = ft_strsplit(g_line, ' ');
	if (rline->c == '\t' && tmp && tmp[0] && !rline->c_i &&
	g_line[ft_strlen(g_line) - 1] != ' ')
	{
		ft_strdbldel(&tmp);
		rline->j = ft_strlen(g_line);
		if (!(rline->op = ft_tab((char)rline->old_c, &rline->env, &rline->j)))
			return (1);
		ft_strdel(&rline->print_line);
		rline->print_line = ft_strdup(g_line);
		rline->c_i = 0;
	}
	if (rline->old_c == '\t' && rline->c != '\t')
		rline->op = save_dir(0);
	ft_func(rline);
	if (rline->c == 127 && rline->print_line && (ft_strlen(g_line) ||
	ft_strlen(rline->print_line)) && (rline->c_i != (int)ft_strlen(g_line) ||
	rline->c_i != (int)ft_strlen(rline->print_line)))
		ft_execdel(rline);
	ft_strdbldel(&tmp);
	return (0);
}

int			ft_sig(t_rline *rline)
{
	if (g_sig == 1)
	{
		rline->old_c = 0;
		rline->c_i = 0;
		if (rline->print_line && (rline->old_c == UP || rline->old_c == DOWN))
			ft_strdel(&rline->print_line);
		g_sig = 0;
		if (rline->c == '\n')
		{
			ft_putchar('\n');
			ft_strdel(&g_line);
			ft_strdel(&rline->print_line);
			ft_strdbldel(&rline->env);
			return (1);
		}
		if (rline->c == 4)
		{
			ft_strdel(&rline->print_line);
			return (2);
		}
	}
	return (0);
}

int			ft_countlines(char *file_path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	if ((fd = open(file_path, O_RDONLY)) < 0)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		ft_strdel(&line);
	}
	close(fd);
	return (i);
}
