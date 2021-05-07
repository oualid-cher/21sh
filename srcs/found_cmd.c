/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 23:28:50 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/14 04:43:08 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

t_env			*search_env(t_env *env, char *name)
{
	t_env		*ptr;
	int			i;

	i = 0;
	ptr = env;
	if (ptr)
	{
		while (ptr && ptr->name)
		{
			if (ft_strcmp(ptr->name, name) == 0)
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (NULL);
}

int				check(t_env **lst, char *str)
{
	if (ft_strchr(str, '/'))
		if (access(str, F_OK) == 0)
			return (1);
	if (!(*lst = search_env(*lst, "PATH")))
	{
		ft_putstr_fd("\aSHELL: command not found: ", 2);
		ft_putendl_fd(str, 2);
		return (0);
	}
	return (0);
}

void			join_path(t_ff *ff, char *cmd)
{
	(*ff).tmp = (*ff).paths[(*ff).i];
	(*ff).paths[(*ff).i] = ft_strjoin((*ff).paths[(*ff).i], "/");
	free((*ff).tmp);
	(*ff).tmp = (*ff).paths[(*ff).i];
	(*ff).paths[(*ff).i] = ft_strjoin((*ff).paths[(*ff).i], cmd);
	free((*ff).tmp);
}

void			search_in_path(t_ff *ff, char *cmd)
{
	if ((*ff).paths)
	{
		while ((*ff).paths[++(*ff).i])
		{
			join_path(ff, cmd);
			if (access((*ff).paths[(*ff).i], F_OK) == 0)
				break ;
		}
	}
}

char			**found_func(t_env *lst, char *cmd, char **str)
{
	t_ff ff;

	ff.i = -1;
	if (check(&lst, str[0]) == 1)
		return (str);
	if (lst == NULL)
	{
		delkill(str);
		return (NULL);
	}
	ff.paths = ft_strsplit(lst->value, ':');
	search_in_path(&ff, cmd);
	if (!(error_cmd(str[0], ff.paths[ff.i])))
	{
		delkill(ff.paths);
		delkill(str);
		return (NULL);
	}
	ft_strdel(&str[0]);
	str[0] = ft_strdup(ff.paths[ff.i]);
	delkill(ff.paths);
	return (str);
}
