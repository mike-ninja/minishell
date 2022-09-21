/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:47:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/21 10:33:31 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo(char **arg)
{
	while (*arg)
		ft_printf("%s ", *arg++);
	ft_printf("\n");
	return (1);
}

bool	built_ins(t_session *sesh)
{
	if (ft_strcmp(*sesh->arg, "env") == 0)
		return(env_print(sesh->env));
	if (ft_strcmp(*sesh->arg, "setenv") == 0 && sesh->arg[1])
		return(set_env(sesh));
	if (ft_strcmp(*sesh->arg, "unsetenv") == 0 && sesh->arg[1])
		return(unset_env(sesh));
	if (ft_strcmp(*sesh->arg, "echo") == 0 && sesh->arg[1])
		return(ft_echo(sesh->arg + 1));
	if (ft_strcmp(*sesh->arg, "cd") == 0 && sesh->arg[1])
		return(ft_cd(sesh));
	return(false);
}