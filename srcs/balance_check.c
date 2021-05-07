/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 04:54:45 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/22 04:57:40 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			balance_checker(char **str, int balance, int *i)
{
	if ((*str)[(*i)] == '"' && balance != 2)
		balance = (balance > 0) ? 0 : 1;
	if ((*str)[(*i)] == '\'' && balance != 1)
		balance = (balance > 0) ? 0 : 2;
	if (((*str)[(*i)] == ' ') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 5;
	if (((*str)[(*i)] == '|') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 1;
	if (((*str)[(*i)] == ';') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 2;
	if (((*str)[(*i)] == '>') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 3;
	if (((*str)[(*i)] == '<') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 4;
	if (((*str)[(*i)] == '&') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 6;
	return (balance);
}
