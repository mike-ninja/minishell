/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/02 13:12:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_last_arg(char	**arg)
{
	if (!*arg)
		return (NULL);
	while (*arg)
		arg++;
	return (arg - 1);
}

char	**cycle(t_session *sesh, char *line)
{
	char	**env;
	char	**last_arg;

	last_arg = NULL;
	if (sesh->tmp_env)
	{
		unset_env(sesh);
		sesh->tmp_env = false;
	}
	env = env_get_var(sesh, "_=");
	last_arg = get_last_arg(sesh->arg);
	if (last_arg && env)
	{
		free(*env);
		*env = ft_strjoin("_=", *last_arg);
	}
	arg_clean(sesh->arg, line);
	return (sesh->env);
}
