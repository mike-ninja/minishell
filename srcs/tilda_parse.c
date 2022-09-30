/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:26:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/30 17:12:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strfind(char *stack, char *token)
{
	int	i;

	while (*stack)
	{
		i = -1;
		while (token[++i])
		{
			if (token[i] == *stack)
				return (stack);
		}
		stack++;
	}
	return (NULL);
}

static char	**tilda_env(char **arg, char **env)
{
	char	*extra;
	char	*tofree;

	if (env)
	{	
		if (!arg[0][1] || ft_strfind(arg[0], "/+-"))
		{
			tofree = arg[0];
			arg[0] = ft_strdup(ft_strchr(env[0], '=') + 1);
			extra = ft_strchr(tofree, '/');
			free(tofree);
			if (extra)
			{
				tofree = arg[0];
				arg[0] = ft_strjoin(arg[0], extra);
				free(tofree);
			}
		}
	}
	return (arg);
}

char	**tilda_parse(t_session *sesh)
{
	char	**arg;

	arg = sesh->arg;
	while (sesh->arg[0])
	{
		if (ft_strstr(sesh->arg[0], "~+"))
			sesh->arg = tilda_env(sesh->arg, env_get_var(sesh, "PWD"));
		else if (ft_strstr(sesh->arg[0], "~-"))
			sesh->arg = tilda_env(sesh->arg, env_get_var(sesh, "OLDPWD"));
		else if (ft_strstr(sesh->arg[0], "~"))
			sesh->arg = tilda_env(sesh->arg, env_get_var(sesh, "HOME"));
		sesh->arg++;
	}
	return (arg);
}
