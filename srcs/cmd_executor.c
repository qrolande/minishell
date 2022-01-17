/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:09 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/16 16:32:13 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	other_commands(char **env, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (shell->full_path[i])
	{
		tmp = NULL;
		if (shell->cmd[0][0] != '/')
		{
			tmp = ft_strjoin(shell->full_path[i], "/");
			tmp = ft_strjoin(tmp, shell->cmd[0]);
		}
		else
			tmp = ft_strdup(shell->cmd[0]);
		if (!access(tmp, X_OK))
			execve(tmp, shell->cmd, env);
		i++;
	}
	printf("minishell: %s: command not found\n", shell->cmd[0]);
	exit(EXIT_FAILURE);
}

void	cmd_executor(char **env, t_shell *shell)
{
	int	i;
	int	pid;

	pid = 10;
	checking_path(shell);
	if (shell->if_pipe > shell->num_pipe && shell->num_pipe)
		close(shell->fd[shell->num_pipe - 1][1]);
	//Билты надо поставить сюда они должны объеденить условия для форков 
	pid = fork();
	if (pid == 0)
	{
		fd_work(shell);
		if (shell->error == 0)
			other_commands(env, shell);
		else
			exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		waitpid(pid, &i, 0);
		shell->ex_flag = i / 256;
	}
	if (shell->if_pipe - 1 > shell->num_pipe && pid > 0)
		pipe_executor(env, shell);
}
