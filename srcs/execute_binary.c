/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:48:55 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/03 09:09:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*addr_return(int status, char *slash, char *path)
// {
// 	free(slash);
// 	if (status == -1)
// 	{
// 		free(path);
// 		return (NULL);
// 	}
// 	return (path);
// }

// char	*confirm_addr(char *addr, char *file, int check)
// {
// 	char		*slash;
// 	char		*path;

// 	slash = NULL;
// 	path = NULL;
// 	if (addr)
// 	{
// 		slash = ft_strjoin(addr, "/");
// 		path = ft_strjoin(slash, file);
// 	}
// 	else
// 		path = file;
// 	if (access(path, check) == 0)
// 		return (addr_return(0, slash, path));
// 	else
// 		return (addr_return(-1, slash, path));
// }

int	check_addr(char *addr, char *file, char **buf)
{
	char		*slash;
	char		*path;

	slash = NULL;
	path = NULL;
	*buf = NULL;
	if (addr)
	{
		slash = ft_strjoin(addr, "/");
		path = ft_strjoin(slash, file);
		ft_strdel(&slash);
	}
	else
		path = file;
	if (access(path, F_OK) != 0)
	{
		ft_strdel(&path);
		return (NOEXI);
	}
	if (access(path, X_OK) != 0)
	{	
		ft_strdel(&path);
		return (NOACC);
	}
	*buf = path;
	return (RESET);
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
		ft_strdel(&slash);
	}
	else
		path = file;
	if (access(path, check) == 0)
		return (path);
	else
	{
		ft_strdel(&path);
		return (NULL);
	}
}

static int	find_binary(char **str, char *file, char **path)
{
	char	*addr;
	char	*path_copy;

	*str = NULL;
	if (!path)
	{
		*str = file;
		return (RESET);
	}
	path_copy = ft_strdup(*path);
	addr = path_copy;
	while (path_copy)
	{
		*str = confirm_addr(ft_strsep(&path_copy, "=:"), ft_strdup(file), X_OK);
		if (*str)
		{
			free(addr);
			return (RESET);
		}
	}
	free(addr);
	if (!confirm_addr(NULL, file, X_OK))
		return (NOACC);
	return (NOEXI);
}

int	system_call(t_session *sesh, char *file)
{
	pid_t	id;
	int		acc;
	char	*path;

	id = fork();
	if (id < 0)
		return (-1);
	else if (id == 0)
	{
		acc = check_addr(NULL, file, &path);
		if (acc == RESET || acc == NOEXI)
		{
			if (!path)
				find_binary(&path, file, env_get_var(sesh, "PATH="));
			if (path)
			{
				if (execve(path, sesh->arg, sesh->env) == -1)
					return (-1);
			}
			else
			{
				ft_printf("minishell: %s: command not found\n", *sesh->arg);
				return (NOEXI);
			}
		}
		if (acc == NOACC)
		{
			ft_printf("minishell: %s: Permission denied\n", *sesh->arg);
			return (NOACC);
		}
	}
	else
		wait(&id);
	return (FAIL);
}
