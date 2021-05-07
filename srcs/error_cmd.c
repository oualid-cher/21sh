/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 04:40:41 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/14 04:41:15 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				error_cmd(char *cmd, char *str)
{
	if (!(ft_strncmp(&cmd[0], "./", ft_strlen("./"))))
	{
		if (access(cmd, F_OK) != 0)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": no such file or directory.\n", 2);
			return (0);
		}
	}
	else if (!str)
	{
		ft_putstr_fd("\aSHELL: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		return (0);
	}
	return (1);
}
