/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 10:53:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_clean(char **arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		ft_strdel(&arg[i]);
	ft_memdel((void **)arg);
}

void	env_clean(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_strdel(&env[i]);
	ft_memdel((void **)env);
}

void	ft_exit(t_session *sesh, char *message, int status)
{
	if (message)
		ft_printf("-minishell: %s: %s\n", *sesh->arg, message);
	env_clean(sesh->env);
	arg_clean(sesh->arg);
	exit(status);
}
