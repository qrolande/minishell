/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:20:26 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/05 18:32:31 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	smth_wrong(char *file, t_node *data)
{
	data->is_err += 1;
	printf("minishell: %s: %s\n", file, strerror(errno));
}

void	opening_file(char *file, t_node *data, int flag)
{
	int	fd;

	if (flag == LEFT)
	{
		fd = open(file, O_RDONLY, 0644);
		if (data->r.l_num == 0)
			data->r.l_num = 1;
		else
			close(data->r.l_fd);
		data->r.l_fd = fd;
	}
	else
	{
		if (flag == RIGHT)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (flag == X_RIGHT)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->r.r_num == 0)
			data->r.r_num = 1;
		else
			close(data->r.r_fd);
		data->r.r_fd = fd;
	}
	if (fd < 0)
		smth_wrong(file, data);
	free(file);
}
