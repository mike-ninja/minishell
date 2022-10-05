/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:26:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/05 09:21:20 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_tilda(char *arg)
{
	while (*arg)
	{
		if (*arg != '+' && *arg != '~' && *arg != '-')
			break ;
		arg++;
	}
	if (*arg == '/' || !*arg)
		return (true);
	return (false);
}

static char	*fetch_val(char *arg, char **env)
{
	char	*ptr;
	char	*extra;

	ptr = NULL;
	extra = NULL;
	if (env && validate_tilda(arg))
	{
		extra = ft_strchr(arg, '/');
		if (extra)
			ptr = ft_strjoin(ft_strchr(*env, '=') + 1, extra);
		else
			ptr = ft_strdup(ft_strchr(*env, '=') + 1);
		ft_strdel(&arg);
		arg = ptr;
	}
	return (arg);
}

void	tilda_parse(t_session *sesh)
{
	int	i;

	i = -1;
	while (sesh->arg[++i])
	{
		if (ft_strstr(sesh->arg[i], "~+"))
			sesh->arg[i] = fetch_val(sesh->arg[i],
					env_get_var(sesh, "PWD="));
		else if (ft_strstr(sesh->arg[i], "~-"))
			sesh->arg[i] = fetch_val(sesh->arg[i],
					env_get_var(sesh, "OLDPWD="));
		else if (ft_strstr(sesh->arg[i], "~"))
			sesh->arg[i] = fetch_val(sesh->arg[i],
					env_get_var(sesh, "HOME="));
	}
}
