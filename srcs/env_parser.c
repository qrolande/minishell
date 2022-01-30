/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qrolande <qrolande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:39:15 by qrolande          #+#    #+#             */
/*   Updated: 2022/01/30 07:15:58 by qrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	checking_path(t_shell *shell)
{
	t_structenv	*temp_env;

	temp_env = shell->env_mass;
	while (temp_env)
	{
		if (ft_strncmp("PATH", temp_env->key, 4) == 0)
			shell->full_path = ft_split(temp_env->value, ':');
		temp_env = temp_env->next;
	}
}

static int	key(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (i);
}

static void	parse_env_lvl(t_structenv *tmp, char **env, int i, int j)
{
	char	*res;

	res = NULL;
	res = ft_strdup(env[i] + 1 + j);
	tmp->value = ft_itoa(ft_atoi(res) + 1);
	free (res);
}

void	env_parser(t_shell *shell, char	**env)
{
	t_structenv	*tmp;
	int			i;
	int			j;

	i = 0;
	while (env[i])
		i++;
	while (i-- != 0)
	{
		j = key(env[i]);
		tmp = (t_structenv *) malloc(sizeof(t_structenv));
		tmp->flag = 0;
		tmp->equality = 1;
		tmp->key = ft_substr(env[i], 0, j);
		if (!ft_strcmp("SHLVL", tmp->key))
			parse_env_lvl(tmp, env, i, j);
		else
			tmp->value = ft_strdup(env[i] + 1 + j);
		if (ft_strncmp("HOME", tmp->key, ft_strlen(tmp->key)) == 0)
			shell->home = ft_strdup(tmp->value);
		tmp->next = shell->env_mass;
		shell->env_mass = tmp;
	}
	env_work(shell);
}

char	**env_constructor(t_shell *shell, int i, int j)
{
	t_structenv	*temp_env;
	char		**str_temp;

	temp_env = shell->env_mass;
	while (temp_env)
	{
		i++;
		temp_env = temp_env->next;
	}
	str_temp = (char **)malloc(sizeof(char *) * (i + 1));
	temp_env = shell->env_mass;
	while (j < i)
	{
		str_temp[j] = (char *)malloc(ft_strlen(temp_env->key) \
				+ ft_strlen(temp_env->value));
		str_temp[j] = ft_strjoin(temp_env->key, "=");
		str_temp[j] = ft_strjoin(str_temp[j], temp_env->value);
		temp_env = temp_env->next;
		j++;
	}
	str_temp[j] = NULL;
	return (str_temp);
}
