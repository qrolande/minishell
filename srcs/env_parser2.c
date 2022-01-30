/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:23:33 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/27 22:30:09 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_size(t_shell *shell, int i)
{
	t_structenv	*tmp;

	tmp = shell->env_mass;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static t_structenv	*min_value(t_structenv *env, int flag)
{
	t_structenv	*tmp;
	t_structenv	*min;
	int			res;

	tmp = env;
	min = env;
	res = 0;
	while (tmp)
	{
		if (flag == MIN && ft_strcmp(tmp->key, min->key) < res)
			min = tmp;
		if (flag == MAX && ft_strcmp(tmp->key, min->key) > res)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

static t_structenv	*max_value(t_shell *shell, t_structenv *back)
{
	t_structenv	*tmp;
	t_structenv	*max;

	tmp = shell->env_mass;
	max = min_value(shell->env_mass, MAX);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, max->key) < 0 \
			&& ft_strcmp(tmp->key, back->key) > 0)
			max = tmp;
		tmp = tmp->next;
	}
	return (max);
}

void	env_work(t_shell *shell)
{
	t_structenv	*min;
	t_structenv	*next;
	int			j;
	int			i;

	i = 2;
	min = min_value(shell->env_mass, MIN);
	min->flag = 1;
	j = env_size(shell, 0) + 1;
	while (i < j)
	{
		next = max_value(shell, min);
		j = env_size(shell, 0) + 1;
		next->flag = i;
		i++;
		min = next;
	}
}
