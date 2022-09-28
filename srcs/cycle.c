/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:10:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/28 12:22:28 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_last_arg(char	**arg)
{
	while (*arg)
		arg++;
	return(arg - 1);
}

// char    **last_arg_update(t_session *sesh)
// {
// 	char	**env_var;
// 	char	**last_arg;

// 	last_arg = get_last_arg(sesh->arg);
// 	ft_printf("Before\n");
// 	env_print(sesh->env);
// 	ft_printf("\n");
// 	if (ft_strcmp(*last_arg, "$_"))
// 	{
// 		env_var = get_last_env(sesh->env);
// 		free(*env_var);
// 		*last_arg = ft_strjoin("_=", *last_arg);
// 	}
// 	ft_printf("After\n");
// 	env_print(sesh->env);
// 	ft_printf("\n");
// 	return (sesh->env);
// }

char	**cycle(t_session *sesh, char *line)
{
	char	**env;

	env = env_get_var(sesh, "_=");
	free(*env);
	*env = ft_strjoin("_=", *get_last_arg(sesh->arg));
	arg_clean(sesh->arg, line);
	return (sesh->env);
}
