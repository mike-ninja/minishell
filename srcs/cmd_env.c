/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 10:11:02 by mbarutel         ###   ########.fr       */
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

int	cmd_env(t_session *sesh)
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
		cmd_setenv(sesh);
		ptr = ft_strdup(sesh->arg[i]);
		tofree = ptr;
		sesh->tmp_env = ft_strdup(ft_strsep(&ptr, "="));
		ft_strdel(&tofree);
		i++;
	}
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
