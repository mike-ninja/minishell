/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/04 11:21:37 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**update_arg(t_session *sesh, char **arg)
{
	int		i;
	char	**new_arg;

	new_arg = (char **)malloc(sizeof(char *) * (array_len(arg) + 1));
	if (!new_arg)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		new_arg[i] = ft_strdup(arg[i]);
		i++;
	}
	new_arg[i] = NULL;
	sesh->tmp_env = false;
	arg_clean(sesh->arg, NULL);
	return (new_arg);
}

int	env_print(t_session *sesh)
{
	int		i;
	char	**env;

	i = 1;
	if (sesh->arg[i] && ft_strchr(sesh->arg[i], '='))
	{
		set_env(sesh);
		sesh->tmp_env = true;
		i++;
	}
	env = sesh->env;
	while (*env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	if (sesh->arg[i])
	{
		sesh->arg = update_arg(sesh, &sesh->arg[i]);
		return (FAIL);
	}
	return (RESET);
}

static int	env_removal(t_session *sesh, char *env)
{
	char	**new_array;
	char	**ptr;
	int		i;

	if (ft_strcmp("PWD", sesh->arg[1]))
	{
		new_array = (char **)malloc(sizeof(char *) * array_len(sesh->env));
		if (!new_array)
			return (0);
		i = 0;
		ptr = sesh->env;
		while (*ptr)
		{
			if (!ft_strnequ(*ptr, env, ft_strlen(env)))
				new_array[i++] = ft_strdup(*ptr);
			ptr++;
		}
		new_array[i] = NULL;
		env_clean(sesh->env);
		sesh->env = new_array;
	}
	return (1);
}

int	unset_env(t_session *sesh)
{
	int		i;
	char	*ptr;

	i = 1;
	ptr = NULL;
	while (sesh->arg[i])
	{
		if (sesh->tmp_env)
		{
			if (ft_strchr(sesh->arg[i], '='))
				ptr = ft_strdup(sesh->arg[i]);
		}
		else
			ptr = ft_strjoin(sesh->arg[i], "=");
		if (ptr)
		{
			if (env_get_var(sesh, ptr))
				if (env_removal(sesh, ptr) == 0)
					return (FAIL);
			ft_strdel(&ptr);
		}
		i++;
	}
	return (RESET);
}

int	append_env(t_session *sesh, char **arg)
{
	char	**new_array;
	char	**ptr;
	int		i;

	new_array = (char **)malloc(sizeof(char *) * (array_len(sesh->env) + 2));
	if (!new_array)
		return (FAIL);
	i = -1;
	ptr = sesh->env;
	while (ptr[++i])
		new_array[i] = ft_strdup(ptr[i]);
	new_array[i++] = ft_strdup(arg[0]);
	new_array[i] = NULL;
	env_clean(sesh->env);
	sesh->env = new_array;
	return (RESET);
}

static bool	replace_value(t_session *sesh, char *arg)
{
	int		i;
	char 	*key;
	char	*frag;

	i = -1;
	frag = NULL;
	key = ft_strsep(&arg, "=");
	while (sesh->env[++i])
	{
		frag = ft_strjoin(key, "=");
		if (!ft_strncmp(sesh->env[i], frag, ft_strlen(frag)))
		{
			ft_strdel(&sesh->env[i]);
			sesh->env[i] = ft_strjoin(frag, arg);
			ft_strdel(&frag);
			ft_strdel(&key);
			return (true);
		}
		ft_strdel(&frag);
	}
	ft_strdel(&key);
	return (false);
}

int	set_env(t_session *sesh)
{
	int i;

	i = 1;
	while (sesh->arg[i])
	{
		if (ft_strchr(sesh->arg[i], '='))
		{
			if (!replace_value(sesh, ft_strdup(sesh->arg[i])))
				append_env(sesh, &sesh->arg[i]);
		}
		i++;
	}
	return (RESET);
}