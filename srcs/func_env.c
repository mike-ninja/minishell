/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/18 17:32:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_print(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
	return (1);
}

// int	unset_env(t_env *env, t_args *args)
// {
	
// }

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
