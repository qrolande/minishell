/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatlyn <akatlyn@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 21:04:19 by akatlyn           #+#    #+#             */
/*   Updated: 2022/01/22 16:25:57 by akatlyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/minishell.h"

void	ft_pwd(void)
{
	char	*line;

	line = malloc(1000);
	getcwd(line, 1000);
	if (!line)
		perror("Reading path error\n");
	else
		ft_putstr_fd(line, 1);
	write(1, "\n", 1);
}