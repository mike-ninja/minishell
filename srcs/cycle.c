/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/11 18:21:47 by mbarutel         ###   ########.fr       */
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
	char	*join;
	char	**env;
	char	**last_arg;

	join = NULL;
	env = env_get_var(sesh, "_=");
	last_arg = get_last_arg(sesh->arg);
	if (last_arg)
	{
		if (env)
		{
			ft_strdel(env);
			*env = ft_strjoin("_=", *last_arg);
		}
		else
		{
			join = ft_strjoin("_=", *last_arg);
			append_env(sesh, &join);
			ft_strdel(&join);
		}
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
			env_removal(sesh, tofree);
			ft_strdel(&sesh->tmp_env);
			ft_strdel(&tofree);
		}
		arg_clean(sesh->arg);
	}
}
