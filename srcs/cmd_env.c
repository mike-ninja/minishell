/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 12:23:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**update_arg(t_session *sesh, char **arg)
{
	int		i;
	char	**new_arg;

	new_arg = (char **)malloc(sizeof(char *) * (array_len(arg, END) + 1));
	if (!new_arg)
		ft_exit_no_mem(1);
	i = 0;
	while (arg[i])
	{
		new_arg[i] = ft_strdup(arg[i]);
		i++;
	}
	new_arg[i] = NULL;
	arg_clean(sesh->tokens->arg);
	return (new_arg);
}

static int	tmp_env_qty(char **arg)
{
	int	len;

	len = 0;
	while (arg[len] && ft_strchr(arg[len], '=') && *arg[len] != '=')
		len++;
	return (len);
}

static void	key_str(t_session *sesh, char *arg, int *j)
{
	char	*sep;
	char	*tofree;

	sep = NULL;
	tofree = NULL;
	sep = ft_strdup(arg);
	append_env(sesh, &arg);
	tofree = sep;
	sesh->tm_en[j[0]++] = ft_strdup(ft_strsep(&sep, "="));
	ft_strdel(&tofree);
}

static int	set_tmp_env(t_session *sesh, int i)
{
	int		j;
	char	*replaced;

	j = 0;
	sesh->tm_en = (char **)malloc(sizeof(char *)
			* (tmp_env_qty(&sesh->tokens->arg[i]) + 1));
	if (!sesh->tm_en)
		ft_exit_no_mem(1);
	while (sesh->tokens->arg[i] && ft_strchr(sesh->tokens->arg[i], '=') && *sesh->tokens->arg[i] != '=')
	{
		if (!replace_value(sesh, ft_strdup(sesh->tokens->arg[i]), &replaced))
			key_str(sesh, sesh->tokens->arg[i], &j);
		else
			sesh->tm_en[j++] = replaced;
		i++;
	}
	sesh->tm_en[j] = NULL;
	return (i);
}

int	cmd_env(t_session *sesh)
{
	int		i;
	char	**env;

	i = 1;
	if (sesh->tokens->arg[i] && ft_strchr(sesh->tokens->arg[i], '='))
		i = set_tmp_env(sesh, i);
	if (sesh->tokens->arg[i])
	{
		sesh->result = ERROR;
		sesh->tokens->arg = update_arg(sesh, &sesh->tokens->arg[i]);
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
