/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:36:05 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/26 23:06:01 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int monitoring(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i])
		return (1);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		i++;
	}
	if (str[i + 1] != '_' && str[i] == '+')
		return (1);
	return (0);
}

void	unset(t_shell	*shell)
{
	int i;

	i = 1;
	while (shell->cmd[i])
	{
		if(monitoring(shell->cmd[i]))
			;
		i++;
	}
}