/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 20:47:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/16 13:30:52 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	built_ins(char **input, t_env *env)
{
	if (ft_strcmp(input[0], "env") == 0)
		return(env_print(env));
	if (ft_strcmp(input[0], "setenv") == 0)
		return(set_env(env, input));
	if (ft_strcmp(input[0], "unsetenv") == 0)
		return(unset_env(env, input));
	return(false);
}