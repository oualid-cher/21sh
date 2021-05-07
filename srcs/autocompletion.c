/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:18:40 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 17:03:15 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

struct dirent	*ft_cmdcmp(DIR *op, int *j, char *str)
{
	struct dirent *rd;

	while ((rd = readdir(op)) > 0)
	{
		if (!ft_strncmp(rd->d_name, str, ft_strlen(str)) &&
		rd->d_name[0] != '.')
		{
			while (*j)
			{
				ft_delchar();
				*j -= 1;
			}
			ft_strdel(&g_line);
			g_line = ft_strdup(rd->d_name);
			*j = *j + ft_strlen(g_line);
			ft_putstr(rd->d_name);
			return (rd);
		}
	}
	return (0);
}

void			ft_shelldup(char **str)
{
	ft_strdel(str);
	(*str) = ft_strdup(g_line);
}

void			ft_shellfinder(char **shell, char old_c, int *j, DIR **op)
{
	static char			*str = NULL;
	struct dirent		*rd;
	static int			i;

	if (old_c != '\t')
		i = 0;
	if (!i && old_c != '\t' && g_line && g_line[0])
		ft_shelldup(&str);
	if (!str || !str[0])
		return ;
	while (shell[i])
	{
		if (old_c != '\t')
			if (i == 0)
				*op = opendir(shell[i] + 5);
		rd = ft_cmdcmp(*op, j, str);
		if (rd && !ft_strcmp(rd->d_name, g_line))
			return ;
		i++;
		closedir(*op);
		*op = opendir(shell[i]);
	}
	ft_strdel(&str);
	i = 0;
}

void			ft_newline(int *j, struct dirent *rd)
{
	int		i;
	char	*tmp;

	i = ft_strlen(g_line);
	while (--i >= 0 && g_line[i] != '/' && g_line[i] != ' ')
	{
		ft_delchar();
		*j -= 1;
	}
	ft_putstr(rd->d_name);
	tmp = g_line;
	g_line = ft_strsub(g_line, 0, i + 1);
	ft_strdel(&tmp);
	tmp = g_line;
	g_line = ft_strjoin(g_line, rd->d_name);
	ft_strdel(&tmp);
	*j = *j + (int)ft_strlen(rd->d_name);
}

DIR				**save_dir(int option)
{
	static DIR *dirp = NULL;

	if (option == 0 && dirp)
	{
		closedir(dirp);
		dirp = NULL;
	}
	return (&dirp);
}
