/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:42:09 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/14 03:46:01 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		pipe_reader(char **str)
{
	char	*buff;
	char	*ptr;

	buff = NULL;
	while (1)
	{
		buff = ft_readline(1, "pipe> ");
		if (buff && buff[0] != '\n')
			break ;
		ft_strdel(&buff);
	}
	ptr = buff;
	buff = ft_strtrim(buff);
	free(ptr);
	ptr = (*str);
	(*str) = ft_strjoin((*str), buff);
	free(ptr);
	ft_historysaver((*str));
	ft_strdel(&buff);
}
