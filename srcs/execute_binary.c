/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:48:55 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/02 15:08:39 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*addr_return(int status, char *slash, char *path)
{
	free(slash);
	if (status == -1)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

char	*confirm_addr(char *addr, char *file, int check)
{
	char		*slash;
	char		*path;

	slash = NULL;
	path = NULL;
	if (addr)
	{
		slash = ft_strjoin(addr, "/");
		path = ft_strjoin(slash, file);
	}
	else
		path = file;
	if ((access(path, F_OK) == 0) && (access(path, check) == 0))
		return (addr_return(0, slash, path));
	else
		return (addr_return(-1, slash, path));
}

static char	*find_binary(char *file, char **path)
{
	char	*addr;
	char	*path_copy;
	char	*ret;

	ret = NULL;
	if (!path)
		return (file);
	path_copy = ft_strdup(*path);
	addr = path_copy;
	while (path_copy)
	{
		ret = confirm_addr(ft_strsep(&path_copy, "=:"), file, X_OK);
		if (ret)
		{
			free(addr);
			return (ret);
		}
	}
	free(addr);
	return (NULL);
}

int	system_call(t_session *sesh, char *file)
{
	pid_t	id;
	char	*path;

	id = fork();
	if (id < 0)
		return (-1);
	else if (id == 0)
	{
		path = confirm_addr(NULL, file, X_OK);
		if (!path)
			path = find_binary(file, env_get_var(sesh, "PATH="));
		if (path)
		{
			if (execve(path, sesh->arg, sesh->env) == -1)
				return (-1);
		}
		else
			return (-1);
	}
	else
		wait(&id);
	return (1);
}
