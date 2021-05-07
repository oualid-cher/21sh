/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_updown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 02:53:03 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/22 18:33:16 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

char	*ft_updown(long c, long old_c, int *num_line)
{
	char	*h_line;
	int		count_line;

	h_line = NULL;
	count_line = ft_countlines("/Users/ahmcherk/.history_21sh");
	if (num_line <= 0)
		return (NULL);
	if (c == UP)
	{
		if (old_c == DOWN)
			*num_line -= 1;
		h_line = ft_linereach(*num_line);
		if (*num_line > 0)
			*num_line -= 1;
	}
	else if (c == DOWN)
	{
		if (old_c == UP && *num_line < count_line)
			*num_line += 1;
		if (*num_line <= count_line)
			*num_line += 1;
		h_line = ft_linereach(*num_line);
	}
	return (h_line);
}

char	*ft_linereach(int num_line)
{
	char	*h_line;
	int		i;
	int		fd;

	h_line = NULL;
	i = 0;
	fd = open("/Users/ahmcherk/.history_21sh", O_RDONLY);
	if (num_line == 0)
		get_next_line(fd, &h_line);
	else
		while (i < num_line)
		{
			ft_strdel(&h_line);
			get_next_line(fd, &h_line);
			i++;
		}
	close(fd);
	return (h_line);
}

void	ft_historysaver(char *line)
{
	int		fd;
	char	*str;
	int		i;

	str = ft_strdup(line);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n')
			str[i] = 1;
	}
	if ((fd = open("/Users/ahmcherk/.history_21sh",
	O_CREAT | O_APPEND | O_RDWR, 0777)) < 0)
		return ;
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	ft_strdel(&str);
	close(fd);
}

char	*ft_printret(char **str, char *old_line)
{
	char	*tmp;

	tmp = NULL;
	ft_clearline();
	if ((*str) && (*str)[0])
	{
		ft_putstr(*str);
		ft_strcpy(old_line, *str);
	}
	tmp = ft_strdup(*str);
	ft_strdel(str);
	return (tmp);
}

char	*ft_printupdown(char **h_line, long c, int num_line, char *line)
{
	int			count;
	static char	old_line[5000];
	char		*str;

	count = ft_countlines("/Users/ahmcherk/.history_21sh");
	str = ft_strdup(*h_line);
	ft_strdel(h_line);
	if (c == DOWN && num_line == count + 1)
	{
		if (!old_line[0])
			ft_clearline();
		else
			ft_clearline();
		ft_bzero(old_line, 5000);
		ft_putstr(line);
		ft_strdel(&str);
		return (ft_strdup(line));
	}
	else if (c == UP || c == DOWN)
		return (ft_printret(&str, old_line));
	ft_strdel(&str);
	return (ft_strdup(line));
}
