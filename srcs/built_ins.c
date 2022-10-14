/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:47:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/13 20:39:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(char **arg)
{
	bool	nl_flag;

	nl_flag = false;
	if (!ft_strcmp(*arg, "-n"))
	{
		nl_flag = true;
		arg++;
	}
	while (*arg)
	{
		if (**arg)
		{	
			ft_printf("%s", *arg++);
			if (*arg)
				ft_printf(" ");
		}
		else
			arg++;
	}
	if (!nl_flag)
		ft_printf("\n");
	return (RESET);
}

int	built_ins(t_session *sesh)
{
	if (ft_strcmp(*sesh->arg, "env") == 0)
		return (cmd_env(sesh));
	if (ft_strcmp(*sesh->arg, "setenv") == 0)
		return (cmd_setenv(sesh));
	if (ft_strcmp(*sesh->arg, "unsetenv") == 0 && sesh->arg[1])
		return (cmd_unsetenv(sesh));
	if (ft_strcmp(*sesh->arg, "echo") == 0 && sesh->arg[1])
		return (cmd_echo(sesh->arg + 1));
	if (ft_strcmp(*sesh->arg, "cd") == 0)
		return (cmd_cd(sesh));
	sesh->result = ERROR;
	return (sesh->result);
}
