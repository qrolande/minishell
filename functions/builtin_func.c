/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:06:41 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/22 16:57:17 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

int	builtin_func(t_shell	*shell)
{
	if (!ft_strcmp(shell->cmd[0], "echo") || !ft_strcmp(shell->cmd[0], "ECHO"))
		ft_echo(shell);
	else if (!ft_strcmp(shell->cmd[0], "exit"))
		ft_exit(shell);
	// if (!ft_strcmp(shell->cmd[0], "cd"))
	// 	ft_cd(shell);
	else if (!ft_strcmp(shell->cmd[0], "pwd") || !ft_strcmp(shell->cmd[0], "PWD"))
		ft_pwd();
	else
		return (1);
	// if (!ft_strcmp(shell->cmd[0], "unset"))
	// 	ft_unset();
	// if (!ft_strcmp(shell->cmd[0], "env"))
	// 	ft_unset();
	// if (!ft_strcmp(shell->cmd[0], "exit"))
	// 	ft_unset();
	return (0);
}
