/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:16:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/17 11:58:27 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_failed_arg(char *str)
{
	while (*str)
	{
		if (*str == '\n')
		{
			write(1, "\\", 1);
			write(1, "n", 1);
		}
		else
			write(1, str, 1);
		str++;
	}
}

void	error_message(t_session *sesh)
{
	ft_printf("minishell: ");
	print_failed_arg(sesh->tok->arg[0]);
	write(1, ": ", 2);
	if (sesh->result == INVALID)
	{
		if (sesh->tok->arg[1])
			print_failed_arg(sesh->tok->arg[1]);
		ft_printf(": No such file or directory\n");
	}
	if (sesh->result == NOACCESS)
	{
		if (sesh->tok->arg[1])
			print_failed_arg(sesh->tok->arg[1]);
		ft_printf(": Permission denied\n");
	}
	if (sesh->result == NOCOMMAND)
		ft_printf("command not found\n");
	if (sesh->result == TOOMANYARGS)
		ft_printf("too many arguments\n");
	sesh->result = ERROR;
}
