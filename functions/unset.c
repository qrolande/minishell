/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:36:05 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/30 06:48:11 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	mystery_star(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != '*')
			return (1);
		i++;
	}
	return (0);
}

static int	monitoring(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '*')
		if (!mystery_star(str, i))
			return (0);
	if (!ft_isalpha(str[i]) && str[i] && str[i] != '_')
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' \
			&& str[i] == '+' && str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_finder(t_shell	*shell, t_structenv	*tmp, char *str)
{
	t_structenv	*tmp2;

	while (tmp->next)
	{
		if (!ft_strcmp(tmp->key, str))
			break ;
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp != shell->env_mass)
			tmp2->next = tmp->next;
		else
			shell->env_mass = shell->env_mass->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	ft_unset(t_shell	*shell)
{
	int			i;
	int			j;
	t_structenv	*tmp;
	char		*buf;

	i = 0;
	while (shell->cmd[++i])
	{
		if (monitoring(shell->cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(shell->cmd[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			g_ex_flag = 1;
			continue ;
		}
		j = ft_strlen(shell->cmd[i]);
		tmp = shell->env_mass;
		buf = ft_substr(shell->cmd[i], 0, j);
		ft_finder(shell, tmp, buf);
		free(buf);
		g_ex_flag = 0;
	}
}
