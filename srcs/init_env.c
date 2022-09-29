/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/29 16:49:58 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

int	env_len(char **env)
{
	size_t	len;

	len = 0;
	while (*env)
	{
		if (!ft_strstr(*env, "OLDPWD="))
			len++;
		env++;
	}
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

static char	**hard_set_env(void)
{
	char	**env;
	char	cwd[MAXPATHLEN];

	env = (char **)malloc(sizeof(char *) * 4);
	if (!env)
		return (NULL);
	env[0] = ft_strjoin("PWD=", getcwd(cwd, MAXPATHLEN));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

char	**env_init(void)
{
	int		i;
	char	**env;

	if (*environ)
	{
		env = (char **)malloc(sizeof(char *) * (env_len(environ) + 1));
		if (!env)
			return (NULL);
		i = 0;
		while (*environ)
		{
			if (!ft_strstr(*environ, "OLDPWD="))
			{	
				if (ft_strstr(*environ, "SHLVL"))
					env[i] = shlvl(env[i], *environ);
				else
					env[i] = ft_strdup(*environ);
				i++;
			}
			environ++;
		}
		env[i] = NULL;
	}
	else
		env = hard_set_env();
	return (env);
}
