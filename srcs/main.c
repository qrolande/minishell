/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:29:11 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/13 19:47:41 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init(t_shell *shell, char **av, char **env)
{
	(void)av;
	shell->num_cmd = 1;
	shell->cmd = NULL;
	shell->line = NULL;
	shell->env_mass = NULL;
	shell->if_pipe = 0;
	shell->num_pipe = 10;
	shell->redir.x_fd = 0;
	shell->redir.x_num = 0;
	shell->redir.r_num = 0;
	shell->redir.l_num = 0;
	shell->redir.r_fd = 0;
	shell->redir.l_fd = 0;
	env_parser(shell, env);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	init(shell, av, env);
	while (ac)
	{
		shell->line = readline("minishell> ");
		begin(shell, env);
		free(shell->line);
	}
	return (0);
}
