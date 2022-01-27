/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:29:11 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/27 21:02:51 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init(t_shell *shell, char **av, char **env)
{
	(void)av;
	shell->num_cmd = 1;
	shell->cmd = NULL;
	shell->env_mass = NULL;
	shell->full_path = NULL;
	shell->her.if_heredoc = 1;
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
		shell->line = NULL;
		signals_first();
		shell->line = readline("minishell> ");
		if (shell->line == NULL)
			shell->line = ft_strdup("exit");
		signals_second();
		if (ft_strlen(shell->line))
			begin(shell, env, 0);
		free(shell->line);
	}
	return (0);
}
