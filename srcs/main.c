/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/02 15:17:07 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	session_init(t_session *sesh)
{
	sesh->tmp_env = false;
	sesh->env = env_init();
	sesh->env = mandatory_env(sesh);
	sesh->arg = NULL;
}

static int	execute_input(t_session *sesh, char *line)
{
	sesh->arg = get_args(sesh, &line);
	sesh->env = cycle(sesh, line, 0);
	if (*sesh->arg)
	{
		if (built_ins(sesh) == -1)
		{	
			if (ft_strcmp(*sesh->arg, "exit") == 0)
				ft_exit(sesh, "exit\n", 1);
			if (system_call(sesh, *sesh->arg) == ERROR)
			{
				ft_printf("minishell: %s: command not found\n", *sesh->arg);
				return (ERROR);
			}
		}
	}
	sesh->env = cycle(sesh, line, 1);
	return (SUCCESS);
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
	return (SUCCESS);
}
