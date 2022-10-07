/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:09:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/07 09:00:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_env(t_session *sesh, char **arg)
{
	char	**new_array;
	char	**ptr;
	int		i;

	i = array_len(sesh->env, END);
	new_array = (char **)malloc(sizeof(char *) * (i + 2));
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
	char	*key;
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
			ft_printf("This happens\n"); 
			return (true);
		}
		ft_strdel(&frag);
	}
	ft_strdel(&key);
	return (false);
}

int	cmd_setenv(t_session *sesh)
{
	int	i;

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
