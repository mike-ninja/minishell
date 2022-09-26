/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:59:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/25 14:41:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_get_var(t_session *sesh, char *key)
{
	char	**env;

	env = sesh->env;
	while (*env)
	{
		if (ft_strnequ(*env, key, ft_strlen(key)))
			return (env);
		env++;
	}
	return (NULL);
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

static void	cd_success(char *path, t_session *sesh)
{
	if (sesh->pwd)
	{
		free(sesh->pwd);
		sesh->pwd = NULL;
	}
	sesh->pwd = ft_strdup(path);
	swap_oldpwd(sesh);
	swap_pwd(sesh);
}

// int	ft_cd(t_session *sesh)
// {
// 	char	cwd[256];

// 	if (chdir(sesh->arg[1]) != 0)
// 		return (0);
// 	else 
// 	{
// 		if (getcwd(cwd, sizeof(cwd)) == NULL)
// 			return (0);
// 		else
// 			cd_success(cwd, sesh);
// 	}
// 	return (1);
// }

int	ft_cd(t_session *sesh)
{
	char	*path;

	path = confirm_addr(NULL, sesh->arg[1]);
	if (path)
	{
		if (chdir(sesh->arg[1]) != 0)
			return (0);
		else
			cd_success(path, sesh);
	}	
	else 
		return (0);
	return (1);
}