/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:23:16 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/22 04:57:15 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			open_cots_checker(char **str, int balance)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		balance = balance_checker(str, balance, &i);
		cut_quotas(str, &i, balance);
		i++;
	}
	return (balance);
}

void		joint(char **str, char *buff)
{
	char	*ptr;

	ptr = (*str);
	(*str) = ft_strjoin((*str), buff);
	ft_strdel(&ptr);
	ptr = ft_strrchr((*str), '\n');
	if (*ptr == (*str)[ft_strlen((*str))])
		*ptr = '\0';
}

void		join_lines(char **str, char *buff)
{
	char	*ptr;

	ptr = (*str);
	(*str) = ft_strjoin((*str), buff);
	ft_strdel(&ptr);
	ptr = (*str);
	(*str) = ft_strjoin((*str), "\n");
	ft_strdel(&ptr);
}

int			check_ctrl_d(int balance, char **str)
{
	if (balance != 0 && (balance = open_cots_checker(str, balance)) != 0)
	{
		ft_putstr_fd("21sh : unexpected EOF while looking for matching", 2);
		if (balance == 1)
			ft_putendl_fd(" `\"`", 2);
		else
			ft_putendl_fd(" `\'`", 2);
		return (0);
	}
	return (1);
}

int			open_cots(char **str, int balance)
{
	char	*buff;
	int		indice;

	indice = 0;
	while (1)
	{
		buff = ft_readline(1, pr_writer(balance));
		if (!buff)
			break ;
		if ((balance = open_cots_checker(&buff, balance)) == 0)
		{
			joint(str, buff);
			break ;
		}
		else
			join_lines(str, buff);
		ft_strdel(&buff);
	}
	if (!check_ctrl_d(balance, str))
		return (0);
	ft_historysaver((*str));
	ft_strdel(&buff);
	return (1);
}
