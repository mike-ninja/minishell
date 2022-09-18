/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:47:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/17 11:08:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo(t_args *args)
{
	size_t	index;
	
	index = 1;
	while (index < args->len)
	{
		ft_printf("%s\n", args->array[index]);
		index++;
	}
	return (1);
}

bool	built_ins(t_args *args, t_env *env)
{
	if (ft_strcmp(*args->array, "env") == 0)
		return(env_print(env));
	if (ft_strcmp(*args->array, "setenv") == 0 && args->array[1])
		return(set_env(env, args->array));
	if (ft_strcmp(*args->array, "unsetenv") == 0 && args->array[1])
		return(unset_env(env, args->array));
	if (ft_strcmp(*args->array, "echo") == 0 && args->array[1])
		return(ft_echo(args));
	return(false);
}