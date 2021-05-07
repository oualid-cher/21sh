/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 02:40:00 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 17:32:06 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			ft_en(char *str, char **environ)
{
	int				i;
	int				len;

	i = 0;
	len = ft_dblstrlen(environ);
	while (i < len)
	{
		if (environ[i][ft_strlen(str)] == '=' &&
		ft_strnstr(environ[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

void		init(t_rline *rline, struct termios	*backup, int flg, char *pr)
{
	g_line = ft_strnew(0);
	(*rline).op = NULL;
	(*rline).old_c = 0;
	(*rline).c_i = 0;
	(*rline).num_line = ft_countlines("/Users/ahmcherk/.history_21sh");
	(*rline).print_line = NULL;
	(*rline).env = NULL;
	(*backup) = ft_setterm();
	g_flag = flg;
	g_pr = pr;
	(*rline).c = 0;
	(*rline).j = 0;
	rline->i = 0;
}

void		ft_execdel(t_rline *rline)
{
	char	*tmp2;

	tmp2 = NULL;
	ft_del(rline->old_c, rline->c_i, &rline->print_line);
	tmp2 = rline->print_line;
	rline->print_line = ft_strdup(g_line);
	ft_strdel(&tmp2);
}

void		ft_start(t_rline *rline, struct termios *backup, int flg, char *pr)
{
	extern char		**environ;

	init(rline, backup, flg, pr);
	if (!g_sig)
		ft_putstr(g_pr);
	tputs(tgetstr("sc", NULL), 1, ft_put);
	if (ft_en("PATH", environ) != -1)
		rline->env = ft_strsplit(environ[ft_en("PATH", environ)], ':');
}

char		*ft_readline(int flg, char *pr)
{
	t_rline			rline;
	struct termios	backup;

	ft_start(&rline, &backup, flg, pr);
	while (1)
	{
		rline.c = 0;
		read(0, &rline.c, 6);
		if ((rline.i = ft_sig(&rline)) == 1)
			return (ft_strdup("\n"));
		if (rline.c == '\n' || (rline.c == 4 && rline.print_line &&
		!rline.print_line[0]) || (rline.c == 4 && !rline.print_line))
		{
			ft_quit(&rline);
			tcsetattr(STDIN_FILENO, TCSANOW, &backup);
			return (ft_change(&rline.print_line, &rline));
		}
		if (ft_func2(&rline))
			continue ;
		rline.old_c = rline.c;
	}
	return (NULL);
}
