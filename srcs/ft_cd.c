/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:59:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/01 23:42:09 by mbarutel         ###   ########.fr       */
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

static void	swap_oldpwd(t_session *sesh)
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

static void	swap_pwd(t_session *sesh, char *cwd)
{
	char	**env;

	env = env_get_var(sesh, "PWD");
	if (env)
	{
		free(*env);
		*env = NULL;
		*env = ft_strjoin("PWD=", cwd);
	}
}

static void	cd_success(t_session *sesh)
{
	char	cwd[MAXPATHLEN];

	if (!env_get_var(sesh, "OLDPWD"))
		set_env(sesh, "OLDPWD=");
	swap_oldpwd(sesh);
	swap_pwd(sesh, getcwd(cwd, sizeof(cwd)));
}

// static bool	check_env_var(t_session *sesh, char *key)
// {
// 	if (!env_get_var(sesh, key))
// 		return (0);
// 	return (1);
// }

static char	*cd_error_check(t_session *sesh)
{
	char	**env;

	env = NULL;
	if (ft_strcmp(sesh->arg[1], "~-") == 0)
		ft_printf("cd: OLDPWD not set\n");
	// 	return (NULL);
	if (ft_strcmp(sesh->arg[1], "-") == 0)
	{
		env = env_get_var(sesh, "OLDPWD=");
		if (env)
		{
			ft_printf("%s\n", ft_strchr(*env_get_var(sesh, "OLDPWD="), '=') + 1);	
			return (ft_strdup(ft_strchr(*env_get_var(sesh, "OLDPWD="), '=') + 1));
		}
	}
	if (ft_strcmp(sesh->arg[1], "--") == 0)
		return (ft_strdup(ft_strchr(*env_get_var(sesh, "HOME="), '=') + 1));
	return (NULL);
}

int	ft_cd(t_session *sesh)
{
	char	*path;

	path = cd_error_check(sesh);
	if (path)
	{
		if (chdir(path) != 0)
		{
			ft_strdel(&path);
			return (0);
		}
		cd_success(sesh);
		ft_strdel(&path);
		return(1);
	}
	// if (!ft_strcmp(sesh->arg[1], "-")) // Currently doesnt work
	// {
	// 	path = ft_strdup(ft_strchr(*env_get_var(sesh, "OLDPWD="), '=') + 1);
	// 	ft_printf("%s\n", path);
	// }
	path = confirm_addr(NULL, ft_strdup(sesh->arg[1]), X_OK);
	if (path)
	{
		free(path);
		if (chdir(sesh->arg[1]) != 0)
			return (0);
		else
			cd_success(sesh);
	}	
	else
		return (0);
	return (1);
}
