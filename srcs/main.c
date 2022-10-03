/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/03 09:08:56 by mbarutel         ###   ########.fr       */
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
	sesh->env = cycle(sesh, line, 0);
	if (*sesh->arg)
	{
		built_ins(sesh);
		if (sesh->result)
		{
			if (sesh->result == 1)
			{	
				if (ft_strcmp(*sesh->arg, "exit") == 0)
					ft_exit(sesh, "exit\n", 1);
				if (system_call(sesh, *sesh->arg) < 0)
					return (-1);
			}
		}
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
			if (execute_input(sesh, line) == -1)
				return (FAIL);
	}
	return (RESET);
}
