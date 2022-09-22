/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/22 15:16:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	session_init(t_session *sesh)
{
	sesh->env = NULL;
	sesh->arg = NULL;
	sesh->pwd = NULL;
}

static char	*addr_return(int status, char *slash, char *path)
{
	free(slash);
	if (status == -1)
	{
		free(path);
		return (NULL);
	}
	return(path);
}

static char	*confirm_addr(char *addr, char *file)
{
	char	*slash;
	char	*path;
	struct stat	buff;

	slash = ft_strjoin(addr, "/");
	path = ft_strjoin(slash, file);
	if (stat(path, &buff) == 0)
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
	path_copy = ft_strdup(*path);
	addr = path_copy;
	while (path_copy)
	{
		ret = confirm_addr(ft_strsep(&path_copy, "=:"), file);
		if (ret)
		{
			free(addr);
			return (ret);
		}
	}
	free(addr); // It never reaches here for some reason
	return (NULL);
}

static int	system_call(t_session *sesh, char *file)
{
	pid_t	id;
	char	*path;

	id = fork();
	if (id < 0)
		return (-1);
	else if (id == 0)
	{
		path = find_binary(file, env_get_var(sesh, "PATH"));
		if (path)
		{
			if (execve(path, sesh->arg, sesh->env) == -1) // Result is negative if failure
				return (-1);
		}
		else
			return (-1);
	}
	else
		wait(&id);
	return (1);
}

int	main(void)
{
	char		*line;
	t_session	sesh[1];

	line = NULL;
	header_print();
	session_init(sesh);
	sesh->env = env_init();
	while (1)
	{
		ft_printf(PROMPT);
		if (get_next_line(0, &line))
		{
			sesh->arg = get_args(&line);
			if (!built_ins(sesh))
			{	
				if (ft_strcmp(*sesh->arg, "exit") == 0)
					return(ft_exit(sesh, "exit\n"));
				if (system_call(sesh, *sesh->arg) == -1)
					return(ft_exit(sesh, strerror(errno)));
			}
			arg_clean(sesh->arg, line);
		}
	}
	return(SUCCESS);
}
