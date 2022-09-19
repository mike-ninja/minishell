/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/19 09:02:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_print(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
	return (1);
}

int	unset_env(t_session *session)
{
	char	**new_array;
	char	**ptr;
	int		i;
	
	new_array = (char **)malloc(sizeof(char *) * env_len(session->env));
	if (!new_array)
		return (0);
	i = 0;
	ptr = session->env;
	while (*ptr)
	{
		if (!ft_strnequ(*ptr, session->arg[1], ft_strlen(session->arg[1])))
			new_array[i] = ft_strdup(*ptr);
		ptr++;
		i++;
	}
	env_del(session->env);
	session->env = new_array;
	return (1);
}

int set_env(t_session *session)
{
	char	**new_array;
	char	**ptr;
	int		i;
	
	new_array = (char **)malloc(sizeof(char *) * env_len(session->env) + 1);
	if (!new_array)
		return (0);
	i = 0;
	ptr = session->env;
	while (*ptr)
		new_array[i++] = ft_strdup(*ptr++);
	new_array[i] = ft_strdup(session->arg[1]);
	env_del(session->env);
	session->env = new_array;
	return (1);
}
