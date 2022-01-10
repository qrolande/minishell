/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:36:09 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 19:10:00 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_executor(char **env, t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (builtin_func(shell) && shell->error == 0)
			other_commands(env, shell);
		else
			exit(EXIT_FAILURE);
	}
}