/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 10:02:05 by mbarutel         ###   ########.fr       */
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

static void	update_last_arg(t_session *sesh)
{
	char	**env;
	char	**last_arg;

	env = env_get_var(sesh, "_=");
	last_arg = get_last_arg(sesh->arg);
	if (last_arg && env)
	{
		ft_strdel(env);
		*env = ft_strjoin("_=", *last_arg);
	}
}

void	cycle(t_session *sesh, bool pos)
{
	
	char	*tofree;

	tofree = NULL;
	if (!pos)
		update_last_arg(sesh);
	else
	{
		if (sesh->tmp_env)
		{
			tofree = ft_strjoin(sesh->tmp_env, "=");
			env_removal(sesh, tofree); // sesh->tmp_env should be a parameter for this function
			ft_strdel(&sesh->tmp_env);
			ft_strdel(&tofree);
		}
		arg_clean(sesh->arg);
	}
}
