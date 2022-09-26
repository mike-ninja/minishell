/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:42:38 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/24 17:21:42 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_print(char **env)
{
	while (*env)
		ft_printf("%s\n", *env++);
	return (1);
}

int	unset_env(t_session *sesh)
{
	char	**new_array;
	char	**ptr;
	int		i;

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
	return (1);
}

int set_env(t_session *sesh)
{
	char	**new_array;
	char	**ptr;
	int		i;
	
	new_array = (char **)malloc(sizeof(char *) * env_len(sesh->env) + 2);
	if (!new_array)
		return (0);
	i = 0;
	ptr = sesh->env;
	while (*ptr)
		new_array[i++] = ft_strdup(*ptr++);
	new_array[i++] = ft_strdup(sesh->arg[1]);
	new_array[i] = NULL;
	env_clean(sesh->env);
	sesh->env = new_array;
	return (1);
}
