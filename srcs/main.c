/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/04 11:25:03 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	session_init(t_session *sesh)
{
	sesh->tmp_env = false;
	sesh->env = env_init();
	sesh->env = mandatory_env(sesh);
	sesh->arg = NULL;
	sesh->result = RESET;
}

static int	execute_input(t_session *sesh, char *line)
{
	sesh->arg = get_args(sesh, &line);
	if (*sesh->arg)
	{
		built_ins(sesh);
		sesh->env = cycle(sesh, line, 0); // This needs to change to a specific function that changes the value of _=
		if (sesh->result == 1)
		{
			if (ft_strcmp(*sesh->arg, "exit") == 0)
				ft_exit(sesh, "exit\n", RESET);
			if (system_call(sesh, *sesh->arg) == ERROR)
				return (ERROR);
			if (sesh->result < 0)
			{
				error_message(sesh);
				return (ERROR);
			}
		}
		else if (sesh->result != RESET)
			error_message(sesh);
	}
	sesh->env = cycle(sesh, line, 1);
	return (RESET);
}

int	main(void)
{
	char		*line;
	t_session	sesh[1];

	line = NULL;
	header_print();
	session_init(sesh);
	while (1)
	{
		ft_printf(PROMPT);
		if (get_next_line(0, &line))
			if (execute_input(sesh, line) == ERROR)
				return (ERROR);
	}
	return (RESET);
}
