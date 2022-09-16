/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/16 09:06:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	garbage_collect(char **av)
{
	int	i;
	char 	*ptr;

	i = 0;
	if (av[i])
	{
		while (av[i])
		{
			ptr = NULL;
			ptr = av[i];
			i++;
			free(ptr);
		}
		free(av);
	}
	av = NULL;
}

int	main(void)
{
	pid_t	id;
	char	*line;
	char	**input;
	t_env	*env;

	line = NULL;
	input = NULL;
	env = NULL;
	env = env_init(env);
	while (1)
	{
		ft_printf("$>: ");	
		if (get_next_line(0, &line))
		{
			input = ft_strsplit(line, ' ');
			if (!built_ins(input, env))
			{	
				id = fork();
				if (id < 0)
				{
					ft_printf("Fork failed\n");
					exit(FAILURE);
				}
				else if (id == 0)
				{
					int ret;

					ret = 0;
					ret = execve(input[0], input, NULL);
					ft_printf("ret %d\n", ret);
					garbage_collect(input);
				}
				else
					wait(&id);
			}
			free(line);
		}
	}
	exit(SUCCESS);
}
