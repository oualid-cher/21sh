/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:59:57 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 18:19:20 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void			ft_setpath(char **str, char **path)
{
	char	**tab_line;
	char	*tmp_line;
	char	tmp_c;

	tab_line = ft_strsplit(g_line, ' ');
	tmp_line = tab_line[ft_dblstrlen(tab_line) - 1];
	tmp_c = tmp_line[ft_strlen(tab_line[ft_dblstrlen(tab_line) - 1]) - 1];
	if (tmp_c != '/')
		*path = ft_strsub(tmp_line, 0, ft_strlen(tmp_line) - ft_strlen(*str));
	else
	{
		*path = ft_strdup(tmp_line);
		ft_strdel(str);
		(*str) = ft_strdup("");
	}
	ft_strdbldel(&tab_line);
}

void			initialiser(char ***tab_line, char **tmp_line, DIR **op)
{
	(*tab_line) = ft_strsplit(g_line, ' ');
	(*tmp_line) = (*tab_line)[ft_dblstrlen((*tab_line)) - 1];
	(*op) = NULL;
}

DIR				*ft_pathfinder(char **str)
{
	char	*path;
	DIR		*op;
	char	**tab_line;
	char	*tmp_line;

	initialiser(&tab_line, &tmp_line, &op);
	if (ft_strchr(tmp_line, '/') &&
	(*str = ft_strdup(ft_strrchr(tmp_line, '/') + 1)))
		ft_setpath(str, &path);
	else
	{
		(*str) = ft_strdup(tmp_line);
		path = ft_strdup(".");
	}
	if (!access(path, X_OK | F_OK))
		op = opendir(path);
	else
	{
		ft_strdel(&path);
		ft_strdbldel(&tab_line);
		return (NULL);
	}
	ft_strdbldel(&tab_line);
	ft_strdel(&path);
	return (op);
}
