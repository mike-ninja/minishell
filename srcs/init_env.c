/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/26 12:28:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

size_t	env_len(char **env)
{
	size_t	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

static char	*lvl_str(char *env)
{
	int		i;
	int		lvl;

	i = 0;
	while (env[i] < '0' || env[i] > '9')
		i++;
	lvl = ft_atoi(&env[i]);
	if (lvl < 1000)
		lvl++;
	else
		lvl = 0;
	return (ft_itoa(lvl));
}

static char	*shlvl(char *my_env, char *env)
{
	char	*lvl;

	lvl = lvl_str(env);
	my_env = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	return (my_env);
}

char	**env_init(void)
{
	int		i;
	char	**env;

	env = (char **)malloc(sizeof(char *) * env_len(environ));
	if (!env)
		return (NULL);
	i = -1;
	while (environ[++i])
	{
		if (!ft_strstr(environ[i], "OLDPWD"))
		{
			if (ft_strstr(environ[i], "SHLVL"))
				env[i] = shlvl(env[i], environ[i]);
			else
				env[i] = ft_strdup(environ[i]);
		}
	}
	env[i - 1] = NULL;
	return (env);
}
