/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:48:55 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/05 13:01:13 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_address(char *file)
{
	if (access(file, F_OK) != 0)
		return (INVALID);
	if (access(file, X_OK) != 0)
		return (NOACCESS);
	return (RESET);
}

static int	find_binary(char **path, char *file, char **env, t_session *sesh)
{
	char	*addr;
	char	*slash;
	char	*tofree;
	char	*env_path;

	addr = NULL;
	slash = NULL;
	*path = addr;
	env_path = ft_strdup(*env);
	tofree = env_path;
	while (env_path)
	{
		slash = ft_strjoin("/", file);
		addr = ft_strjoin(ft_strsep(&env_path, "=:"), slash);
		ft_strdel(&slash);
		sesh->result = check_address(addr);
		if (sesh->result == RESET)
		{
			*path = ft_strdup(addr);
			ft_strdel(&addr);
			ft_strdel(&tofree);
			return (RESET);
		}
		if (sesh->result == NOACCESS)
		{
			ft_strdel(&addr);
			ft_strdel(&tofree);
			return (NOACCESS);
		}
		ft_strdel(&addr);
	}
	ft_strdel(&tofree);
	return (INVALID);
}

int	system_call(t_session *sesh, char *file) // Dont free file
{
	pid_t	id;
	char	*path;

	id = fork();
	if (id < 0)
		return (-1);
	else if (id == 0)
	{
		sesh->result = check_address(file);
		if (sesh->result == RESET)
		{
			if (execve(file, sesh->arg, sesh->env) == -1)
				return (-1);
		}
		else if (sesh->result == INVALID)
		{
			find_binary(&path, file, env_get_var(sesh, "PATH="), sesh);
			if (sesh->result == RESET)
			{
				if (execve(path, sesh->arg, sesh->env) == -1)
					return (-1);
			}
			else
			{
				sesh->result = NOCOMMAND;
				return (sesh->result);
			}
		}
	}
	else
		wait(&id);
	return (RESET);
}
