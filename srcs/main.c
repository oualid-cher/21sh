/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmcherk <ahmcherk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:25:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/21 23:13:37 by ahmcherk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void			func(int signal)
{
	g_sig = 1;
	ft_putchar('\n');
	ft_putstr(g_pr);
	tputs(tgetstr("sc", NULL), 1, ft_put);
	ft_strdel(&g_line);
	g_line = ft_strnew(0);
}

void			alias(t_cmd *cmd)
{
	if (cmd->cmd)
		alias_checker(&cmd->cmd);
	if (cmd->pipe)
		alias(cmd->pipe);
	if (cmd->sep)
		alias(cmd->sep);
}

int				read_parse(t_core *core)
{
	ft_strdel(&g_line);
	(*core).buff = ft_readline(0, "-> 21sh ");
	if ((*core).buff == NULL)
		return (420);
	if (((*core).buff && (*core).buff[0] && (*core).buff[0] == '\n'))
	{
		ft_strdel(&(*core).buff);
		return (0);
	}
	if (((*core).cmd_line = parser(&(*core).buff)) == NULL)
	{
		ft_strdel(&(*core).buff);
		del_cmd_lst(&(*core).cmd_line);
		return (0);
	}
	return (1);
}

int				core(t_env **env)
{
	t_core		core;
	int			n;

	core.buff = NULL;
	while (1)
	{
		if (!(n = (read_parse(&core))))
			continue ;
		if (n == 420)
		{
			ft_putendl_fd("exit", 2);
			core.cmd_line = NULL;
			break ;
		}
		alias(core.cmd_line);
		if ((n = execute_cmd(core.cmd_line, env, 0)) != 666 && n != 555)
			break ;
		del_cmd_lst(&core.cmd_line);
		ft_strdel(&core.buff);
	}
	del_cmd_lst(&core.cmd_line);
	ft_strdel(&core.buff);
	return (n);
}

int				main(int ac, char **av, char **environ)
{
	t_env			*env;
	int				n;
	t_cmd			*cmd_line;

	env = NULL;
	g_sig = 0;
	g_cp = NULL;
	g_line = NULL;
	env_to_list(&env, environ);
	signal(SIGINT, func);
	n = core(&env);
	free_env(&env, del);
	return (n);
}
