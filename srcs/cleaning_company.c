/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_company.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:56:42 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 21:00:02 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clean_cmd(t_shell *shell, int i)
{
	if (shell->cmd)
	{
		while (shell->cmd[i])
		{
			free(shell->cmd[i]);
			i++;
		}
		free(shell->cmd);
		shell->cmd = NULL;
	}
}

void	cleaning_company(t_shell *shell)
{
	clean_cmd(shell, 0);
}