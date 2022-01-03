/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:41:24 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 21:59:13 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	del_space(t_shell *shell, int j, int i)
{
	char	*line1;
	char	*line2;

	line1 = ft_substr(shell->splitted_cmd[i], 0, j);
	while (shell->splitted_cmd[i][j] == ' ')
		j++;
	line2 = ft_strdup(&shell->splitted_cmd[i][j - 1]);
	shell->splitted_cmd[i] = ft_strjoin(line1, line2);
	return (j);
}

void	if_space(t_shell *shell, int i)
{
	int		j;

	j = 0;
	while (shell->splitted_cmd[i][j] == ' ')
		j++;
	shell->splitted_cmd[i] = ft_strdup(&shell->splitted_cmd[i][j]);
	j = 0;
	while (shell->splitted_cmd[i][j])
	{
		if (shell->splitted_cmd[i][j] == '\''
			|| shell->splitted_cmd[i][j] == '\"')
		{
			j++;
			while ((shell->splitted_cmd[i][j] != '\'' \
				|| shell->splitted_cmd[i][j] != '\"') \
				&& shell->splitted_cmd[i][j])
				j++;
		}
		if (shell->splitted_cmd[i][j] == ' '
			&& shell->splitted_cmd[i][j + 1] == ' ')
			j = del_space(shell, j, i);
		j++;
	}
}
