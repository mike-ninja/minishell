/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:44:19 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/29 08:56:20 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void testing_function(char *input)
// {
// 	char **art;
// 	char **ptr;

// 	art = ft_strsplit(input, '$');
// 	ptr = art;
// 	while (*art)
// 	{
// 		free(*art);
// 		art++;
// 	}
// 	free(ptr);
// }

// static char	**dollar_swap(char **arg, char **env, char *input)
// {
// 	int			i;
// 	// char		*spec;
// 	char		*key;

// 	testing_function(input);
// 	key = ft_strsep(&input, "$");
	
// 	ft_printf("key   [%s]\n", key);
// 	ft_printf("input [%s]\n", input);
// 	// spec = check_spec_char(input)
// 	while (env[0])
// 	{
// 		i = 0;
// 		while(env[0][i] != '=')
// 			i++;
// 		env[0][i] = '\0';
// 		if (ft_strcmp(env[0], input) == 0)
// 		{
// 			free(*arg);
// 			*arg = ft_strjoin(key, &env[0][i + 1]);
// 			env[0][i] = '=';
// 			free(key);
// 			return (arg);
// 		}
// 		env[0][i] = '=';
// 		env++;
// 	}
// 	free(*arg);
// 	*arg = ft_strdup(key);
// 	free(key);
// 	return (arg);
// }
static char	**dollar_swap(char **arg, char **env, char *input)
{
	int			i;
	char		**keys;
	char		**ptr;
	char		*tmp;

	keys = ft_strsplit(input, '$');
	free(*arg);
	*arg = NULL;
	while (*keys)
	{
		tmp = *arg;
		ptr = env;
		while (ptr[0])
		{
			i = 0;
			while(ptr[0][i] != '=')
				i++;
			ptr[0][i] = '\0';
			if (ft_strcmp(ptr[0], keys[0]) == 0)
			{
				if (!*arg)
					*arg = ft_strdup(&ptr[0][i + 1]);
				else
				{
					*arg = ft_strjoin(*arg, &ptr[0][i + 1]);
					free(tmp);
				}
				ptr[0][i] = '=';
				break ;
			}
			ptr[0][i] = '=';
			ptr++;
		}
		if (!ptr[0])
		{
			if (!*arg)
				*arg = ft_strdup(*keys);
			else
			{
				*arg = ft_strjoin(*arg, *keys);
				free(tmp);
			}
		}
		keys++;
	}
	return (arg);
}

/*
while (env[0])
{
	i = 0;
	j = -1;
	while(env[0][i] != '=')
		i++;
	env[0][i] = '\0';
	while (keys[++j])
	{
		if (ft_strcmp(env[0], keys[j]) == 0)
		{
			*arg = ft_strjoin(key, &env[0][i + 1]);
			env[0][i] = '=';
			free(key);
			return (arg);
		}	
	}
	env[0][i] = '=';
	env++;
}
*/

	
char	**dollar_parse(t_session *sesh)
{
	char	**arg;

	arg = sesh->arg;
	while (*sesh->arg)
	{
		if (ft_strchr(*sesh->arg, '$') && (ft_strlen(*sesh->arg) > 1))
			sesh->arg = dollar_swap(sesh->arg, sesh->env, *sesh->arg);
		sesh->arg++;
	}
	return(arg);
}
// char	**dollar_parse(t_session *sesh)
// {
// 	char	**arg;

// 	arg = sesh->arg;
// 	while (*sesh->arg)
// 	{
// 		if (ft_strchr(*sesh->arg, '$') && (ft_strlen(*sesh->arg) > 1))
// 			sesh->arg = dollar_swap(sesh->arg, sesh->env, ft_strdup(*sesh->arg));
// 		sesh->arg++;
// 	}
// 	return(arg);
// }