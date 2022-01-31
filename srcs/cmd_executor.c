/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:09 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 08:08:41 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	builtin_func_two(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd[0], "cd") \
		|| !ft_strcmp(shell->cmd[0], "CD"))
		ft_cd(shell);
	else if (!ft_strcmp(shell->cmd[0], "unset") \
		|| !ft_strcmp(shell->cmd[0], "UNSET"))
		ft_unset(shell);
	else
		return (1);
	return (0);
}

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
		ft_env(shell, 1);
	else if (!ft_strcmp(shell->cmd[0], "export") \
		|| !ft_strcmp(shell->cmd[0], "EXPORT"))
	{
		if (shell->cmd[1])
		{
			ft_export_with_param(shell, 0, 0);
		}
		else
			ft_export_without_param(shell, 1, 0);
	}
	else if (builtin_func_two(shell))
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

void	cmd_executor(char **env, t_shell *shell, int pid, int res)
{
	int	i;

	checking_path(shell);
	fd_work(shell, 0);
	if (shell->cmd != NULL && ft_strcmp(shell->cmd[0], " "))
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
