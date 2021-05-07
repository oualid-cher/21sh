/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 21:41:54 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/14 03:22:45 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	int	i;

	i = 0;
	if (s && s[i])
	{
		while (s[i])
		{
			if (s[i] == 1)
				ft_putchar('\n');
			else
				write(1, &s[i], 1);
			i++;
		}
	}
}