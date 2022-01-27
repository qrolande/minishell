/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:26:31 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/19 21:28:07 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_output(t_node *data, int *i, int fd_out)
{
	if (!ft_strcmp(data->cmd[*i], "$?"))
		ft_putnbr_fd(g_exit_status, fd_out);
	else
		ft_putstr_fd(data->cmd[*i], fd_out);
	if (*i + 1 < ft_bigstr_len(data->cmd))
		write(fd_out, " ", 1);
	*i += 1;
}

void	pwd_f(t_node *data)
{
	char	*buff;
	int		fd_out;

	fd_out = 1;
	if (data->r.r_num || data->r.x_num)
		fd_out = data->r.r_fd;
	if (data->pipe_num < data->is_pipe - 1)
		fd_out = data->fd[data->pipe_num][1];
	buff = malloc(sizeof(char) * 1000);
	getcwd(buff, 1000);
	if (!buff[0])
	{
		perror("\n Error getcwd");
		g_exit_status = 1;
		return ;
	}
	else
	{
		ft_putstr_fd(buff, fd_out);
		write(fd_out, "\n", 1);
	}
	free(buff);
	g_exit_status = 0;
}

void	echo_f(t_node *data)
{
	int	flag;
	int	fd_out;
	int	i;

	fd_out = 1;
	flag = 0;
	i = 1;
	change_out(data, &fd_out);
	if (data->cmd[i] == NULL)
	{
		write(fd_out, "\n", 1);
		return ;
	}
	if (!(ft_strcmp(data->cmd[i], "-n")))
	{
		i++;
		flag = 1;
	}
	while (data->cmd[i])
		echo_output(data, &i, fd_out);
	if (flag == 1)
		return ;
	write(fd_out, "\n", 1);
	g_exit_status = 0;
}

int	buildin_2(t_node *data)
{	
	if (!ft_strcmp(data->cmd[0], "export"))
	{
		if (data->cmd[1])
			export_f(data);
		else
			export_f2(data);
	}
	else if (!ft_strcmp(data->cmd[0], "exit"))
		exit_f(data);
	else
		return (1);
	return (0);
}

int	buildin_1(t_node *data)
{	
	if (!ft_strcmp(data->cmd[0], "pwd"))
		pwd_f(data);
	else if (!ft_strcmp(data->cmd[0], "echo"))
		echo_f(data);
	else if (!ft_strcmp(data->cmd[0], "cd"))
		cmd_cd(data);
	else if (!ft_strcmp(data->cmd[0], "env"))
		env_f(data);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		unset_f(data, 0);
	else if (buildin_2(data))
		return (1);
	return (0);
}
