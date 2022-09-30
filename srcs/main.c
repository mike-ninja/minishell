/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/30 12:55:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*addr_return(int status, char *slash, char *path)
{
	free(slash);
	if (status == -1) // Is this necessary
	{
		free(path);
		return (NULL);
	}
	return (path);
}

char	*confirm_addr(char *addr, char *file)
{
	char		*slash;
	char		*path;
	struct stat	buff;

	slash = NULL;
	path = NULL;
	if (addr)
	{
		slash = ft_strjoin(addr, "/");
		path = ft_strjoin(slash, file);
	}
	else
		path = file;
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
	free(addr);
	return (NULL);
}

// char	**env_last_prog(char *path, t_session *sesh)
// {
// 	int		i;
// 	int		x;
// 	char	tmp;
// 	char	*tofree;

// 	i = -1;
// 	tofree = NULL;
// 	while (sesh->env[++i])
// 	{
// 		x = 0;
// 		while (sesh->env[i][x] != '=')
// 			x++;
// 		tmp = sesh->env[i][x + 1];
// 		sesh->env[i][x + 1] = '\0';
// 		if (ft_strcmp(sesh->env[i], "_=") == 0)
// 		{
// 			tofree = sesh->env[i];
// 			sesh->env[i] = ft_strjoin(sesh->env[i], path);
// 			sesh->env[i][x] = '=';
// 			free(tofree);
// 			break ;
// 		}
// 		sesh->env[i][x + 1] = tmp;
// 	}
// 	return (sesh->env);
// }

static int	system_call(t_session *sesh, char *file)
{
	pid_t	id;
	char	*path;
	char	**path_env;

	id = fork();
	if (id < 0)
		return (-1);
	else if (id == 0)
	{
		path_env = env_get_var(sesh, "PATH");
		if (!path_env)
			return (-1);
		path = confirm_addr(NULL, file);
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

static char	**hard_set_env(char	**curr_env)
{
	int		i;
	char	**env;
	char	cwd[MAXPATHLEN];

	env = (char **)malloc(sizeof(char *) * (env_len(curr_env) + 4));
	if (!env)
		return (NULL);
	i = 0;
	while (curr_env[i])
	{
		env[i] = ft_strdup(curr_env[i]);
		free(curr_env[i]);
		i++;
	}
	free(curr_env);
	env[i++] = ft_strjoin("PWD=", getcwd(cwd, MAXPATHLEN));
	env[i++] = ft_strdup("SHLVL=1");
	env[i++] = ft_strdup("_=/usr/bin/env");
	env[i] = NULL;
	return (env);
}

static char	**check_mandatory_env(t_session *sesh)
{
	if (!env_get_var(sesh, "PWD=") && !env_get_var(sesh, "SHLVL=") && !env_get_var(sesh, "_="))
		sesh->env = hard_set_env(sesh->env);
	return (sesh->env);
}

static void	session_init(t_session *sesh)
{
	sesh->tmp_env = false;
	sesh->env = env_init();
	sesh->env = check_mandatory_env(sesh);
	sesh->arg = NULL;
}

int	main(void)
{
	char		*line;
	t_session	sesh[1];

	line = NULL;
	header_print();
	session_init(sesh);
	while (1)
	{
		ft_printf(PROMPT);
		if (get_next_line(0, &line))
		{
			sesh->arg = get_args(sesh, &line);
			if (*sesh->arg)
			{
				if (built_ins(sesh) == -1)
				{	
					if (ft_strcmp(*sesh->arg, "exit") == 0)
						ft_exit(sesh, "exit\n", 1);
					if (system_call(sesh, *sesh->arg) == -1)
					{
						ft_printf("minishell: %s: command not found\n", *sesh->arg);
						return (-1);
					}
				}
			}
			sesh->env = cycle(sesh, line);
		}
	}
	return (SUCCESS);
}
