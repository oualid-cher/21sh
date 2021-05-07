/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 00:49:40 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/14 04:36:28 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		tabs_skipper(char *buff)
{
	int		i;
	int		len;

	i = 0;
	while (buff[i] && buff[i] == '\t')
		ft_move_replace(&buff[i]);
}

void		replace(t_red *red)
{
	char	*ptr;

	if (red->file && red->file[0])
	{
		ptr = ft_strrchr(red->file, '\n');
		*ptr = '\0';
	}
}

void		join_herdoc_lines(t_red *red, char *buff)
{
	char	*ptr;

	ptr = red->file;
	red->file = ft_strjoin(red->file, buff);
	free(ptr);
	ptr = red->file;
	red->file = ft_strjoin(red->file, "\n");
	free(ptr);
}

void		read_herdoc(t_red *red)
{
	char	*buff;
	char	*ptr;
	char	*key;

	key = ft_strdup(red->file);
	ft_strclr(red->file);
	buff = NULL;
	while (1)
	{
		buff = ft_readline(1, "$-herdoc> ");
		if (!buff)
			break ;
		if (!ft_strcmp(buff, key))
			break ;
		if ((red->type & HERDOC) && (red->type & CLOSE_RFD))
			tabs_skipper(buff);
		join_herdoc_lines(red, buff);
		ft_strdel(&buff);
	}
	replace(red);
	free(key);
	ft_strdel(&buff);
}
