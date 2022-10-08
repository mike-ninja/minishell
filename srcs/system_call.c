/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:48:55 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/08 19:54:09 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pointers(char **arg, char *addr, char *tofree)
{
	if (arg)
		ft_strdel(arg);
	ft_strdel(&addr);
	ft_strdel(&tofree);
}

static int	find_binary(t_session *sesh, char *env, char *addr)
{
	char	*path;
	char	*tofree;

	path = NULL;
	tofree = env;
	while (env)
	{
		path = ft_strjoin(ft_strsep(&env, "=:"), addr);
		sesh->result = check_address(path);
		if (sesh->result == RESET)
		{
			free_pointers(sesh->arg, addr, tofree);
			*sesh->arg = path;
			return (RESET);
		}
		if (sesh->result == NOACCESS)
		{
			free_pointers(&path, addr, tofree);
			return (NOACCESS);
		}
		ft_strdel(&path);
	}
	free_pointers(NULL, addr, tofree);
	return (INVALID);
}

static int	heart(t_session *sesh)
{
	char	**path;

	path = NULL;
	sesh->result = check_address(*sesh->arg);
	if (sesh->result == RESET || **sesh->arg == '.')
	{
		if (execve(*sesh->arg, sesh->arg, sesh->env) == -1)
			return (-1);
	}
	else if (sesh->result == INVALID)
	{
		path = env_get_var(sesh, "PATH=");
		if (path)
		{
			find_binary(sesh, ft_strdup(*path), ft_strjoin("/", *sesh->arg));
			if (sesh->result == RESET)
			{
				if (execve(*sesh->arg, sesh->arg, sesh->env) == -1)
					return (-1);
			}
		}
		sesh->result = NOCOMMAND;
		return (sesh->result);
	}
	return (RESET);
}

int	system_call(t_session *sesh)
{
	pid_t	id;

	id = fork();
	if (id < 0)
		return (-1);
	else if (id == 0)
	{
		if (heart(sesh))
			return (sesh->result);
	}
	else
		wait(&id);
	return (RESET);
}
