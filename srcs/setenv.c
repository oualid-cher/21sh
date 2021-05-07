/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 02:21:04 by ahmcherk          #+#    #+#             */
/*   Updated: 2020/12/04 20:41:28 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

struct termios	ft_setterm(void)
{
	struct termios old;
	struct termios new;

	tcgetattr(STDIN_FILENO, &old);
	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	tgetent(NULL, getenv("TERM"));
	return (old);
}
