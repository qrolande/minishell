/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:29:11 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 02:58:41 by akatlyn          ###   ########.fr       */
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

// static void	signals_work(int signal)
// {
// 	(void)signal;
// 	rl_on_new_line();
// 	rl_redisplay();
// 	write(1, "  \n", 3);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// static void	signals(void)
// {
// 	signal(SIGINT, signals_work);
// 	signal(SIGQUIT, SIG_IGN);
// }

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	init(shell, av, env);
	while (ac)
	{
		shell->line = NULL;
		//signals();
		shell->line = readline("minishell> ");
		if (shell->line == NULL)
			shell->line = ft_strdup("exit");
		else if (shell->line && ft_strlen(shell->line))
			begin(shell, env, 0);
		free(shell->line);
	}
	return (0);
}
