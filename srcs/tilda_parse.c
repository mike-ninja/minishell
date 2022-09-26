/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:26:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/26 11:27:18 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**tilda_env(char **arg, char **env)
{
	char	*extra;
	char	*tofree;

	if (!arg[0][1] || arg[0][1] == '/')
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
	return (arg);
}

char	**tilda_parse(t_session *sesh)
{
	char	**arg;

	arg = sesh->arg;
	while (sesh->arg[0])
	{
		if (sesh->arg[0][0] == '~')
			sesh->arg = tilda_env(sesh->arg, env_get_var(sesh, "HOME"));
		sesh->arg++;
	}
	return(arg);
}