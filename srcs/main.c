/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 06:21:44 by mbarutel          #+#    #+#             */
/*   Updated: 2022/09/14 12:32:01 by mbarutel         ###   ########.fr       */
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
		ft_printf("This happens\n");	
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

/*
static void print_array(char **input)
{
	while (*input)
	{
		ft_printf("~%s\n", *input);
		input++;
	}
}
*/

int	main(void)
{
	pid_t	id;
	char	*line;
	char	**input;

	line = NULL;
	input = NULL;
	while (1)
	{
		ft_printf("$>: ");	
		if (get_next_line(0, &line))
		{
			ft_printf("[%s]\n", line);
			input = ft_strsplit(line, ' ');
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
//			print_array(input);
			free(line);
		}
	}
	exit(SUCCESS);
}
