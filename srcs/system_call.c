/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:48:55 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 14:51:31 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pointers(char *path, char *file, char *tofree)
{
	if (path)
		ft_strdel(&path);
	ft_strdel(&file);
	ft_strdel(&tofree);
}

static int	find_binary(char **path, char *file, char **env, t_session *sesh)
{
	char	*tofree;
	char	*env_path;

	env_path = ft_strdup(*env);
	tofree = env_path;
	while (env_path)
	{
		*path = ft_strjoin(ft_strsep(&env_path, "=:"), file);
		sesh->result = check_address(*path);
		if (sesh->result == RESET)
		{
			free_pointers(NULL, file, tofree);
			return (RESET);
		}
		if (sesh->result == NOACCESS)
		{
			free_pointers(*path, file, tofree);
			return (NOACCESS);
		}
		ft_strdel(path);
	}
	free_pointers(NULL, file, tofree);
	return (INVALID);
}

static int	heart(t_session *sesh, char *file)
{
	char	*path;

	path = NULL;
	sesh->result = check_address(file);
	if (sesh->result == RESET)
	{
		if (execve(file, sesh->arg, sesh->env) == -1)
			return (-1);
	}
	else if (sesh->result == INVALID)
	{
		find_binary(&path, ft_strjoin("/", file),
			env_get_var(sesh, "PATH="), sesh);
		if (sesh->result == RESET)
		{
			if (execve(path, sesh->arg, sesh->env) == -1)
				return (-1);
		}
		sesh->result = NOCOMMAND;
		return (sesh->result);
	}
	return (RESET);
}

int	system_call(t_session *sesh, char *file)
{
	pid_t	id;

	id = fork();
	if (id < 0)
		return (-1);
	else if (id == 0)
	{
		if (heart(sesh, file))
			return (sesh->result);
	}
	else
		wait(&id);
	return (RESET);
}
