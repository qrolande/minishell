/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:12:31 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/23 22:48:23 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*left_redir(char *line, int i, t_node *data)
{
	char	*temp;
	char	*temp1;
	char	*file_name;
	int		j;

	temp = ft_substr(line, 0, i - 1);
	i++;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i])
		i++;
	file_name = ft_substr(line, j, i - j);
	opening_file(file_name, data, LEFT);
	temp1 = ft_strdup(line + i + 1);
	temp = ft_strjoin(temp, " ");
	temp = ft_strjoin(temp, temp1);
	return (temp);
}

int	check_red(char *line, int j)
{
	if (line[j] == '<')
		return (1);
	if (line[j] == '>' && (!line[j + 1] || line[j + 1] != '>'))
		return (2);
	else
		return (3);
}

char	*right_redir(char *line, int i, t_node *data)
{
	char	*temp;
	char	*temp1;
	char	*file_name;
	int		j;

	temp = ft_substr(line, 0, i - 1);
	i++;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i])
		i++;
	file_name = ft_substr(line, j, i - j);
	opening_file(file_name, data, RIGHT);
	temp1 = ft_strdup(line + i + 1);
	temp = ft_strjoin(temp, " ");
	temp = ft_strjoin(temp, temp1);
	return (temp);
}

char	*double_redir(char *line, int i, t_node *data)
{
	char	*temp;
	char	*temp1;
	char	*file_name;
	int		j;

	temp = ft_substr(line, 0, i - 1);
	i += 2;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i])
		i++;
	file_name = ft_substr(line, j, i - j);
	opening_file(file_name, data, X_RIGHT);
	temp1 = ft_strdup(line + i + 1);
	temp = ft_strjoin(temp, " ");
	temp = ft_strjoin(temp, temp1);
	return (temp);
}

char	*ft_redirect(char *line, int *i, t_node *data)
{
	int	flag;
	int	j;

	j = *i;
	*i = -1;
	flag = check_red(line, j);
	if (flag == LEFT)
		return (left_redir(line, j, data));
	if (flag == RIGHT)
		return (right_redir(line, j, data));
	if (flag == X_RIGHT)
		return (double_redir(line, j, data));
	return (line);
}

char	*parser_redir(char *line, t_node *data)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
			line = ft_heredoc(line, i, data);
		else if (line[i] == '>' || line[i] == '<')
			line = ft_redirect(line, &i, data);
	}
	return (line);
}
