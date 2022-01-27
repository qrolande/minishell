/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 20:54:24 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/26 21:35:26 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_old_pwd(t_shell	*shell)
{
	char	*line;

	
}

void choice_way(t_shell *shell, char **way)
{
	if (!shell->cmd[1])
		*way = ft_strjoin(shell->home, "/");
	else if (!ft_strcmp(shell->cmd[1], "-"))
	{
		*way = set_old_pwd(shell);
	}
}

void ft_cd(t_shell	*shell)
{
	DIR		*dir;
	char	*way;

	choice_way(shell, way);
	

}