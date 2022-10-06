/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:16:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/06 12:05:00 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(t_session *sesh)
{
	ft_printf("minishell: %s:", sesh->arg[0]);
	if (sesh->result == INVALID)
	{
		if (sesh->arg[1])
			ft_printf(" %s:", sesh->arg[1]);
		ft_printf(" No such file or directory\n");
	}
	if (sesh->result == NOACCESS)
	{
		if (sesh->arg[1])
			ft_printf(" %s:", sesh->arg[1]);
		ft_printf(" Permission denied\n");
	}
	if (sesh->result == NOCOMMAND)
		ft_printf(" command not found\n");
	if (sesh->result == TOOMANYARGS)
		ft_printf(" too many arguments\n");
	sesh->result = ERROR;
}
