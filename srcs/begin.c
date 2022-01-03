/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 16:13:11 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 21:55:39 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	semicolon(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == ';')
			shell->num_cmd += 1;
		i++;
	}
	shell->splitted_cmd = ft_split(shell->line, ';');
}

void	begin(t_shell *shell)
{
	int	i;

	if (ft_strlen(shell->line))
	{
		i = 0;
		add_history(shell->line);
		semicolon(shell);
		while (shell->num_cmd)
		{
			prepare_cmd(shell, i);
			printf ("line = %s\n", shell->splitted_cmd[i]);
			shell->num_cmd--;
			i++;
		}
	}
}
