/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/05 13:06:30 by mbarutel         ###   ########.fr       */
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
	arg_clean(sesh->arg);
	return (new_arg);
}

int	env_print(t_session *sesh)
{
	int		i;
	char	**env;
	char	*ptr;
	char	*tofree;

	i = 1;
	ptr = NULL;
	tofree = NULL;
	if (sesh->arg[i] && ft_strchr(sesh->arg[i], '='))
	{
		set_env(sesh);
		ptr = ft_strdup(sesh->arg[i]);
		tofree = ptr;
		sesh->tmp_env = ft_strdup(ft_strsep(&ptr, "="));
		ft_strdel(&tofree);
		i++;
	}
	if (sesh->arg[i]) // update this
	{
		sesh->result = ERROR;
		sesh->arg = update_arg(sesh, &sesh->arg[i]);
		return (ERROR);
	}
	env = sesh->env;
	while (*env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return (RESET);
}

int	env_removal(t_session *sesh, char *env)
{
	char	**new_array;
	char	**ptr;
	int		i;

	// if (ft_strcmp("PWD", sesh->arg[1]))
	if (ft_strcmp("PWD", env))
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

int	unset_env(t_session *sesh) // tmp_env update
{
	int		i;
	char	*ptr;

	i = 1;
	ptr = NULL;
	while (sesh->arg[i])
	{
		ptr = ft_strjoin(sesh->arg[i], "=");
		if (ptr)
		{
			if (env_get_var(sesh, ptr))
				if (env_removal(sesh, ptr) == 0)
					return (ERROR);
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
		return (ERROR);
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