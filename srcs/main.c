/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/29 15:32:11 by mbarutel         ###   ########.fr       */
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
			path = find_binary(file, env_get_var(sesh, "PATH"));
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

static void	session_init(t_session *sesh)
{
	sesh->env = env_init();
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
						return (ft_exit(sesh, "exit\n"));
					if (system_call(sesh, *sesh->arg) == -1)
						return (ft_exit(sesh, strerror(errno)));
				}
			}
			// ft_printf("Before breaking\n");
			sesh->env = cycle(sesh, line);
			// ft_printf("After breaking\n");
		}
	}
	return (SUCCESS);
}
