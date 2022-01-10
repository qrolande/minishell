/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:01:47 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/10 17:03:10 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*types(char *str, int *i, t_shell *shell)
{
	if (str[*i] == '\'')
		return (gap(str, i));
	else if (str[*i] == '\"')
		return (double_gap(str, i, shell));
	else if (str[*i] == '\\')
		return (slash(str, i));
	else if (str[*i] == '~')
		return (tilde(str, i, shell));
	else if (str[*i] == '$')
		return (dollar(str, i, shell));
	return (str);
}

void	cmd_parser(t_shell *shell, char *str, int i, int j)
{
	int	res;

	res = 0;
	while (str[++i])
	{
		types(str, &i, shell);
		if (str[i] == ' ')
		{
			shell->cmd = two_dimension_check(shell->cmd, \
				ft_substr(str, res, i - res), &j, 0);
			res = i + 1;
		}
	}
	if (res != ft_strlen(str))
	{
		shell->cmd = two_dimension_check(shell->cmd, \
			ft_substr(str, res, ft_strlen(str) - res), &j, 0);
	}
	free(str);
}
