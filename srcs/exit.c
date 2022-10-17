/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 11:05:20 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/17 13:36:25 by mbarutel         ###   ########.fr       */
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
		ft_printf("-minishell: %s: %s\n", *sesh->tok->arg, message);
	env_clean(sesh->env);
	arg_clean(sesh->tok->arg);
	ft_memdel((void **)&sesh->tok->tok);
	ft_memdel((void **)&sesh->tok);
	exit(status);
}
