/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/19 11:14:43 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char **environ;

void	env_del(char **env)
{
	char **ptr;

	ptr = env;
	while (*ptr)
		free(*ptr++);
	free(env);
	env = NULL;
}

size_t	env_len(char **env)
{
	size_t len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

static char	*shell_level(char *env)
{
	char	*res;
	char	*key;
	int		lvl;
	int		i;
	
	i = 0;
	res = NULL;
	while (env[i] < '0' || env[i] > '9')
		i++;
	lvl = ft_atoi(&env[i]);
	if (lvl < 1000)
		lvl++;
	else
		lvl = 0;
	key = env;
	key[i] = '\0';
	return(ft_strjoin(key, ft_itoa(lvl)));
	return(res);
}

char	**env_init(void)
{
	char	**env;
	char	**ptr;

	ptr = (char **)malloc(sizeof(char *) * env_len(environ) + 1);
	if (!ptr)
		return(NULL);
	env = ptr;
	while (*environ)
	{
		if (ft_strstr(*environ, "SHLVL"))
			*ptr = shell_level(*environ);
		else
			*ptr = ft_strdup(*environ);
		environ++;
		ptr++;
	}
	*ptr = NULL;
	return (env);
}