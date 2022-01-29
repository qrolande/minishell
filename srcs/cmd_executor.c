/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:09 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/27 21:31:02 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	builtin_func(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd[0], "echo") \
		|| !ft_strcmp(shell->cmd[0], "ECHO"))
		ft_echo(shell, 1);
	else if (!ft_strcmp(shell->cmd[0], "pwd") \
		|| !ft_strcmp(shell->cmd[0], "PWD"))
		ft_pwd(shell);
	else if (!ft_strcmp(shell->cmd[0], "exit") \
		|| !ft_strcmp(shell->cmd[0], "EXIT"))
		ft_exit(shell);
	else if (!ft_strcmp(shell->cmd[0], "env") \
		|| !ft_strcmp(shell->cmd[0], "ENV"))
		ft_env(shell);
	else if (!ft_strcmp(shell->cmd[0], "cd") \
		|| !ft_strcmp(shell->cmd[0], "CD"))
	 	ft_cd(shell);
	else if (!ft_strcmp(shell->cmd[0], "unset") \
		|| !ft_strcmp(shell->cmd[0], "UNSET"))
	 	ft_unset(shell);
	else
		return (1);
	return (0);
}

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
	int	res;

	checking_path(shell);
	fd_work(shell, 0);
	res = builtin_func(shell);
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
