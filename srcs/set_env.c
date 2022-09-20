/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:21:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/19 17:02:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char **environ;

size_t	env_len(char **env)
{
	size_t len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

static char	*shell_level(char *my_env, char *env)
{
	char	*key;
	int		lvl;
	char	*lvl_str;
	int		i;
	
	i = 0;
	lvl_str = NULL;
	while (env[i] < '0' || env[i] > '9')
		i++;
	lvl = ft_atoi(&env[i]);
	if (lvl < 1000)
		lvl++;
	else
		lvl = 0;
	lvl_str = ft_itoa(lvl);
	key = env;
	key[i] = '\0';
	my_env = ft_strjoin(key, lvl_str);
	free(lvl_str);
	return (my_env);
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
			*ptr = shell_level(*ptr, *environ);
		else
			*ptr = ft_strdup(*environ);
		environ++;
		ptr++;
	}
	*ptr = NULL;
	return (env);
}