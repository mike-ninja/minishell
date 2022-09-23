/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:44:19 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/23 15:34:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**dollar_env(t_session *sesh, char *key)
// {
// 	char	**env;
// 	char	*key;

// 	env = sesh->env;
// 	while (*env)
// 	{
// 		key 
// 		if (ft_strstr())
// 	}
// }

// void	dollar_env(t_session *sesh, char *key, size_t len)
// {
// 	char	**env_ptr;
// 	char	*key_env;
// 	char	*env;
// 	char	*tofree;

// 	env = NULL;
// 	tofree = NULL;
// 	key_env = NULL;
// 	env_ptr = sesh->env;
// 	while (*env_ptr)
// 	{
// 		ft_printf("%s %i\n", key, len);
// 		if (ft_strnequ(*env_ptr, key, len))
// 		{
// 			env = ft_strdup(*env_ptr);
// 			tofree = env;
// 			key_env = ft_strsep(&env, "=");
// 			if (ft_strnequ(key_env, key, len))
// 			{
// 				free(*env_ptr);
// 				*env_ptr = ft_strdup(env);
// 				ft_printf("key %s after transfer %s env %s\n", key_env, *env_ptr, env);
// 				free(tofree);
// 				break ;
// 			}
// 		}
// 		env_ptr++;
// 	}
// }

static char	*ft_key(char *key)
{
	char	*ptr;

	if (*key == '{')
	{
		key += 1;
		ptr = key;
		while (*ptr != '}' && *ptr)
			ptr++;
		if (*ptr == '\0')
			return (NULL);
	}
	return (key);
}

static char	**dollar_env(char **arg, char **env, char *key_frag)
{
	char	*key;
	int		i;

	i = 0;
	key_frag = ft_key(key_frag);
	if (key_frag)
	{
		key = ft_strsep(&key_frag, "}");
		while (*env)
		{
			if (ft_strstr(*env, key))
			{
				free(*arg);
				while(env[0][i] != '=')
					i++;
				env[0][i] = '\0';
				*arg = ft_strdup(&env[0][i + 1]);
				env[0][i] = '=';
				return (arg);
			}
			env++;
		}
	}
	free(*arg);
	*arg = ft_strdup("");
	return (arg);
}

char	**dollar_parse(t_session *sesh)
{
	char	*key;
	char	**arg;

	key = NULL;
	arg = sesh->arg;
	while (*sesh->arg)
	{
		key = *sesh->arg;
		if (*key == '$')
		{
			key += 1;
			sesh->arg = dollar_env(sesh->arg, sesh->env, key);
		}
		sesh->arg++;
	}
	return(arg);
}