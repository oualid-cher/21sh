/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:48:16 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 17:32:06 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		ft_enter(long c, char *print_line, long old_c, int c_i)
{
	ft_putchar('\n');
	if (!g_line[0] && c == 4)
		ft_strdel(&g_line);
	if (print_line && print_line[0])
		ft_goendline(c_i, print_line);
	if (old_c && print_line && print_line[0] && !g_flag)
		ft_historysaver(print_line);
}

void		ft_termprint(t_rline *rline)
{
	char	*tmp2;

	tmp2 = NULL;
	if (ft_isprint((int)rline->c) && rline->c != '\t')
	{
		ft_print(rline->c, rline->old_c, &rline->print_line, &rline->c_i);
		if (g_line && !g_line[0])
		{
			tmp2 = g_line;
			g_line = ft_strdup(rline->print_line);
			ft_strdel(&tmp2);
		}
		tmp2 = rline->print_line;
		rline->print_line = ft_strdup(g_line);
		ft_strdel(&tmp2);
	}
}

void		ft_func(t_rline *rline)
{
	char	*tmp2;
	char	*tmp;

	tmp2 = NULL;
	tmp = NULL;
	if (rline->c == UP || rline->c == DOWN || rline->c == LEFT
		|| rline->c == RIGHT)
	{
		if (rline->c == UP || rline->c == DOWN)
		{
			tmp2 = ft_updown(rline->c, rline->old_c, &rline->num_line);
			tmp = rline->print_line;
			rline->print_line = ft_printupdown(&tmp2,
			rline->c, rline->num_line, g_line);
			ft_strdel(&tmp);
		}
		ft_leftright(&rline->print_line, rline->c,
		&rline->c_i);
	}
	else
		rline->num_line = ft_countlines("/Users/ahmcherk/.history_21sh");
	ft_button(&rline->c_i, &rline->print_line, rline->c);
	ft_termprint(rline);
}

int			ft_if(long old_c)
{
	if (old_c == LEFT || old_c == RIGHT || old_c == B_HOME ||
	old_c == ALT_LEFT || old_c == ALT_RIGHT)
		return (1);
	return (0);
}

void		ft_print(long c, long old_c, char **print_line, int *c_i)
{
	char	*tmp;

	tmp = NULL;
	ft_putchar(c);
	if (ft_if(old_c))
	{
		ft_leftright(print_line, c, c_i);
		ft_strdel(&g_line);
		g_line = ft_strdup(*print_line);
	}
	else if (old_c == UP || old_c == DOWN)
	{
		if (g_line && !g_line[0])
			ft_strdel(&g_line);
		tmp = g_line;
		g_line = ft_strdup((char*)&c);
		ft_strdel(&tmp);
		tmp = g_line;
		g_line = ft_strjoin(*print_line, g_line);
		ft_strdel(&tmp);
		ft_strdel(&(*print_line));
		(*print_line) = ft_strdup(g_line);
	}
	else
		ft_leftright(&g_line, c, c_i);
}
