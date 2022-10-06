/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:13:31 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 10:14:12 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_get_var(t_session *sesh, char *key)
{
	char	**env;

	env = sesh->env;
	while (*env)
	{
		if (ft_strnequ(*env, key, ft_strlen(key)))
			return (env);
		env++;
	}
	return (NULL);
}

int	array_len(char **array, bool pos)
{
	size_t	len;

	len = 0;
	while (*array)
	{
		if (!ft_strstr(*array, "OLDPWD="))
			len++;
		else if (pos)
			len++;
		array++;
	}
	return (len);
}
