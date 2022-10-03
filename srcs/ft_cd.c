/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:59:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/03 09:13:56 by mbarutel         ###   ########.fr       */
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
	char	*oldpwd;
	char	cwd[MAXPATHLEN];

	oldpwd = "OLDPWD=";
	if (!env_get_var(sesh, oldpwd))
		append_env(sesh, &oldpwd);
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
	char	*file;

	file = NULL;
	path = cd_error_check(sesh);
	if (path)
	{
		if (chdir(path) != 0)
		{
			ft_strdel(&path);
			return (-1);
		}
		cd_success(sesh);
		ft_strdel(&path);
		return(RESET);
	}
	file = ft_strdup(sesh->arg[1]);
	if (!confirm_addr(NULL, file, F_OK)) // Free error here, I need to update my check addr function
		return (NOEXI);
	path = confirm_addr(NULL, file, X_OK);
	ft_strdel(&file);
	if (path)
	{
		ft_strdel(&path);
		if (chdir(sesh->arg[1]) != 0)
			return (NOACC);
		else
			cd_success(sesh);
	}	
	else
		return (NOACC);
	return (RESET);
}
