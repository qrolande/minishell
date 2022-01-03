/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:39:15 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/03 20:35:58 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	all_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	key(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (i);
}

void	env_parser(t_shell *shell, char	**env)
{
	t_structenv	*tmp;
	int			i;
	int			j;

	i = all_env(env);
	while (i-- != 0)
	{
		j = key(env[i]);
		tmp = (t_structenv *)malloc(sizeof(t_structenv));
		tmp->flag = 1;
		tmp->value = ft_strdup(env[i] + 1 + j);
		tmp->key = ft_substr(env[i], 0, j);
		if (ft_strncmp("PATH", tmp->key, j) == 0)
			shell->full_path = ft_split(tmp->value, ':');
		tmp->next = shell->env_mass;
		shell->env_mass = tmp;
		free(tmp);
	}
}
