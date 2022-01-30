/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 20:35:03 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 01:44:30 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	export_checker(t_shell *shell, int i, int j)
{
	if (shell->cmd[i][0] == '*' && !shell->cmd[i][j + 1])
		return (2);
	if (shell->cmd[i][0] != '_' && !ft_isalpha(shell->cmd[i][0]))
		return (1);
	while (shell->cmd[i][j] && shell->cmd[i][j] != '+' \
		&& shell->cmd[i][j] != '=')
	{
		if (shell->cmd[i][j] == '_' && !ft_isalnum(shell->cmd[i][j + 1]))
			return (2);
		j++;
	}
	if (shell->cmd[i][j] == '+' && shell->cmd[i][j + 1] != '=')
		return (1);
	return (0);
}

static int	new_env2(t_shell *shell, t_structenv *tmp, int i, int j)
{
	char	*str;
	int		res;

	res = ft_strlen(shell->cmd[i]) - j + 1;
	if (shell->cmd[i][j] == '=' && shell->cmd[i][j + 1])
	{
		free(tmp->value);
		tmp->value = ft_substr(shell->cmd[i], j + 1, res);
	}
	else if (shell->cmd[i][j] == '+' && shell->cmd[i][j + 2])
	{
		str = ft_substr(shell->cmd[i], j + 2, res);
		tmp->value = ft_strjoin_free(tmp->value, str);
		free(str);
	}
	else
	{
		free(tmp->value);
		tmp->value = NULL;
	}
	tmp->equality = 1;
	return (1);
}

static int	new_env(t_shell *shell, int i, int j)
{
	t_structenv	*tmp;
	char		*str;

	while (shell->cmd[i][j] && shell->cmd[i][j] != '=' \
		&& shell->cmd[i][j] != '+')
		j++;
	tmp = shell->env_mass;
	str = ft_substr(shell->cmd[i], 0, j);
	while (tmp)
	{
		if (ft_strcmp(str, tmp->key))
			tmp = tmp->next;
		else
		{
			free(str);
			return (new_env2(shell, tmp, i, j));
		}
	}
	free(str);
	return (0);
}

static void	export_work(t_shell *shell, int i, int j, int eq)
{
	int			a;
	t_structenv	*tmp;

	tmp = (t_structenv *)malloc(sizeof(t_structenv));
	if (shell->cmd[i][j - 1] != '+')
		tmp->key = ft_substr(shell->cmd[i], 0, j);
	else
		tmp->key = ft_substr(shell->cmd[i], 0, j - 1);
	j++;
	a = j;
	tmp->flag = env_size(shell, 0) + 1;
	tmp->next = NULL;
	tmp->equality = eq;
	if (shell->cmd[i][j])
	{
		while (shell->cmd[i][j])
			j++;
		tmp->value = ft_substr(shell->cmd[i], a, j - a);
	}
	else
		tmp->value = NULL;
	ft_lstadd_back_env(&shell->env_mass, tmp);
}

void	ft_export_with_param(t_shell *shell, int i, int j)
{
	int	res;

	while (shell->cmd[++i])
	{
		j = 0;
		res = export_checker(shell, i, j);
		if (res == 2)
			break ;
		if (res == 1)
		{
			error_output(shell->cmd[i]);
			g_ex_flag = 1;
			continue ;
		}
		if (!new_env(shell, i, j))
		{
			while (shell->cmd[i][j] && shell->cmd[i][j] != '=')
				j++;
			if (!shell->cmd[i][j])
				export_work(shell, i, j, 0);
			else
				export_work(shell, i, j, 1);
		}
		g_ex_flag = 0;
	}
}
