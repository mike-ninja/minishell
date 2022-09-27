/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:44:19 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/27 11:05:05 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_key(char *key)
{
	int	i;

	i = 0;
	while (key[i] != '$')
		i++;
	i++;
	return (i);
}

static char	**dollar_swap(char **arg, char **env, char *key)
{
	int		i;
	int		key_pos;

	key_pos = ft_key(key);
	key[key_pos - 1] = '\0';
	while (env[0])
	{
		i = 0;
		while(env[0][i] != '=')
			i++;
		env[0][i] = '\0';
		if (ft_strcmp(env[0], &key[key_pos]) == 0)
		{
			free(*arg);
			*arg = ft_strjoin(key, &env[0][i + 1]);
			env[0][i] = '=';
			return (arg);
		}
		env[0][i] = '=';
		env++;
	}
	free(*arg);
	*arg = ft_strdup(key);
	return (arg);
}

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