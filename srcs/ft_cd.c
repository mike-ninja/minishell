/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:59:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/20 12:03:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**env_get_var(t_session *sesh, char *key)
{
	char	**env;

	env = sesh->env;
	while (!ft_strnequ(*env, key, ft_strlen(key)) && *env)
		env++;
	return (env);
}

static void swap_oldpwd(t_session *sesh)
{
	int		i;
	char	**env;
	char	**pwd;
	
	i = 0;
	pwd = env_get_var(sesh, "PWD");
	env = env_get_var(sesh, "OLDPWD");
	if (env && pwd)
	{
		free(*env);
		*env = NULL;
		while (pwd[0][i] != '=')
			i++;
		*env = ft_strjoin("OLDPWD=", &pwd[0][++i]);
	}
}

static void swap_pwd(t_session *sesh)
{
	char	**env;

	env = env_get_var(sesh, "PWD");
	if (env)
	{
		free(*env);
		*env = NULL;
		*env = ft_strjoin("PWD=", sesh->pwd);
	}
}

static void	cd_success(char *cwd, t_session *sesh)
{
	if (sesh->pwd)
	{
		free(sesh->pwd);
		sesh->pwd = NULL;
	}
	sesh->pwd = ft_strdup(cwd);
	swap_oldpwd(sesh);
	swap_pwd(sesh);
}

int	ft_cd(t_session *sesh)
{
	char	cwd[256];
	int		dir;

	dir = chdir(sesh->arg[1]);
	if (dir != 0)
	{
			ft_printf("chdir() error() %i\n", dir);
			return (0);
	}
	else 
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (0);
		else
			cd_success(cwd, sesh);
	}
	return (1);
}