/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 12:01:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**update_arg(t_session *sesh, char **arg)
{
	int		i;
	char	**new_arg;

	new_arg = (char **)malloc(sizeof(char *) * (array_len(arg, END) + 1));
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

static int	set_tmp_env(t_session *sesh, int i)
{
	char	*sep;
	char	*tofree;

	sep = NULL;
	cmd_setenv(sesh);
	sep = ft_strdup(sesh->arg[i]);
	tofree = sep;
	sesh->tmp_env = ft_strdup(ft_strsep(&sep, "="));
	ft_strdel(&tofree);
	return (++i);
}

int	cmd_env(t_session *sesh)
{
	int		i;
	char	**env;

	i = 1;
	if (sesh->arg[i] && ft_strchr(sesh->arg[i], '='))
		i = set_tmp_env(sesh, i);
	if (sesh->arg[i])
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
