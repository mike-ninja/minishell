/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/30 12:36:20 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **update_arg(t_session *sesh, char **arg)
{
	int		i;
	char	**new_arg;

	new_arg = (char **)malloc(sizeof(char *) * (env_len(arg) + 1));
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
	int 	i;
	char **env;
	
	i = 1;
	if (sesh->arg[i] && ft_strchr(sesh->arg[i], '='))
	{
		set_env(sesh, sesh->arg[i]);
		sesh->tmp_env = true;
		i++;
	}
	if (sesh->arg[i])
	{
		sesh->arg = update_arg(sesh, &sesh->arg[i]);
		return (-1);
	}
	env = sesh->env;
	while (*env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return (1);
}

int	unset_env(t_session *sesh)
{
	char	**new_array;
	char	**ptr;
	int		i;

	if (ft_strcmp("PWD", sesh->arg[1]))
	{
		new_array = (char **)malloc(sizeof(char *) * env_len(sesh->env));
		if (!new_array)
			return (0);
		i = 0;
		ptr = sesh->env;
		while (*ptr)
		{
			if (!ft_strnequ(*ptr, sesh->arg[1], ft_strlen(sesh->arg[1])))
				new_array[i++] = ft_strdup(*ptr);
			ptr++;
		}
		new_array[i] = NULL;
		env_clean(sesh->env);
		sesh->env = new_array;
	}
	return (1);
}

int set_env(t_session *sesh, char *env)
{
	char	**new_array;
	char	**ptr;
	int		i;
	
	if (ft_strchr(env, '='))
	{
		new_array = (char **)malloc(sizeof(char *) * env_len(sesh->env) + 2);
		if (!new_array)
			return (0);
		i = 0;
		ptr = sesh->env;
		while (*ptr)
			new_array[i++] = ft_strdup(*ptr++);
		new_array[i++] = ft_strdup(env);
		new_array[i] = NULL;
		env_clean(sesh->env);
		sesh->env = new_array;
		return (1);
	}
	return (0);
}
