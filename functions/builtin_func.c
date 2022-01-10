/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:06:41 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/10 22:26:14 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_pwd(void)
{
	char	*line;

	line = malloc(1000);
	getcwd(line, 1000);
	if (!line)
		perror("Reading path error\n");
	else
		ft_putstr_fd(line, 1);
	write(1, "\n", 1);
}

int	builtin_func(t_shell	*shell)
{
	// if (!ft_strcmp(shell->cmd[0], "echo"))
	// 	ft_echo(shell);
	// if (!ft_strcmp(shell->cmd[0], "cd"))
	// 	ft_cd(shell);
	if (!ft_strcmp(shell->cmd[0], "pwd"))
		ft_pwd();
	// if (!ft_strcmp(shell->cmd[0], "export"))
	// 	ft_export();
	// if (!ft_strcmp(shell->cmd[0], "unset"))
	// 	ft_unset();
	// if (!ft_strcmp(shell->cmd[0], "env"))
	// 	ft_unset();
	// if (!ft_strcmp(shell->cmd[0], "exit"))
	// 	ft_unset();
	return (0);
}
