/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:09 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 22:07:23 by qrolande         ###   ########.fr       */
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
		tmp = ft_strjoin(shell->full_path[i], "/");
		tmp = ft_strjoin(tmp, shell->cmd[0]);
		if (!access(tmp, X_OK))
			execve(tmp, shell->cmd, env);
		i++;
	}
	printf("minishell: %s: command not found\n", shell->cmd[0]);
	exit(EXIT_FAILURE);
}

static void	checking_path(t_shell *shell)
{
	t_structenv	*temp_env;

	temp_env = shell->env_mass;
	while (temp_env)
	{
		if (ft_strncmp("PATH", temp_env->key, 4) == 0)
			shell->full_path = ft_split(temp_env->value, ':');
		temp_env = temp_env->next;
	}
}

void	cmd_executor(char **env, t_shell *shell)
{
	int	pid;

	checking_path(shell);
	pid = fork();
	if (pid == 0)
	{
		if (shell->error == 0)
			other_commands(env, shell);
		else
			exit(EXIT_FAILURE);
	}
	if (pid > 0)
		wait(NULL);
}