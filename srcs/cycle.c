/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/13 11:11:45 by mbarutel         ###   ########.fr       */
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

static void	revert_tm_en(t_session *sesh)
{
	int		i;
	int		j;
	char	c;
	char	*key;
	char	**env;

	i = -1;
	j = 0;
	c = 0;
	key = NULL;
	env = NULL;
	while (sesh->tm_en[++i])
	{
		if (ft_strchr(sesh->tm_en[i], '='))
		{
			while (sesh->tm_en[i][j] != '=')
				j++;
			c = sesh->tm_en[i][j + 1];
			sesh->tm_en[i][j + 1] = '\0';
			env = env_get_var(sesh, sesh->tm_en[i]);
			if (env)
			{
				ft_strdel(env);
				sesh->tm_en[i][j + 1] = c;
				*env = ft_strdup(sesh->tm_en[i]);
			}
		}
		else
		{
			key = ft_strjoin(sesh->tm_en[i], "=");
			env_removal(sesh, key);
			ft_strdel(&key);
		}
		ft_strdel(&sesh->tm_en[i]);
	}
}

void	cycle(t_session *sesh, bool pos)
{
	if (!pos)
		update_last_arg(sesh);
	else
	{
		if (sesh->tm_en)
			revert_tm_en(sesh);
		arg_clean(sesh->arg);
	}
}
