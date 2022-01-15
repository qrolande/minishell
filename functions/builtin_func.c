/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:06:41 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/15 18:02:40 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_echo(t_shell		*shell)
{
	int		i;
	int 	n;
	
	i = 1;
	n = 0;
	if (!(ft_strcmp(shell->cmd[i], "-n")))
		n = 1;
	while (shell->cmd[i])
	{
		ft_putstr_fd(shell->cmd[i + n], 1);
		i++;
		if (i + n < ft_bigstr_len(shell->cmd))
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}

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
	if (!ft_strcmp(shell->cmd[0], "echo") || !ft_strcmp(shell->cmd[0], "ECHO"))
		ft_echo(shell);
	// if (!ft_strcmp(shell->cmd[0], "cd"))
	// 	ft_cd(shell);
	if (!ft_strcmp(shell->cmd[0], "pwd") || !ft_strcmp(shell->cmd[0], "PWD"))
		ft_pwd();
	if (!ft_strcmp(shell->cmd[0], "export"))
		ft_exit(shell);
	// if (!ft_strcmp(shell->cmd[0], "unset"))
	// 	ft_unset();
	// if (!ft_strcmp(shell->cmd[0], "env"))
	// 	ft_unset();
	// if (!ft_strcmp(shell->cmd[0], "exit"))
	// 	ft_unset();
	return (0);
}
