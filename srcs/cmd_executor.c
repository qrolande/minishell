/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:09 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/23 14:43:26 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	other_commands(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (shell->full_path && shell->full_path[++i])
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
			execve(tmp, shell->cmd, env_constructor(shell, 0, 0));
	}
	printf("minishell> %s: command not found\n", shell->cmd[0]);
	exit(127);
}

void	cmd_executor(char **env, t_shell *shell, int pid)
{
	int	i;
	int	res = 1;

	checking_path(shell);
	fd_work(shell, 0);
	//res = builtin_func(shell);
	if (res)
	{
		pid = fork();
		if (pid == 0)
		{
			fd_work(shell, 1);
			if (shell->error == 0)
				other_commands(shell);
			else
				exit(EXIT_FAILURE);
		}
	}
	if (pid)
	{
		waitpid(pid, &i, 0);
		g_ex_flag = i / 256;
	}
	if (shell->if_pipe - 1 > shell->num_pipe)
		pipe_executor(env, shell);
}
