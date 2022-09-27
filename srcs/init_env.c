/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/27 14:50:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

int	env_len(char **env)
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
	int		len;

	len = env_len(environ);
	// env = (char **)malloc(sizeof(char *) * env_len(environ));
	// if (ft_strstr(environ[len - 1], "OLDPWD"))
	// 	len--;
	// ft_printf("len %i\n", len);
	env = (char **)malloc(sizeof(char *) * len);
	if (!env)
		return (NULL);
	i = -1;
	while (environ[++i])
	{
		ft_printf("%i %s\n", i, environ[i]);
		if (ft_strstr(environ[i], "SHLVL"))
			env[i] = shlvl(env[i], environ[i]);
		else
			env[i] = ft_strdup(environ[i]);
	}
	env[i] = NULL;
	return (env);
}
