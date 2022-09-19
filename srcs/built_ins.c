/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:47:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/19 12:32:50 by mbarutel         ###   ########.fr       */
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

bool	built_ins(t_session *session)
{
	if (ft_strcmp(*session->arg, "env") == 0)
		return(env_print(session->env));
	if (ft_strcmp(*session->arg, "setenv") == 0 && session->arg[1])
		return(set_env(session));
	if (ft_strcmp(*session->arg, "unsetenv") == 0 && session->arg[1])
		return(unset_env(session));
	if (ft_strcmp(*session->arg, "echo") == 0 && session->arg[1])
		return(ft_echo(session->arg + 1));
	return(false);
}